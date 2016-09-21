/*
 * Task.cpp
 *
 *  Created on: 22.08.2016
 *      Author: Jarod
 */

#include "Task.hpp"

namespace Execution {
	void Task::run(){
		if(dependencies != 0)return;
		running = true;
		//run
		if(parameter == nullptr)
			reinterpret_cast<void(*)()>(function)();
		else
			return reinterpret_cast<void(*)(void *)>(function)(parameter);
		//finish
		for(Task& t:dependers){
			if((--t.dependencies)==0)Execution::TaskManager::queueTask(t);
		}
		running = false;
	}
	void Task::addDependency(Task& t){
		if(running)
			#ifdef DEBUG throw "Task is Already Running can't add dependencies";
			#else
			return;
			#endif;
		t.dependers.push(this);
		dependencies++;
	}
	void Task::addDependency(Execution::Util::CallbackFuture t){
		()
		t.callbackFunction(;
		dependencies++;
	}
	void Task::registerExtensionsOfInterest(std::vector<Data::ExtensionTypeID>& eof){
		std::sort(eof.begin(),eof.end());
		extensionOfInterest = eof;
	}
	std::vector<Data::ExtensionTypeID>& Task::getExtensionOfInterest(){
		return extensionOfInterest;
	}
} /* namespace Execution */
