#include <QtCore/qdebug.h>

#include <QtBluetooth/qbluetoothhostinfo.h>
#include <QtBluetooth/qbluetoothdeviceinfo.h>
#include <QtBluetooth/qbluetoothlocaldevice.h>
#include <QtBluetooth/qbluetoothuuid.h>

#include <QBasicTimer>
#include <QFile>

#include "BtClient.h"
#include "BtServer.h"

//! [declaration]
class ArduinoSimulator : public QObject
{
    Q_OBJECT

public:
    ArduinoSimulator();
    ~ArduinoSimulator();

protected:
    void timerEvent(QTimerEvent *e);
    void doWork();
    bool loadDataFile(QString sDataFilename);

signals:
    void sendMessage(const QString &message);

private slots:
    void clientConnected(const QString &name);
    void clientDisconnected(const QString &name);
    void clientDisconnected();
    void setDataFile(QString sDataFilename);

private:
    BtServer *server;
    QList<BtClient *> clients;
    QBasicTimer* m_pTimer;
    float m_fFps;
    bool m_bIsDataFileLoaded;
    std::vector<QString> m_vSimulatedData;
    int m_i32DataIndex;

};
//! [declaration]
