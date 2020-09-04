#pragma once
#include <QObject>
#include <definitions.hpp>
#include <zmq.hpp>
#include <QQmlEngine>

class RpiConnector : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString remoteAddress READ remoteAddress WRITE setRemoteAddress NOTIFY remoteAddressChanged)
    Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(int action READ action WRITE setAction NOTIFY actionChanged)
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)

public:
	enum MsgCode
	{
		MSGCODES	
	};
	Q_ENUMS(MsgCode)
    explicit RpiConnector();
    const QString& remoteAddress() const { return mRemoteAddress; }
    int port() const { return mPort; }
    int action() const { return mAction; }
    int value() const { return mValue; }

    void setRemoteAddress(const QString& remoteAddress);
    void setPort(int port);
    void setAction(int action);
    void setValue(int value);
    Q_INVOKABLE void send();
    Q_INVOKABLE void reconnect();

signals:
	void remoteAddressChanged(const QString& remoteAddress) const;
	void portChanged(int port) const;
	void actionChanged(int action) const;
	void valueChanged(int value) const;
private:

	QString mRemoteAddress = "127.0.0.1";
	QString mConnectionType = "tcp";
	int mPort {0};
	int mAction {-1};
	int mValue {0};
	std::unique_ptr<zmq::context_t> mContext;
	std::unique_ptr<zmq::socket_t> mSocket;
};

