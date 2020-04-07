#include "BtClient.h"

#include <QtCore/qmetaobject.h>

BtClient::BtClient(QObject *parent)
    :   QObject(parent)
{
}

BtClient::~BtClient()
{
    stopClient();
}

//! [startClient]
void BtClient::startClient(const QBluetoothServiceInfo &remoteService)
{
    if (socket)
        return;

    // Connect to service
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    qDebug() << "Create socket";
    socket->connectToService(remoteService);
    qDebug() << "ConnectToService done";

    connect(socket, &QBluetoothSocket::readyRead, this, &BtClient::readSocket);
    connect(socket, &QBluetoothSocket::connected, this, QOverload<>::of(&BtClient::connected));
    connect(socket, &QBluetoothSocket::disconnected, this, &BtClient::disconnected);
    connect(socket, QOverload<QBluetoothSocket::SocketError>::of(&QBluetoothSocket::error),
            this, &BtClient::onSocketErrorOccurred);

}
//! [startClient]

//! [stopClient]
void BtClient::stopClient()
{
    delete socket;
    socket = nullptr;
}
//! [stopClient]

//! [readSocket]
void BtClient::readSocket()
{
    if (!socket)
        return;

    while (socket->canReadLine()) {
        QByteArray line = socket->readLine();
        emit messageReceived(socket->peerName(),
                             QString::fromUtf8(line.constData(), line.length()));
    }
}
//! [readSocket]

//! [sendMessage]
void BtClient::sendMessage(const QString &message)
{
    QByteArray text = message.toUtf8() + '\n';
    socket->write(text);
}
//! [sendMessage]

void BtClient::onSocketErrorOccurred(QBluetoothSocket::SocketError error)
{
    if (error == QBluetoothSocket::NoSocketError)
        return;

    QMetaEnum metaEnum = QMetaEnum::fromType<QBluetoothSocket::SocketError>();
    QString errorString = socket->peerName() + QLatin1Char(' ')
            + metaEnum.valueToKey(error) + QLatin1String(" occurred");

    emit socketErrorOccurred(errorString);
}

//! [connected]
void BtClient::connected()
{
    emit connected(socket->peerName());
}
//! [connected]
