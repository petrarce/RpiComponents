#include <memory>
#include "RpiConnector.hpp"

using namespace std;
RpiConnector::RpiConnector()
{
    mContext =  std::unique_ptr<zmq::context_t>(new zmq::context_t(1));
    mSocket = std::unique_ptr<zmq::socket_t>(new zmq::socket_t(*mContext, zmq::socket_type::pair));
}


void RpiConnector::setRemoteAddress(const QString& remoteAddress)
{
    if(remoteAddress == mRemoteAddress)
        return;

    mRemoteAddress = remoteAddress;
    emit remoteAddressChanged(mRemoteAddress);
}
void RpiConnector::setPort(int port)
{
        if(port == mPort)
            return;

        mPort = port;
        emit portChanged(mPort);
}
void RpiConnector::setAction(int action)
{
        if(action == mAction)
            return;

        mAction = action;
        emit actionChanged(mAction);
}
void RpiConnector::setValue(int value)
{
        if(value == mValue)
            return;

        mValue = value;
        emit valueChanged(mValue);
}
void RpiConnector::send()
{
    std::array<signed char, 2> msg;
    msg[0] = static_cast<int>(mAction);
    msg[1] = mValue;
    mSocket->send(zmq::buffer(msg), zmq::send_flags::dontwait);
}

void RpiConnector::reconnect()
{
    std::string connection = mConnectionType.toStdString() + "://" + mRemoteAddress.toStdString() + ":" + std::to_string(mPort);
    try {
        mSocket->connect(connection.c_str());
    } catch(const zmq::error_t& err){
        pr_err("%s: %s:%d", err.what(), mRemoteAddress.toStdString().c_str(), mPort);
    }
}
