#include <memory>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <definitions.hpp>
#include "ThunderListener.hpp"

using namespace std;
ThunderListener::ThunderListener():
    mContext(1),
    mSocket(mContext, zmq::socket_type::pull)
{
    reconnect();
    listenThread = QtConcurrent::run(this, &ThunderListener::listen);
}


void ThunderListener::setRemoteAddress(const QString& remoteAddress)
{
    if(remoteAddress == mRemoteAddress)
        return;

    mRemoteAddress = remoteAddress;
    emit remoteAddressChanged(mRemoteAddress);
    reconnect();
}
void ThunderListener::setPort(int port)
{
        if(port == mPort)
            return;

        mPort = port;
        emit portChanged(mPort);
        reconnect();
}
void ThunderListener::listen()
{
    while(1)
    {
        zmq::message_t msg;
        mSocket.recv(msg, zmq::recv_flags::none);
        if(msg.size() < sizeof(DataTypeId))
        {
            pr_warn("ill-formated message... Ignoring");
            continue;
        }
        DataTypeId* dataType = static_cast<DataTypeId*>(msg.data());
        handleData(*dataType, (dataType + 1), msg.size() - sizeof(DataTypeId));
    }
}

void ThunderListener::reconnect()
{
    std::string connection = mConnectionType.toStdString() + "://" + mRemoteAddress.toStdString() + ":" + std::to_string(mPort);
    mSocket.connect(connection.c_str());
}
