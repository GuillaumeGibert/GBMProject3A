#include "ArduinoSimulator.h"

ArduinoSimulator::ArduinoSimulator() :
    m_pTimer(new QBasicTimer), m_fFps(1.0), m_bIsConfigFileLoaded(false),
    m_i32DataIndex(0)
{
    if (!loadConfigFile("config.txt"))
        return;

    //! [Create Bt Server]
    server = new BtServer();
    connect(server, QOverload<const QString &>::of(&BtServer::clientConnected), this, &ArduinoSimulator::clientConnected);
    connect(server, QOverload<const QString &>::of(&BtServer::clientDisconnected), this,  QOverload<const QString &>::of(&ArduinoSimulator::clientDisconnected));
    connect(this, &ArduinoSimulator::sendMessage, server, &BtServer::sendMessage);
    server->startServer();
    //! [Create Chat Server]


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
	qDebug() << name << "  has joined";
    m_pTimer->start(1000.0 / m_fFps, this);

}

void ArduinoSimulator::clientDisconnected(const QString &name)
{
	qDebug() << name << "  has left";
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
    emit sendMessage(m_vSimulatedData[m_i32DataIndex%m_vSimulatedData.size()]);
    m_i32DataIndex++;
}

bool ArduinoSimulator::loadConfigFile(QString sConfigFilename)
{
    auto fillVariable = [](QStringList strList, QString key, auto var) -> void
    {
        if (strList[0].contains(key, Qt::CaseSensitive))
        {
            *var = strList[1].toFloat();
        }
    };

    QFile file(sConfigFilename);

    // opens the file
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "[ERROR] (ArduinoSimulator::loadConfigFile) Cannot open the Config File!";
        m_bIsConfigFileLoaded = false;
    }
    else
    {
        QTextStream in(&file);
        // 1st line
        QString line;

        while (in.readLineInto(&line))
        {
            qDebug() << line;
            QStringList list = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);

            fillVariable(list, "fps:", &m_fFps);



            if (list[0].contains("data:", Qt::CaseSensitive))
            {
                m_vSimulatedData.push_back(list[1]);
            }
        }

        file.close();

        m_bIsConfigFileLoaded = true;
    }

    return m_bIsConfigFileLoaded;
}


