/*
 * TaskManager.cpp
 *	
 *  Created on: Aug 31, 2014
 *      Author: Pascal Kuthe
 */
#include "TaskManager.hpp"
#pragma once

//Std includes
#include "stdint.h"
#include "string"
#include "vector"

#include "iostream"

//Boost includes
#include "boost/shared_ptr.hpp"
#include "boost/thread.hpp"


namespace TaskManager{
Task * nulltask= ((Task*)nullptr);
bool isNull(Task& task){
	return &task == nulltask;
}
//Variables
	boost::mutex *							TaskLock		;	// A lock to prevent to prevent async writing to Tasks and FreeIds (only write acces in removeTask() and schedule() so we can just lock both since we need both there anyway)
	std::vector<boost::shared_ptr<Task>> *	Tasks			;	// All tasks who aren't done yet (Those who are done are deleted)
	std::vector<TaskID> *					FreeIds			;	// All Ids who are free (smallest first)
	boost::thread * 						Threads			;	// All Threads.
	const uint8_t							ThreadAmount =	boost::thread::hardware_concurrency()			;
	uint8_t									FreeThreadCount;	// Threads that execute the Taks which have to be finished within the current Thread (last  FreeThreadCount Threads of  Threads are FreeThreads)
	uint8_t									FreeWorkLeft	;	// Amount of Taks left which how have to finish this Tick
	uint8_t									TickWorkLeft	;	// Amount of Taks left which how have to finish this Tick
	work *									SpecialThreads	;	// Special Implementation of code that always needs to be executed by the same Thread (Threads index = Special Threads Index) For expample: Rendering
	uint8_t									SpecialAmount	;
	bool	 								Flag			;	// A collection of Flags
#define TickFlag 		1										// To tell whether or not a Tick update has occurred (started Tick!= Tick)
#define RunningFlag 	2										// If the Engine is Running
#define FwHeavyLoadFlag 4										// If the double amount of Threads is being used for not Thread finishing Tasks
#define TickUpdateFlag  8										// To prevent Threads from doing shit during a Tick update

bool getFlag(uint8_t p_Flag){
	return Flag&p_Flag;
}
void updateFlag(uint8_t p_Flag){
	if(Flag&p_Flag)Flag &= !p_Flag;
	else Flag |= p_Flag;
}
void HeavyFreeTaskLoad(){
	if(!getFlag(FwHeavyLoadFlag)){
		FreeThreadCount = (ThreadAmount-SpecialAmount)/2;
		Flag|= FwHeavyLoadFlag;
	}else{
		FreeThreadCount=(ThreadAmount-SpecialAmount)%2==0?(ThreadAmount-SpecialAmount)/4:(ThreadAmount-SpecialAmount)/3	;
		Flag &= !FwHeavyLoadFlag;
	}


}
//Thread Internal Methods

Task& grapWork(bool highPriorty){
	int i = 1;
	highPriorty++;
	if(highPriorty-1){
		bool highest = 0;
		int highestindex = -1;
		while(i < Tasks->size()){
				Task& tmp = getTask(i);
				if(!(isNull(tmp)||tmp.IsDone()||tmp.IsWorking()||tmp.getDependency()!=-1||tmp.getTicksLeft()>highPriorty)){
					if(tmp.getTicksLeft()>highest){
						highest = tmp.getTicksLeft();
						highestindex = i;
					}
				}
				i++;
			}
		if(highestindex >= 0)
		return getTask(highestindex);
	}else{
		while(i < Tasks->size()){
				Task& tmp = getTask(i);
				if(!(isNull(tmp)||tmp.IsDone()||tmp.IsWorking()||tmp.getDependency()!=-1||tmp.getTicksLeft()>1)){
					return tmp;
				}
				i++;
			}
	}
	return (*nulltask);
}
Task& grapWork(){
	return grapWork(false);
}
//Makes This Thread for Ticks( 1 = Rest of the Current Tick; 2 = Rest of The Current Tick + The Tick Afterwards....)
void Work(uint8_t Ticks){
	bool currentTick = getFlag(TickFlag);
	while(getFlag(RunningFlag) && Ticks>0){
		if(currentTick != getFlag(TickFlag)){
			currentTick = getFlag(TickFlag);
			Ticks--;
			continue;
		}
		while(getFlag(TickUpdateFlag)){
			grapWork(0).run();
		}
		grapWork(Ticks).run();
	}
}
//Makes This Thread a Worker Thread FOREVER!!
void Work(){
	static int Workers;
	int id = Workers++;
	while(getFlag(RunningFlag)){
		while(getFlag(TickUpdateFlag)){
				grapWork(0).run();
		}
		grapWork(FreeThreadCount>id?FreeThreadCount-id+2:0).run();

	}
}


//Called at Startup inits all required thereads.
void init(){
	Tasks 			= new std::vector<boost::shared_ptr<Task>>();
	TaskLock 		= new boost::mutex()						;
	FreeIds			= new std::vector<TaskID>()					;
	Threads			= new boost::thread[ThreadAmount];
	SpecialAmount	= 0;
	//TODO: Interface to register Specials for Systems
	// Sould be something like this:

	//int i = 0;
	//int i2 = 0;
	//while(i < SystemAmount){
	//	i2 = 0;
	//	while(i2 < System[i].getSpecialThreadAmount()){
	// 		Add to list
	//		SpecialAmount++;
	//		i2++;
	//	}
	// 	i++;
	//}
	FreeThreadCount=(ThreadAmount-SpecialAmount)%2==0?(ThreadAmount-SpecialAmount)/4:(ThreadAmount-SpecialAmount)/3	;
	//Starts all the Threads
	int i = 0;
	while(i < SpecialAmount){
		Threads[i] = boost::thread(SpecialThreads[i]);
		i++;
	}
	while(i < ThreadAmount){
		Threads[i] = boost::thread((work)Work);
		i++;
	}
}
void deinit(){
	//TODO stop Threads
	delete Threads;
	delete SpecialThreads;
	delete Tasks;
	delete TaskLock;
	delete FreeIds;

}
//Called by the Thread that reduces TickWorkLeft to 0
void tick(){
	//Doesn't lock because it is already locked by calling method( removeThread() )

	TickWorkLeft = 0;
	int  i = 0;
	while(i < Tasks->size()){
		if(!isNull(getTask(i))&&getTask(i).tick()){
			TickWorkLeft++;
			FreeWorkLeft--;
		}
		i++;
	}
	updateFlag(TickFlag);
	if(getFlag(FwHeavyLoadFlag)!=(FreeWorkLeft>TickWorkLeft)){//No Triggering check needed here because tick() is well only called once per tick (kind'a obvious)
		HeavyFreeTaskLoad();
	}
}

Task & getTask(TaskID Id){
	if(Tasks->at(Id)){
		return *(Tasks->at(Id).get());
	}else{
		return (*nulltask);
	}
}

void removeTask(TaskID id){
    TaskLock->lock();
    if(Tasks->at(id)->getTicksLeft() == 1&&--TickWorkLeft<= 0){
     	tick();
     }else{
    	 FreeWorkLeft--;
     }
      		 HeavyFreeTaskLoad();
    //Destroy The Task
	if(id==Tasks->size()-1){
		Tasks->pop_back();
		//Keep Vector as small as possible
		while(FreeIds->at(FreeIds->size()-1)==Tasks->size()-1&&FreeIds->size()>0){
			FreeIds->pop_back();
			Tasks->pop_back();
		}
	}else{

		Tasks->at(id).reset();

		//Sort the id into the free ids list

	    // We need at least 1 value to sort
	    if(FreeIds->size()==0){
	    	FreeIds->push_back(id);

	    	return;
	    }else

	    //if the id the is the last oner we can save performance and just push it to the end
	    if(id > FreeIds->at(FreeIds->size()-1)){
	    	FreeIds->push_back(id);

	    	return;
	    }else

	    //if the id the is the last one so we can save performance and just insert it at the beginning
	    if(id < FreeIds->at(0)){
		   	FreeIds->insert(FreeIds->begin(),id);
		   	return;
		 }else{
	    //Just like binary search but instead of == we use [i] < x && [i] > x instead of ==
	    int min = 0;
	    int max = FreeIds->size();
	    int current;
	    bool running = true;
	    int i = FreeIds->size();
		while(running&&	/*To prevent invinit loops*/i>= 0){	// Just in case this is buggy...
				current--;
				current /= 2;
				i--;
			if(FreeIds->at(current)<id){
				if(FreeIds->at(current+1)>id){
					FreeIds->insert(FreeIds->begin()+current+1,id);
					running = false;
				}
			}else{
				if(FreeIds->at(current+1)<id){
					FreeIds->insert(FreeIds->begin()+current,id);
					running = false;
				}
			}

		}
		if(i < 0){
			//If we end up here something went horribly wrong! So we are going to report it in all depths. This would be an absouloudly devestating bug wich would break the entire Engine!
			std::cerr << "Insertion of ThreadID "<<id << " into the FreeID list{";
			int i = 0;
			while(i < FreeIds->size()){
				std::cerr << FreeIds->at(i++);
			}
			std::cerr << "} failed. Tmp variables: min{"<<min<<"} max{"<<max<<"} current{"<<current<<"}";
			}
		}

	}

    TaskLock->unlock();

}

void schedule(Task& task){
	//We have to lock here so no over Thread removes a Item while I still read which would lead to a fatal error crashing the entrie engine

	boost::lock_guard<boost::mutex> IdGuard(*TaskLock);

	if(FreeIds->size() > 0){
		Tasks->at(FreeIds->at(0)) = boost::shared_ptr<Task>(new Task(task));
		Tasks->at(FreeIds->at(0))->init(FreeIds->at(0));
		FreeIds->erase(FreeIds->begin());
		return;
	}
	Tasks->push_back(boost::shared_ptr<Task>(new Task(task)));
	Tasks->at(Tasks->size()-1)->init(Tasks->size()-1);

    if(task.getTicksLeft() <= 1){
     	TickWorkLeft++;
     }else{
    	 FreeWorkLeft--;
     }
  		 HeavyFreeTaskLoad();
}


//The Task Class:
Task::Task(TaskID p_dependency,work p_work,TaskID  p_parent,uint16_t p_TicksLeft):TicksLeft(p_TicksLeft),dependency(p_dependency),m_work(p_work),parent(p_parent),dependers(nullptr),dependerAmount(0),WorkLeft(1),Id(0),running(),working(false){}

Task::Task(					   work p_work,TaskID  p_parent,uint16_t p_TicksLeft):TicksLeft(p_TicksLeft),dependency(-1),m_work(p_work),parent(p_parent),dependers(nullptr),dependerAmount(0),WorkLeft(1),Id(0),running(),working(false){}

Task::Task(TaskID p_dependency,work p_work				 ,uint16_t p_TicksLeft):TicksLeft(p_TicksLeft),dependency(p_dependency),m_work(p_work),parent(-1),dependers(nullptr),dependerAmount(0),WorkLeft(1),Id(0),running(),working(false){}

Task::Task(					 work p_work				 ,uint16_t p_TicksLeft):TicksLeft(p_TicksLeft),dependency(-1),m_work(p_work),parent(-1),dependers(nullptr),dependerAmount(0),WorkLeft(1),Id(0),running(),working(false){}




Task::Task(TaskID p_dependency,work p_work,TaskID  p_parent							):TicksLeft(1),dependency(p_dependency),m_work(p_work),parent(p_parent),dependers(nullptr),dependerAmount(0),WorkLeft(1),Id(0),running(),working(false){}

Task::Task(					   work p_work,TaskID  p_parent							):TicksLeft(1),dependency(-1),m_work(p_work),parent(p_parent),dependers(nullptr),dependerAmount(0),WorkLeft(1),Id(0),running(),working(false){}

Task::Task(TaskID p_dependency,work p_work				   							):TicksLeft(1),dependency(p_dependency),m_work(p_work),parent(-1),dependers(nullptr),dependerAmount(0),WorkLeft(1),Id(0),running(),working(false){}

Task::Task(						work p_work				   							):TicksLeft(1),dependency(-1),m_work(p_work),parent(-1),dependers(nullptr),dependerAmount(0),WorkLeft(1),Id(0),running(),working(false){}

Task::Task(Task & task):TicksLeft(task.TicksLeft),dependency(task.dependency),m_work(task.m_work),parent(task.parent),dependers((TaskID *)malloc((std::size_t)task.dependerAmount*sizeof(TaskID))),dependerAmount(task.dependerAmount),WorkLeft(task.WorkLeft),Id(task.Id),running(),working(false){
	int i = 0;
	while(i < dependerAmount){
		dependers[i] = task.dependers[i];
		i++;
	}
}

Task::~Task(){
	if(parent!=-1)getTask(parent).removeChild();
	TaskID tmp;
	while(0 < dependerAmount){
		dependerAmount --;
		tmp = dependers[dependerAmount];
		getTask(tmp).dependencyFinished();
	}
	delete dependers;
}


