#ifndef BT_CLIENT_H
#define BT_CLIENT_H

#include <QtCore/qobject.h>

#include <QtBluetooth/qbluetoothserviceinfo.h>
#include <QtBluetooth/qbluetoothsocket.h>

QT_FORWARD_DECLARE_CLASS(QBluetoothSocket)

QT_USE_NAMESPACE

//! [declaration]
class BtClient : public QObject
{
    Q_OBJECT

public:
    explicit BtClient(QObject *parent = nullptr);
    ~BtClient();

    void startClient(const QBluetoothServiceInfo &remoteService);
    void stopClient();

public slots:
    void sendMessage(const QString &message);

signals:
    void messageReceived(const QString &sender, const QString &message);
    void connected(const QString &name);
    void disconnected();
    void socketErrorOccurred(const QString &errorString);

private slots:
    void readSocket();
    void connected();
    void onSocketErrorOccurred(QBluetoothSocket::SocketError);

private:
    QBluetoothSocket *socket = nullptr;
};
//! [declaration]

#endif // BT_CLIENT_H
