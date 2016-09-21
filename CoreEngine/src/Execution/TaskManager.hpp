/*
 * TaskManager.hpp
 *	
 *  Created on: Aug 30, 2014
 *      Author: Pascal Kuthe
 */
#ifndef TASKMANAGER_HPP_
#define TASKMANAGER_HPP_
#include "boost/thread.hpp"
#include <stdint.h>
#include "Flags.hpp"
namespace Thread{
	typedef uint_fast8_t ID;
}
#include "Task.hpp"

namespace Execution{
	namespace TaskManager{

		void queueTask(Task&);
		void queueTask(std::shared_ptr<Task> &t);
		void queueTask(void(*func)(),ExecutionPriority);

		void start();
		void shutdown();
		void togglePrimaryQueue(bool enabled);
		bool primaryQueueEnable();
		Thread::ID getCurrentThreadID();
	}
}
#endif /* TASKMANAGER_HPP_ */
