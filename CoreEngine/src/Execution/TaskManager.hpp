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
#include "Task.hpp"
namespace Execution{
	namespace TaskManager{
	typedef uint_fast8_t ThreadID;

		void queueTask(Task&);
		void start();
		void shutdown();
		ThreadID getCurrentThreadID();
	}
}
#endif /* TASKMANAGER_HPP_ */
