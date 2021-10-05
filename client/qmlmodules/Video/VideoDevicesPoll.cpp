#include "VideoDevicesPoll.h"
#include <QtConcurrent/QtConcurrent>

VideoDevicesPoll::VideoDevicesPoll(QObject* parent):
	QObject(parent)
{
	mRunning = true;
	mPollFuture = QtConcurrent::run( this, &VideoDevicesPoll::pollFunction);
}

VideoDevicesPoll::~VideoDevicesPoll()
{
	mRunning = false;
	mPollFuture.waitForFinished();
}

void VideoDevicesPoll::setPollsPerSecond(qreal pollsPerSecond)
{
	if(qFuzzyCompare(pollsPerSecond, mPollsPerSecond))
			return;
	mPollsPerSecond = pollsPerSecond;
	Q_EMIT pollsPerSecondChanged(mPollsPerSecond);

}
