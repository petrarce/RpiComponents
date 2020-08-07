#pragma once
#include <boost/thread/thread.hpp>
#include <memory>
#include <mutex>
#include <definitions.hpp>


template<class ... Args>
class Operator
{
	virtual void executionTask(Args... args) = 0;
	std::function<void (Args...)> fn;
protected:
	std::unique_ptr<boost::thread> task;
public:
	Operator()
	{
		fn = [this](Args... args)
		{ 
			static std::mutex localMutex;
			std::lock_guard<std::mutex> guard(localMutex);
			try 
			{
				this->executionTask(args...);
			}
			catch(const boost::thread_interrupted& inter)
			{
				pr_dbg("thread interrupted");
			}	
		};
	}
	virtual ~Operator()
	{
		stop();
	}

	void run(Args... args)
	{
		stop();
		task = std::unique_ptr<boost::thread>(new boost::thread(fn, args...));
	}
	void stop(){
		if(task){
			task->interrupt();
			task->join();
			task = nullptr;
		}
	}

	Operator(const Operator&) = delete;
	const Operator& operator=(const Operator&) = delete;

};
