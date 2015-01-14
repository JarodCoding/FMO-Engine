/*
 * TaskManager.hpp
 *	
 *  Created on: Aug 30, 2014
 *      Author: Pascal Kuthe
 */
#include "boost/thread.hpp"
#include "boost/thread/mutex.hpp"

#include <stdint.h>

#ifndef TASKMANAGER_HPP_
#define TASKMANAGER_HPP_



namespace TaskManager{

typedef uint8_t TaskID;
typedef void (*work)();

	class Task {
	public:
		Task(TaskID p_dependency,work p_work,TaskID  p_parent,uint16_t p_TicksLeft);
		Task(					 work p_work,TaskID  p_parent,uint16_t p_TicksLeft);
		Task(TaskID p_dependency,work p_work				 ,uint16_t p_TicksLeft);
		Task(					 work p_work				 ,uint16_t p_TicksLeft);

		Task(TaskID p_dependency,work p_work,TaskID  p_parent);
		Task(					 work p_work,TaskID  p_parent);
		Task(TaskID p_dependency,work p_work				 );
		Task(					 work p_work				 );
		Task(Task &task);

		virtual ~Task();

		//Getters
		int 	 IsDone()			;
		int8_t 	 getParent()		;
		int8_t 	 getDependency()	;
		TaskID 	 getID()			;
		uint16_t getTicksLeft()		;
		bool 	 IsWorking()		;



		//INTERNAL METHODS DON'T USE. They are used by the taskmanager and that is the only reason they are public just pretend they aren't ther

		//Inits the Task
		void init(TaskID Id);
		void run();
		bool tick();


	private:
		uint16_t TicksLeft; //How Many ticks(Main Loop Run Throughs) this has left until it has to be finsihed
		int16_t	 dependency;
		work 	 m_work;
		int16_t	 parent;
		boost::mutex dependersLock;
		TaskID * dependers;
		uint16_t dependerAmount;
		boost::mutex WorkLeftLock;
		uint16_t WorkLeft;
		TaskID	 Id;
		boost::mutex running;		// Theoretical not needed but it is for security in case a second Thread grabs the Task before it can be marked as working
		bool working;

		void removeChild()	;
		void addChild()		;


		void addDepender(TaskID depender);

		void dependencyFinished();

	};



	//Declare Methods;

	void tick();

	void schedule(Task task);

	Task& getTask(TaskID Id);
}




#endif /* TASKMANAGER_HPP_ */
