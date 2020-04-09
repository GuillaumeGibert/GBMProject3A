#ifndef ARDUINO_SIM_CLIENT_H
#define ARDUINO_SIM_CLIENT_H

#include <QElapsedTimer>
#include <QtBluetooth/qbluetoothhostinfo.h>
#include <QtBluetooth/qbluetoothlocaldevice.h>
#include <QtBluetooth/qbluetoothuuid.h>

#ifdef Q_OS_ANDROID
#include <QtAndroidExtras/QtAndroid>
#endif

#include "BtClient.h"
#include "RemoteSelector.h"

static const QLatin1String serviceUuid("e8e10f95-1a70-4b27-9ccf-02010264e9c8");
#ifdef Q_OS_ANDROID
static const QLatin1String reverseUuid("c8e96402-0102-cf9c-274b-701a950fe1e8");
#endif

class ArduinoSimClient: public QObject
{
    Q_OBJECT

public:
    ArduinoSimClient();
    ~ArduinoSimClient();

    void setBufferBeginKeyword(QString);
    void setBufferEndKeyword(QString);
    void setValueSeparator(char);

public slots:
    void searchBtServer();
    void readData(const QString &sender, const QString &message);

signals:
    void sigBroadcastSignalValues(float, std::vector<float>);

private:
    BtClient* m_pBtClient;
    RemoteSelector* m_pRemoteSelector;
    QList<QBluetoothHostInfo> m_olocalAdapters;

    QString m_sBufferBeginKeyword;
    QString m_sBufferEndKeyword;
    char m_cValueSeparator;
    std::vector<float> m_vDataBuffer;
    QElapsedTimer* m_pElapsedTimer;

};

#endif
