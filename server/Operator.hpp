#pragma once
#include <boost/thread/thread.hpp>
#include <memory>
#include <mutex>
#include <definitions.hpp>


template<class ... Args>
class Operator
{
	std::unique_ptr<boost::thread> task;
	virtual void executionTask(Args... args) = 0;
	std::function<void (Args...)> fn;
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
	void run(Args... args)
	{
		if(task)
		{
			task->interrupt();
			task->join();
		}
		task = std::unique_ptr<boost::thread>(new boost::thread(fn, args...));
	}

	Operator(const Operator&) = delete;
	const Operator& operator=(const Operator&) = delete;

};
