#ifndef ARDUINO_SIM_CLIENT_H
#define ARDUINO_SIM_CLIENT_H

#include <QtBluetooth/qbluetoothhostinfo.h>
#include <QtBluetooth/qbluetoothlocaldevice.h>

#ifdef Q_OS_ANDROID
#include <QtAndroidExtras/QtAndroid>
#endif

#include "BtClient.h"
#include "RemoteSelector.h"

static const QLatin1String serviceUuid("e8e10f95-1a70-4b27-9ccf-02010264e9c8");
#ifdef Q_OS_ANDROID
static const QLatin1String reverseUuid("c8e96402-0102-cf9c-274b-701a950fe1e8");
#endif

class ArduinoSimClient
{
public:
    ArduinoSimClient();
    ~ArduinoSimClient();

private:
    BtClient* m_pBtClient;
    RemoteSelector* m_pRemoteSelector;
    QList<QBluetoothHostInfo> m_olocalAdapters;
};

#endif
