#include "ArduinoSimClient.h"

ArduinoSimClient::ArduinoSimClient() :
    m_pBtClient(nullptr),
    m_pElapsedTimer(new QElapsedTimer)
{
    m_olocalAdapters = QBluetoothLocalDevice::allDevices();
}

ArduinoSimClient::~ArduinoSimClient()
{
    auto deleteAndNullify = [](auto pointer) -> void
    {
       if (nullptr != pointer)
       {
           delete pointer;
           pointer = nullptr;
       }
    };

   deleteAndNullify(m_pElapsedTimer);
   deleteAndNullify(m_pBtClient);
}

void ArduinoSimClient::searchBtServer()
{
    const QBluetoothAddress adapter = m_olocalAdapters.isEmpty() ?
                                           QBluetoothAddress() :
                                           m_olocalAdapters.at(0).address();

    RemoteSelector remoteSelector(adapter);

    #ifdef Q_OS_ANDROID
        if (QtAndroid::androidSdkVersion() >= 23)
            remoteSelector.startDiscovery(QBluetoothUuid(reverseUuid));
        else
            remoteSelector.startDiscovery(QBluetoothUuid(serviceUuid));
    #else
        remoteSelector.startDiscovery(QBluetoothUuid(serviceUuid));
    #endif

    if (remoteSelector.exec() == QDialog::Accepted)
    {
        QBluetoothServiceInfo service = remoteSelector.service();

        qDebug() << "Connecting to service 2" << service.serviceName()
        << "on" << service.device().name();

        // Create client
        qDebug() << "Going to create client";

        if (nullptr == m_pBtClient)
            m_pBtClient = new BtClient(this);

        qDebug() << "Connecting...";

        connect(m_pBtClient, SIGNAL(messageReceived(const QString, const QString)), this, SLOT(readData(const QString, const QString)));
        connect(m_pBtClient, &BtClient::disconnected, this, QOverload<>::of(&ArduinoSimClient::clientDisconnected));
        qDebug() << "Start client";
        m_pBtClient->startClient(service);

        m_pElapsedTimer->start();
    }

}

void ArduinoSimClient::readData(const QString &sender, const QString &message)
{
    // looks for starting and ending keywords
    int dataBufferBegin = message.indexOf(m_sBufferBeginKeyword, 0);
    int dataBufferEnd = message.indexOf(m_sBufferEndKeyword, dataBufferBegin);

    // processes buffer if complete
    if ((dataBufferBegin != -1) && (dataBufferEnd != -1))
    {
        // cuts the buffer if necessary
        QString cutBuffer = message.mid(dataBufferBegin, dataBufferEnd - dataBufferBegin);

        // splits it into useful values
        QStringList listData = cutBuffer.split(m_cValueSeparator);

        // checks if at least 2 separators were found
        if (listData.count() < 2)
        {
            qCritical() << "[WARNING] <ArduinoSimClient> readData failure -> not enough data available --> skipped!";
            return;
        }

        // stores values in a vector of floats
        // skips the first and last ones that contain buffer separators
        m_vDataBuffer.clear();
        for (int i = 1; i < listData.count() - 1; i++)
        {
            m_vDataBuffer.push_back(listData[i].toFloat());
        }

        // sends the data through a signal
        emit sigBroadcastSignalValues((float)m_pElapsedTimer->elapsed() / 1000.0, m_vDataBuffer);

    }
}

void ArduinoSimClient::setBufferBeginKeyword(QString sBufferBeginKeyword)
{
    m_sBufferBeginKeyword = sBufferBeginKeyword;
}

void ArduinoSimClient::setBufferEndKeyword(QString sBufferEndKeyword)
{
    m_sBufferEndKeyword = sBufferEndKeyword;
}

void ArduinoSimClient::setValueSeparator(char cValueSeparator)
{
    m_cValueSeparator = cValueSeparator;
}

void ArduinoSimClient::clientDisconnected()
{
    m_pBtClient->deleteLater();
}
