/*
 * System.hpp
 *	
 *  Created on: Sep 16, 2014
 *      Author: Pascal Kuthe
 */

#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_
#include "vector"
#include "deque"

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

	void init();
	virtual void UserInit()=0;
	virtual void TypeInit()=0;
	void DataInit(un);


	void syncData(BaseTypes::Data*);

	int postDataChange(std::string name);
	int postDataChange(unsigned int id );

	int postDataChange(std::string name,uint64_t newSize);
	int postDataChange(unsigned int id ,uint64_t newSize);

	int postDataChange(unsigned int id  ,void * value,uint64_t newSize);
	int postDataChange(std::string name ,void * value,uint64_t newSize);


	template<class T>
	inline int postDataChange(unsigned int id ,T * value){
		if(id>dataSize)return -1;
		BaseTypes::PointerData<T> *tmp = data[id];
		tmp->update(value);
		return 0;
	}
	template<class T>
	inline int postDataChange(std::string name ,T * value){
		return postDataChange(translateToID(name));
	}




	int translateToID(std::string);

	unsigned int  registerDataInterest(std::string name ,BaseTypes::Data *refernce   );
	void registerPossibleChange(unsigned int id	     	    );

	unsigned int getDataOfinterest(BaseTypes::Data **);	//returnValue = pointer to array of Values; return: Size of That array
	unsigned int getPossibleChanges(unsigned int *   );	//returnValue = pointer to array of Values; return: Size of That array

protected:
    	       INode  &parent;
    	   	uint64_t dataSize;
    BaseTypes::Data  **data  ;
    std::deque		   names ;
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
	virtual void syncData(BaseTypes::Data *data);
	virtual int getDataOfinterest(uint64_t *returnValue);	//returnValue = pointer to array of Values; return: Size of That array
	virtual int getPossibleChanges(uint64_t *returnValue);	//returnValue = pointer to array of Values; return: Size of That array
	virtual void postDataChange(BaseTypes::Data *data);
private:
	Universal::Object& parent;

};

#endif /* SYSTEM_HPP_ */
