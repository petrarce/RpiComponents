#include <PIDcontroller.hpp>
#include <Operator.hpp>

class DC_ENG : public Operator<float /*update frequence*/>
{

public:
	DC_ENG():
		mPid(*this){}
	void configurePid(float p, float i, float d)
	{
		mPid.setProportional(p);
		mPid.setIntegral(i);
		mPid.setDifferential(d);
	}


	void setTorque(float torque)
	{
		std::lock_guard<std::mutex> guard(mTorqueMutex);
		mTorque = torque;
	}
	float getCurrentState() const 
	{ 
		return mAngle;
	}

	void input(float inp)
	{
		setTorque(inp);
	}
	void stop()
	{
		setTorque(0);
	}
	void goTo(float angle)
	{
		mPid.setTargetState(angle);
		mPid.run(60, 1e-2);
	}

private:

	void executionTask(float frequence) override
	{
		float dt = 1.f/frequence;
		auto wakePoint = boost::chrono::system_clock::now() + boost::chrono::microseconds(static_cast<int>(dt * 1000000));
		float totalTime = 0;
		while(1)
		{
			boost::this_thread::sleep_until(wakePoint);
			wakePoint = boost::chrono::system_clock::now() + boost::chrono::microseconds(static_cast<int>(dt * 1000000));

			std::lock_guard<std::mutex> guard(mAngleMutex);
			mSpeed += mTorque * dt;
			mSpeed = std::min(mSpeed, 20.f);
			mAngle += mSpeed * dt;
			if(totalTime > 1)
			{
				pr_dbg("mAngle=%2.1f, mSpeed=%2.1f", mAngle, mSpeed);
				totalTime = 0;
			}
			totalTime += dt;
		}
	}

	std::mutex mSpeedMutex;
	float mSpeed {0};
	std::mutex mAngleMutex;
	float mAngle {0};
	std::mutex mTorqueMutex;
	float mTorque {0};

	PIDcontroller<DC_ENG> mPid;
};