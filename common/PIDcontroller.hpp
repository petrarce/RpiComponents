#include <Operator.hpp>

template<class Controlable>
class PIDcontroller : public Operator<int /*updateFrequenceHz*/, float /*eps*/>
{
public:
	PIDcontroller() = delete;
	PIDcontroller(Controlable& machine):
		mMachine(machine)
	{}

	void setProportional(float prop) { kProprotional = prop; }
	void setIntegral(float integ) { kIntegral = integ; }
	void setDifferential(float diff) { kDifferential = diff; }

	void setTargetState(float targetState) 
	{ 
		std::lock_guard<std::mutex> guard(mTargStateMutex);
		mTargetState = targetState; 
	}

private:
	void executionTask(int updateFrequenceHz, float eps) override
	{
		assert(eps > 0);
		assert(updateFrequenceHz > 0);
		float integral = 0;
		float lastError = mTargetState - mMachine.getCurrentState();
		float dt = 1.f / updateFrequenceHz;

		auto wakePiont = boost::chrono::system_clock::now() + boost::chrono::microseconds(static_cast<int>(dt * 1000000));
		while(1)
		{
			float error =  mTargetState - mMachine.getCurrentState();

			integral += error * dt;
			float differential = (error - lastError) / dt;
			lastError = error;

			float inp = kProprotional * error + kIntegral * integral + kDifferential * differential;
			
			mMachine.input(inp);

			boost::this_thread::sleep_until(wakePiont);
			wakePiont = boost::chrono::system_clock::now() + boost::chrono::microseconds(static_cast<int>(dt * 1000000));
		}
	}

	Controlable& mMachine {nullptr};
	float kProprotional {1};
	float kIntegral {1};
	float kDifferential {1};
	float mTargetState {0};

	std::mutex mTargStateMutex;
};