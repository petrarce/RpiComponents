#pragma once
#include <QVector2D>
#include <QObject>
#include <memory>
#include <exception>
#include <QQuickItem>
#include <eigen3/Eigen/Dense>
#include "Environment.hpp"
class Autopilot;
class Robot : public QQuickItem
{
	Q_OBJECT
	Q_PROPERTY(QVector2D center READ center WRITE setCenter NOTIFY centerChanged)
	Q_PROPERTY(float rotationStep READ rotationStep WRITE setRotationStep NOTIFY rotationStepChanged)
	Q_PROPERTY(float stepLength READ stepLength WRITE setStepLength NOTIFY stepLengthChanged)
	Q_PROPERTY(QVector2D targetPosition READ targetPosition WRITE setTargetPosition NOTIFY targetPositionChanged)
	Q_PROPERTY(float maxObstackleDist READ maxObstackleDist WRITE setMaxObstackleDist NOTIFY maxObstackleDistChanged)
	Q_PROPERTY(int autopilotSpeed READ autopilotSpeed WRITE setAutopilotSpeed NOTIFY autopilotSpeedChanged)
public:
    enum Directions{
        Front,
        Right,
        Left,
        Back,
    };
    explicit Robot();
    ~Robot();

	float rotationStep() const {return mRotationStep;}
	float stepLength() const {return mStepLength;}
	QVector2D center() const {return mCenter;}
	const QVector2D targetPosition() const { return mTargetPosition; }
	Eigen::Vector2f centerEig() const {
		return Eigen::Vector2f(mCenter.x(), mCenter.y());
	}
	Eigen::Vector2f targetPositionEig() const
	{
		return Eigen::Vector2f(mTargetPosition.x(), mTargetPosition.y());
	}
	float maxObstackleDist() const { return mMaxObstDist; }
	int autopilotSpeed() const {return mAutopilotSpeed; }

	void setCenter(const QVector2D& center);
	void setRotationStep(float rotationStep);
	void setStepLength(float stepLength);
	void setTargetPosition(const QVector2D& targetPosition)
	{
		if(mTargetPosition == targetPosition)
			return;

		mTargetPosition = targetPosition;
		emit targetPositionChanged(mTargetPosition);
	}
	void setMaxObstackleDist(float maxObstackleDist);
	void setAutopilotSpeed(int autopilotSpeed);

	Q_INVOKABLE bool hasObstackle(float angle) const;
	Q_INVOKABLE float getCurrentAngle();
	Q_INVOKABLE void rotate(float angle);
	Q_INVOKABLE void move();
	Q_INVOKABLE void startAutopilot(QVariantList objects);

signals:
	void centerChanged(const QVector2D& center);
	void angleChanged(float angle) const;
	void rotationStepChanged(float rotationStep);
	void stepLengthChanged(float stepLength) const;
	void targetPositionChanged(const QVector2D& targetPosition) const;
	void maxObstackleDistChanged(float maxObstackleDist) const;
	void autopilotSpeedChanged(int autopilotSpeed) const;

private:
signals:
	void updateRotation(float angle) const;
	void updateCenter(QVector2D center) const;


private:
    float mRotationStep {5};
    float mStepLength {1};
    QVector2D mCenter{0,0};
    Environment mEnv;
    QVector2D mTargetPosition {0,0};
    Autopilot* mAutopilot;
    float mMaxObstDist {1};
    int mAutopilotSpeed {1};

};
