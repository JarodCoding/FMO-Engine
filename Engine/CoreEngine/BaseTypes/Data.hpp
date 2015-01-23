/*
 * Data.hpp
 *	
 *  Created on: Sep 14, 2014
 *      Author: Pascal Kuthe
 */

#include "string"
#include "stdint.h"
#include "string"
#include <algorithm>
#include <memory.h>
#ifndef DATA_HPP_
#define DATA_HPP_
namespace BaseTypes{
class Data {
public:

	 Data(uint64_t localID,uint16_t systemID);

	uint64_t getlocalId();
	uint64_t getGlobalID();
	uint16_t getSystem();
	virtual void sync(Data *) = 0;
	bool operator ==(const Data& d) const;
private:
	uint64_t id;
	uint16_t system;
};
//Use this for normal variabels (not pointer and they have to be on the heap)
template<class T>
class NormalData: public Data{
public:
	NormalData(T &data,uint64_t localID,uint16_t systemID);
	T &getData();
protected:
	T &data;
};
//Use this if you used new T to init your variable (so basically if you have a pointer) but don'T use this if you intend to use the pointer for more than just a reference to one element on the heap
template<class T>
class PointerData: public Data{

public:
	PointerData(T *data, uint64_t localID,uint16_t systemID);
	virtual ~PointerData();
	T *getData();
	void update(T* newLocation);
protected:
	T *data;
};
//Use this if you want to do all the memory managment yourself
class CustomData: public PointerData<void>{
public:
	CustomData(void *data,uint64_t size, uint64_t localID,uint16_t systemID);
	void update(void *newLocation,uint64_t newSize);
	void update(uint64_t newSize);
	uint64_t getSize();					//in Bytes
protected:
	uint64_t size;						//in Bytes

};
//Use this if you want to do all the memory management yourself but want the convenience of a few extras like garbage collection.
class ManagedCustomData: public CustomData{
public:
	ManagedCustomData(void *data,uint64_t size, uint64_t localID,uint16_t systemID);
	virtual ~ManagedCustomData();

};

}
#endif /* DATA_HPP_ */
