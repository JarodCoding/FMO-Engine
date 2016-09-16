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
		//run
		if(parameter == nullptr)
			reinterpret_cast<void(*)()>(function)();
		else
			return reinterpret_cast<void(*)(void *)>(function)(parameter);
		//finish
		for(Task& t:dependers){
			if(__sync_sub_and_fetch(&t.dependencies,1)==0);//Add t to TaskManager
		}
	}
	void Task::addDependency(Task& t){
		t.dependers.push_back(*this);
		__sync_add_and_fetch(&dependencies,1);
	}
	void Task::registerExtensionsOfInterest(std::vector<Data::ExtensionTypeID>& eof){
		std::sort(eof.begin(),eof.end());
		extensionOfInterest = eof;
	}
	std::vector<Data::ExtensionTypeID> Task::getExtensionOfInterest(){
		return extensionOfInterest;
	}
} /* namespace Execution */