		//Getters
		int 	Task::IsDone(){
			return WorkLeft*-1+1;	//1 = done  1-WorkLeft = Childs Unfinshed+ 1 if This Task is not done
		}
		int8_t 	Task::getParent(){
			return parent;
		}
		int8_t 	Task::getDependency(){
			return dependency;
		}
		TaskID 	Task::getID(){
			return Id;
		}
		bool 	Task::IsWorking(){
			return working;
		}
		uint16_t Task::getTicksLeft(){
			return TicksLeft;
		}


		//Childs
		void Task::addChild(){
			WorkLeftLock.lock();
			WorkLeft++;
			WorkLeftLock.unlock();
		}
		void Task::removeChild(){
			WorkLeftLock.lock();
			WorkLeft--;
			WorkLeftLock.unlock();
			if(WorkLeft <= 0)removeTask(getID());
		}


		//DependedBy
		void Task::addDepender(TaskID depender){
			dependersLock.lock();
			if(dependerAmount == 0){
				dependers = (TaskID *)malloc(sizeof(TaskID));
				dependers[0] = depender;

			}else{
				dependers = (TaskID *)realloc((void *) dependers,(std::size_t)++dependerAmount*sizeof(TaskID));
			}
			dependerAmount++;
			dependersLock.unlock();
		}

		void Task::dependencyFinished(){
				dependency = -1;
			}



		//INTERNAL METHODS DON'T USE. They are used by the taskmanager and that is the only reason they are public just pretend they aren't there

		//Inits the TaskDes
		void Task::init(TaskID p_Id){
			Id = p_Id;
			if(parent!=-1)getTask(parent).addChild();
			if(dependency!=-1)getTask(dependency).addDepender(getID());
		}
		void Task::run(){
			if(dependency != -1)return;
			if(!running.try_lock())return;//Just for Thread safety;
			working = true;
			m_work();
			WorkLeftLock.lock();
			WorkLeft--;
			WorkLeftLock.unlock();
			if(WorkLeft <= 0)removeTask(getID());
		}
		bool Task::tick(){
			if(--TicksLeft==1)return true;
			return false;
		}

}
//End Of The Task Class


//I know you didn't expect it here but it needs to be here for Taskmanaging
int main(){

}
