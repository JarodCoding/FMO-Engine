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

#include "../Data/Data.hpp"
#include "Module.hpp"

namespace Execution {

class Task {
protected:
	std::vector<Task&> dependers;
	volatile uint_fast8_t dependencies;
	std::vector<Data::ExtensionTypeID> extensionOfInterest;
public:
	void *function;
	void * parameter;
	ExecutionPriority priority;
	void run();
	void addDependency(Task&);
	std::vector<Data::ExtensionTypeID> getExtensionOfInterest();
	void registerExtensionsOfInterest(std::vector<Data::ExtensionTypeID>&);
};

} /* namespace Execution */

#endif /* COREENGINE_SRC_EXECUTION_TASK_HPP_ */
