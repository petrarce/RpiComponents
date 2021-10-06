#pragma once
#include <QObject>
#include <definitions.hpp>
#include <QFuture>
#include <QVector>
#include <zmq.hpp>
#include "ThunderListener.hpp"

class ThunderDistanceListener : public ThunderListener
{
    Q_OBJECT

    Q_PROPERTY(QVector<qreal> distances READ distances NOTIFY distancesChanged)
public:
    explicit ThunderDistanceListener()
    {
        connect(this, &ThunderDistanceListener::distancesReceived,
                this, &ThunderDistanceListener::setDistances);
    }

    const QVector<qreal>& distances() const {return mDistances; }
signals:
    void distancesChanged(const QVector<qreal>& distances)const;
private:
	void handleData(DataTypeId typeId, const void* data, size_t size) override
	{
		if(typeId != tDistances)
		{
			pr_dbg("Unknown data type received");
			return;
		}

		if((size % sizeof(float)) != 0)
			throw std::runtime_error("invalid size of received data");
		QVector<qreal> distances(size / sizeof(float));
		for(int i = 0; i < size / sizeof(float); i++)
		{
			const float* value = static_cast<const float*>(data) + i;
			distances[i] = *value;
		}
		emit distancesReceived(distances);
	}
	void setDistances(QVector<qreal> distances)
	{
		mDistances = distances;
		emit distancesChanged(mDistances);
	}
signals:
	void distancesReceived(QVector<qreal> distances);

private:
	QVector<qreal> mDistances;
};

Q_DECLARE_METATYPE(QVector<qreal>)

