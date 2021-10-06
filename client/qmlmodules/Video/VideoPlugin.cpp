#include <QQmlEngine>
#include "VideoPlugin.h"
#include "VideoDevicesPoll.h"
#include "GstreamerPipelineRunner.h"

void VideoPlugin::registerTypes(const char *uri)
{
	qmlRegisterSingletonType<VideoDevicesPoll>(uri, 0, 1, "VideoDevicesPoll", &VideoDevicesPoll::instantiate);
	qmlRegisterType<GstreamerPipelineRunner>(uri, 0, 1, "GstreamerPipelineRunner");
}
