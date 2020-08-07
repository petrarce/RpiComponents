#include <iostream>
#include <Operator.hpp>
#include <eigen3/Eigen/Dense>
#include <cmath>
#include "Robot.hpp"


class Autopilot : public Operator<>
{
public:
    explicit Autopilot(Robot& r): robot(&r)
    {
        pr_dbg("created autopilit class");
    }

private:
    enum States {
        Idle,
        RecalculateBlindRange,
        ChangeDirection,
        Move,
    };

    bool isOnFinish()
    {
        return (robot->centerEig() - robot->targetPositionEig()).norm() < 5;
    }
    float angleToTarget()
    {
        float curAngle = robot->rotation();
        Eigen::Vector3f targetDir;
        targetDir << (robot->targetPositionEig() - robot->centerEig()).normalized(), 0;
        Eigen::Vector3f currDirection;
        currDirection << Eigen::Vector2f(cos(curAngle * 3.14 / 180), sin(curAngle * 3.14 / 180)), 0;
        auto direction = currDirection.cross(targetDir);
        float angle = std::acos(std::min(1.0f, std::max(-1.0f, currDirection.dot(targetDir)))) / 3.14 * 180;
        return angle * (1 - 2 * std::signbit(direction(2)));

    }


    float cubicSpline(float x)
    {
        auto v = fabs(x);
        if (v <= 0.5)
            return 1-3*v*v*2*(1-v);
        else if (v <= 1)
            return 2*(1-v)*(1-v)*(1-v);
        return 0;
    }

    float offsetAngle()
    {
        float curAngle = robot->rotation();
        float rotationAngle = 360 / directions.size();
        float maxWeight  = 0;
        int rotationIndex = 0;
        for(int i = 0; i < directions.size(); i++)
        {
            if(directions[i])
                continue;

            float angle = rotationAngle * i;
            angle = (angle > 180) ? angle - 360 : angle;
            float weight = 1.f / std::max(1.0, fabs(angle - angleToTarget())) * cubicSpline(angle / 190);
            if(maxWeight < weight)
            {
                maxWeight = weight;
                rotationIndex = i;
            }
        }
        float angle = rotationAngle * rotationIndex;
        angle = (angle > 180) ? angle - 360 : angle;
        return angle;
    }

    int recalculateDirections(std::array<float, 2> blindRange)
    {

        std::sort(blindRange.begin(), blindRange.end());
        int numOfFreeDirections = directions.size();
        float rotationAngle = 360.f / directions.size();
        int neighbDirCount = directions.size()/3;
        for(int i = 0; i < directions.size(); i++)
        {
            float currAngle = robot->rotation() + i * rotationAngle;
            if(currAngle > blindRange[0] && currAngle < blindRange[1])
            {
                directions[i] = true;
                numOfFreeDirections--;
                continue;
            }

            bool hasObstackle = false;
            for(int j = -neighbDirCount/2; j <= neighbDirCount/2; j++)
                hasObstackle |= robot->hasObstackle(robot->rotation() + (i + j) * rotationAngle);
            directions[i] = hasObstackle;
            numOfFreeDirections -= directions[i];
        }
        return numOfFreeDirections;
    }

    void executionTask()
    {
        States state = Idle;
        std::array<float, 2> blindRange {0,0};
        float previousAngle = 0;
        while(1)
        {
            boost::this_thread::interruption_point();
            switch(state){


            case Idle:
                pr_dbg("entered Idle state");
                if(isOnFinish())
                {
                    pr_dbg("destination reached");
                    return;
                }
                blindRange = {robot->rotation(), robot->rotation()};
                state = ChangeDirection;
                break;


            case RecalculateBlindRange:
                blindRange[robot->rotation() > previousAngle] = robot->rotation();
                state = ChangeDirection;
                break;


            case ChangeDirection:
            {
                pr_dbg("entered ChangeDirection state");
                if(!recalculateDirections(blindRange))
                {
                    pr_warn("no free space to make step");
                    return; //no free space left - robot stacked...
                }

                float angle = offsetAngle();
                float rotationAngle = 360.f / directions.size();
                float restrictedAngle = std::min(30.f, std::fabs(angle))
                                        * (1 - 2 * std::signbit(angle));
                float newAbsoluteAngle = robot->rotation() + restrictedAngle;
                previousAngle = robot->rotation();
                robot->rotate(newAbsoluteAngle);
                if(robot->hasObstackle(robot->rotation()))
                    state = RecalculateBlindRange;
                else
                    state = Move;
                break;
            }


            case Move:
                pr_dbg("entered Move state");
                robot->move();
                state = Idle;
                break;


            default:
                pr_err("Unknown state!!!");
                return;
            }
        }
    }


    std::array<bool, 32> directions{false, false, false, false};
    Robot* robot;

};
