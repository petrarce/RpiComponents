#include <QQmlEngine>
#include "ThunderPlugin.hpp"
#include "RpiConnector.hpp"
#include "ThunderDistanceListener.hpp"

void ThunderPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<RpiConnector>(uri, 0, 1, "RpiConnector");
    qmlRegisterType<ThunderDistanceListener>(uri, 0, 1, "ThunderDistanceListener");
}
