#pragma once
#include <QObject>
#include <definitions.hpp>
#include <QFuture>
#include <zmq.hpp>

class ThunderListener : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString remoteAddress READ remoteAddress WRITE setRemoteAddress NOTIFY remoteAddressChanged)
    Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)

public:
    explicit ThunderListener();
    ThunderListener(const ThunderListener&) = delete;
    ThunderListener& operator=(const ThunderListener&) = delete;
    const QString& remoteAddress() const { return mRemoteAddress; }
    int port() const { return mPort; }

    void setRemoteAddress(const QString& remoteAddress);
    void setPort(int port);

signals:
	void remoteAddressChanged(const QString& remoteAddress) const;
	void portChanged(int port) const;

private:
	void listen();
	void reconnect();
	virtual void handleData(DataTypeId, const void*, size_t) = 0;
	QString mRemoteAddress = "127.0.0.1";
	QString mConnectionType = "tcp";
	int mPort {0};
	zmq::context_t mContext;
	zmq::socket_t mSocket;
	QFuture<void> listenThread;
};

