#include <cmath>
#include <chrono>
#include <thread>
#include <definitions.hpp>
#include "Robot.hpp"
#include "Autopilot.hpp"

Robot::Robot(): mAutopilot(new Autopilot(*this))
{
	connect(this, &Robot::updateCenter, this, &Robot::setCenter);
	connect(this, &Robot::updateRotation, this, &Robot::setRotation);
}
Robot::~Robot() { delete mAutopilot; }

void Robot::setCenter(const QVector2D& center)
{
	if (mCenter != center)
	{
		mCenter = center;
		emit centerChanged(mCenter);
	}
}

void Robot::setRotationStep(float rotationStep)
{
    if (mRotationStep == rotationStep || rotationStep <= 0)
        return;
    mRotationStep = rotationStep;
    emit rotationStepChanged(mRotationStep);
}

void Robot::setStepLength(float stepLength) 
{
	if (mStepLength != stepLength)
	{
		mStepLength = stepLength;
		emit stepLengthChanged(mStepLength);
	}
}


bool Robot::hasObstackle(float angle) const
{
//    if(mEnv == nullptr)
//        throw std::runtime_error("environment was not initialised");

    QVector2D direction = QVector2D(std::cos(angle * 3.14 / 180), std::sin(angle * 3.14 / 180));
    return mEnv.hasObstackle(mCenter, direction, mMaxObstDist);
}

static int convertAutopilotSpeed(int asp)
{
    const float a = - 50.f/11.f;
    const float b = 5550.f/11.f;
    return static_cast<int>(std::min(500.f, std::max(50.f, a * asp + b)));
}

void Robot::rotate(float ang)
{

    emit updateRotation(ang);
    auto waitms = convertAutopilotSpeed(mAutopilotSpeed);
    std::this_thread::sleep_for(std::chrono::milliseconds(waitms));

}

void Robot::move()
{
    QVector2D direction = QVector2D(cos(rotation() * 3.14 / 180), sin(rotation() * 3.14 / 180)) * mStepLength;
    emit updateCenter(mCenter + direction);
    auto waitms = convertAutopilotSpeed(mAutopilotSpeed);
    std::this_thread::sleep_for(std::chrono::milliseconds(waitms));
}
void Robot::startAutopilot(QVariantList objects)
{
	mAutopilot->stop();
	mEnv.setObjects(objects);
	mAutopilot->run();
}

void Robot::setMaxObstackleDist(float maxObstackleDist)
{
	if(maxObstackleDist == mMaxObstDist)
		return;

	mMaxObstDist = maxObstackleDist;
	emit maxObstackleDistChanged(mMaxObstDist);
}

void Robot::setAutopilotSpeed(int autopilotSpeed)
{
	if (autopilotSpeed == mAutopilotSpeed && (mAutopilotSpeed > 100 || mAutopilotSpeed < 1))
		return;

	mAutopilotSpeed = autopilotSpeed;
	emit autopilotSpeedChanged(mAutopilotSpeed);
}


