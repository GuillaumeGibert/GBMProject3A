#include "ArduinoSimClient.h"

ArduinoSimClient::ArduinoSimClient() : m_pBtClient(nullptr), m_pRemoteSelector(nullptr)
{
    m_olocalAdapters = QBluetoothLocalDevice::allDevices();
    const QBluetoothAddress adapter = m_olocalAdapters.isEmpty() ?
                                           QBluetoothAddress() :
                                           m_olocalAdapters.at(0).address();

    m_pRemoteSelector = new RemoteSelector(adapter);
    #ifdef Q_OS_ANDROID
        if (QtAndroid::androidSdkVersion() >= 23)
            m_pRemoteSelector->startDiscovery(QBluetoothUuid(reverseUuid));
        else
            m_pRemoteSelector->startDiscovery(QBluetoothUuid(serviceUuid));
    #else
        m_pRemoteSelector->startDiscovery(QBluetoothUuid(serviceUuid));
    #endif


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

    deleteAndNullify(m_pBtClient);
    deleteAndNullify(m_pRemoteSelector);
}
