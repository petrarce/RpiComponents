#include "GstreamerPipelineRunner.h"

void GstreamerPipelineRunner::stopPipeline()
{
	if(!mPipeline)
		return;
	gst_element_set_state(mPipeline, GST_STATE_NULL);
}

void GstreamerPipelineRunner::constructPipeline()
{
	if(mPipeline)
	{
		gst_object_unref(mPipeline);
		mPipeline = nullptr;
	}
	
	GError *error = nullptr;
	mPipeline = gst_parse_launch(mLaunch.toStdString().c_str(), &error);
	if(error)
		throw std::runtime_error(std::string("error ") + std::to_string(error->code) + " " + error->message);
}

void GstreamerPipelineRunner::startPipeline()
{
	if(!mPipeline)
		return;
	gst_element_set_state(mPipeline, GST_STATE_PLAYING);
}
void GstreamerPipelineRunner::setLaunch(const QString& launch)
{
	if(mLaunch == launch)
		return;
	
	mLaunch = launch;
	Q_EMIT launchChanged(mLaunch);
	stopPipeline();
	constructPipeline();
}