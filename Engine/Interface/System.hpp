/*
 * System.hpp
 *	
 *  Created on: Sep 16, 2014
 *      Author: Pascal Kuthe
 */

#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_
#include "vector"
#include "../CoreEngine/BaseTypes/Data.hpp"
#include "../CoreEngine/Managers/TaskManager.hpp"
namespace Universal{
	class Object;
	class Scene;
}
class IObject;
class ISystem;
class INode{
public:
	INode(INode &parent);
	virtual ~INode();

	virtual void init()=0;

	void syncData(BaseTypes::Data*);

	template<typename T>
	int postDataChange(std::string name,T &value);
	int postDataChange(std::string name,uint64_t newSize);
	int postDataChange(unsigned int id,uint64_t newSize);
	int postDataChange(unsigned int id,void * value,uint64_t newSize);
	int postDataChange(std::string name ,void * value,uint64_t newSize);



	int translateToID(std::string);

	template<typename T>
	unsigned int  registerDataInterest(std::string name ,T &reference   );
			 int  registerDataInterest(std::string name ,void *reference);
			 void registerPossibleChange(unsigned int id	     	    );

	unsigned int getDataOfinterest(BaseTypes::Data **);	//returnValue = pointer to array of Values; return: Size of That array
	unsigned int getPossibleChanges(unsigned int *   );	//returnValue = pointer to array of Values; return: Size of That array

protected:
    	       INode  &parent;
    BaseTypes::Data  **data  ;
    std::string 	  *names ;

};
class IScene: public INode{
	friend class ISystem;
public:
	IScene(Universal::Scene& p_parent);
	virtual ~IScene();
	virtual IObject createObjectExtension(Universal::Object& object);




private:
	std::vector<IObject> children;
	Universal::Scene& parent;
	BaseTypes::Data **data;
};

class ISystem{
public:
	ISystem();
	virtual ~ISystem();
	virtual IScene* createSceneExtension(Universal::Scene& scene) ;
	virtual bool isDone(); //Called at an end of a tick to check if the Systems Data can be synced
	virtual uint32_t getDelay();//Gets The Delay between the execution of this System in ticks;
	virtual void init();
private:
	IScene* scene;
	TaskManager::work SystemTask;
};

class IObject{
	friend class IScene;
protected:
	IObject(Universal::Object& parent);

public:
	virtual ~ IObject();
	virtual void syncData(BaseTypes::Data data);
	virtual int getDataOfinterest(uint64_t *returnValue);	//returnValue = pointer to array of Values; return: Size of That array
	virtual int getPossibleChanges(uint64_t *returnValue);	//returnValue = pointer to array of Values; return: Size of That array
	virtual void postDataChange(BaseTypes::Data data);
private:
	Universal::Object& parent;

};

#endif /* SYSTEM_HPP_ */
