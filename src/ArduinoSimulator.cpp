#include "ArduinoSimulator.h"

ArduinoSimulator::ArduinoSimulator() :
    m_pTimer(new QBasicTimer), m_fFps(1.0), m_bIsDataFileLoaded(false),
    m_i32DataIndex(0)
{
    //! [Create Bt Server]
    server = new BtServer();
    connect(server, QOverload<const QString &>::of(&BtServer::clientConnected), this, &ArduinoSimulator::clientConnected);
    connect(server, QOverload<const QString &>::of(&BtServer::clientDisconnected), this,  QOverload<const QString &>::of(&ArduinoSimulator::clientDisconnected));
    connect(this, &ArduinoSimulator::sendMessage, server, &BtServer::sendMessage);
    server->startServer();
    //! [Create Bt Server]

}

ArduinoSimulator::~ArduinoSimulator()
{
    m_pTimer->stop();

    qDeleteAll(clients);

    delete server;

    if (nullptr != m_pTimer)
        delete m_pTimer;
}

//! [clientConnected clientDisconnected]
void ArduinoSimulator::clientConnected(const QString &name)
{
    qDebug() << "[INFO] The client " << name << "  has joined";
    qDebug() << "[INFO] Data are being sent to this client";
    m_pTimer->start(1000.0 / m_fFps, this);

}

void ArduinoSimulator::clientDisconnected(const QString &name)
{
    qDebug() <<"[INFO] The client "<< name << "  has left";
    qDebug() << "[INFO] Data stop being sent to this client";
    m_pTimer->stop();
}
//! [clientConnected clientDisconnected]

//! [clientDisconnected]
void ArduinoSimulator::clientDisconnected()
{
    BtClient *client = qobject_cast<BtClient *>(sender());
	if (client) 
	{
		clients.removeOne(client);
		client->deleteLater();
	}
}
//! [clientDisconnected]

void ArduinoSimulator::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);

    doWork();
}

void ArduinoSimulator::doWork()
{
    if (m_vSimulatedData.size() > 0 && m_bIsDataFileLoaded)
    {
        emit sendMessage(m_vSimulatedData[m_i32DataIndex%m_vSimulatedData.size()]);
        m_i32DataIndex++;
    }
    else
    {
        qDebug() << "[WARNING]: The data file was not set properly!";
    }
}

void ArduinoSimulator::setDataFile(QString sDataFilename)
{
    qDebug() << sDataFilename;
    loadDataFile(sDataFilename);
}

bool ArduinoSimulator::loadDataFile(QString sDataFilename)
{
    QFile file(sDataFilename);

    // opens the file
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "[ERROR] (ArduinoSimulator::loadDataFile) Cannot open the Data File!";
        m_bIsDataFileLoaded = false;
    }
    else
    {
        QTextStream in(&file);
        QString line;

        while (in.readLineInto(&line))
        {
            QStringList list = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);

            if (list[0].contains("fps:", Qt::CaseSensitive))
            {
                m_fFps = list[1].toFloat();
            }

            if (list[0].contains("data:", Qt::CaseSensitive))
            {
                m_vSimulatedData.push_back(list[1]);
            }
        }
        file.close();

        qDebug() << "[INFO] The data were loaded correctly";
        qDebug() << "[INFO] There are " << m_vSimulatedData.size() << " frames";
        qDebug() << "[INFO] The FPS is " << m_fFps << " Hz";


        m_bIsDataFileLoaded = true;
    }

    return m_bIsDataFileLoaded;
}


