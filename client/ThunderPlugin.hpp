#pragma once
#include <QQmlExtensionPlugin>
#include "RpiConnector.hpp"

class ThunderPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri) override;
};
