#include <QQmlEngine>
#include "VideoPlugin.h"
#include "VideoDevicesPoll.h"

void VideoPlugin::registerTypes(const char *uri)
{
	qmlRegisterSingletonType<VideoDevicesPoll>(uri, 0, 1, "VideoDevicesPoll", &VideoDevicesPoll::instantiate);
}
