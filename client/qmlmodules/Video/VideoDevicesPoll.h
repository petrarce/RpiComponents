#pragma once
#include <QObject>
#include <QVector>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <vector>
#include <string>
#include <QQmlEngine>
#include <QJSEngine>

class VideoDevicesPoll :  public QObject
{
	Q_OBJECT
	Q_PROPERTY(QVariantList listDevices READ listDevices NOTIFY listDevicesChanged)
	Q_PROPERTY(qreal pollsPerSecond READ pollsPerSecond WRITE setPollsPerSecond NOTIFY pollsPerSecondChanged)
public:
	VideoDevicesPoll(QObject* parent = nullptr);
	virtual ~VideoDevicesPoll();
	const QVariantList& listDevices() const {return mListDevices; }
	qreal pollsPerSecond() const {return mPollsPerSecond; }
	void setPollsPerSecond(qreal pollsPerSecond);

	static QObject* instantiate(QQmlEngine*, QJSEngine*)
	{
		static VideoDevicesPoll inst;
		return &inst;
	}
signals:
	void listDevicesChanged(const QVariantList& listDevices);
	void pollsPerSecondChanged(qreal pollsPerSecond);

private:
	void pollFunction()
	{
		auto vdevs = []()->QVariantList
		{
			char buffer[128];
			QVariantList devices;
			FILE* pipe = popen(" v4l2-ctl --list-devices | grep : -A 1 | grep video | sed -e 's,[ \\t\\n],,g'", "r");
			if(!pipe)
				return {};
			try{
				while(std::fgets(buffer, 128, pipe))
				{
					QString str = buffer;
					devices.push_back(QVariant::fromValue(QString(buffer)));
				}
			}
			catch(...)
			{
				pclose(pipe);
				throw;
			}
			pclose(pipe);
			return devices;
		};

		while(mRunning)
		{
			auto devices = vdevs();
			if(mListDevices == devices)
				continue;
			else
			{
				mListDevices = devices;
				Q_EMIT listDevicesChanged(mListDevices);
			}
		}
	}

	QVariantList mListDevices;
	qreal mPollsPerSecond {1};
	QFuture<void> mPollFuture;
	bool mRunning {false};

};
