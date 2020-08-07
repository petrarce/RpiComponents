#include <QQmlEngine>
#include "PathExploration.hpp"
#include "Robot.hpp"
#include "Environment.hpp"

void PathExploration::registerTypes(const char *uri)
{
    qmlRegisterType<Robot>(uri, 0, 1, "Robot");
    qmlRegisterType<Environment>(uri, 0, 1, "Environment");
}
