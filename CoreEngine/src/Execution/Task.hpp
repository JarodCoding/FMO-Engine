/*
 * Task.hpp
 *
 *  Created on: 22.08.2016
 *      Author: Jarod
 */
#ifndef COREENGINE_SRC_EXECUTION_TASK_HPP_
#define COREENGINE_SRC_EXECUTION_TASK_HPP_

#include "vector"

namespace Execution {
	typedef uint_fast8_t ExecutionPriority;
	class Task;
}

#include "../Data/ExtensionType.hpp"
#include "Module.hpp"
#include "atomic"
#include "TaskManager.hpp"

namespace Execution {

class Task {
protected:
	boost::lockfree::queue<Task *> dependers;
	std::atomic<uint_fast8_t> dependencies;
	std::vector<Data::ExtensionTypeID> extensionOfInterest;
	std::atomic<bool> running;
public:
	void *function;
	void * parameter;
	ExecutionPriority priority;
	void run();
	//ThreadSafe
	void addDependency(Task&);
	void addDependency(Task&);
	std::vector<Data::ExtensionTypeID>& getExtensionOfInterest();
	void registerExtensionsOfInterest(std::vector<Data::ExtensionTypeID>&);
};

} /* namespace Execution */

#endif /* COREENGINE_SRC_EXECUTION_TASK_HPP_ */
