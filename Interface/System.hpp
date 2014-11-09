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
class IScene{
	friend class ISystem;
protected:
	IScene(Universal::Scene& parent);
public:
	virtual ~IScene();
	virtual IObject createObjectExtension(Universal::Object& object);
	virtual void syncData(BaseTypes::Data data);
	virtual int getDataOfinterest(uint64_t *returnValue);	//returnValue = pointer to array of Values; return: Size of That array
	virtual int getPossibleChanges(uint64_t *returnValue);	//returnValue = pointer to array of Values; return: Size of That array
	virtual void postDataChange(BaseTypes::Data data);


private:
	std::vector<IObject> Extensions;
	Universal::Scene& parent;
};

class ISystem{
public:
	ISystem();
	virtual ~ISystem();
	virtual IScene createSceneExtension(Universal::Scene& scene);
	virtual bool isDone(); //Called at an end of a tick to check if the Systems Data can be synced
	virtual uint32_t getDelay();//Gets The Delay between the execution of this System in ticks;
	virtual void init();
private:
	IScene scene;
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
