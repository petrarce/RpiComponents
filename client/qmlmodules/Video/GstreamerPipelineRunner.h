#include <QObject>
#include <gst/gst.h>

class GstreamerPipelineRunner : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString launch READ launch WRITE setLaunch NOTIFY launchChanged)

public:
	Q_INVOKABLE void start();
	Q_INVOKABLE void stop();

	const QString& launch() const {return mLaunch; }
	void setLaunch(const QString& launch);
	
Q_SIGNALS:
	void launchChanged(const QString& launch);
private:
	void stopPipeline();
	void startPipeline();
	void constructPipeline();
	
	QString mLaunch;
	GstElement* mPipeline;
};
