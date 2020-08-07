#pragma once
#include <QVariantList>
#include <QSharedPointer>
#include <QObject>
#include <memory>

class Environment : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QVariantList objects READ objects WRITE setObjects NOTIFY objectsChanged)

public:
	const QVariantList& objects() const {return mObjects;}

	void setObjects(const QVariantList& objects);

	Q_INVOKABLE bool hasObstackle(const QVector2D& pos,
					  const QVector2D& direction,
					  float distance) const;
	const Environment& operator=(const Environment& other)
	{
		this->mObjects = other.mObjects;
		return *this;
	}
	Environment(const Environment& other)
	{
		this->mObjects = other.mObjects;
	}
	Environment(){}

signals:
	void objectsChanged(QVariantList objects) const;


private:

	QVariantList mObjects;
};
Q_DECLARE_METATYPE(Environment)
Q_DECLARE_METATYPE(Environment*)


