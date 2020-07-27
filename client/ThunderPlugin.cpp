#include <QQmlEngine>
#include "ThunderPlugin.hpp"

void ThunderPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<RpiConnector>(uri, 0, 1, "RpiConnector");
}
