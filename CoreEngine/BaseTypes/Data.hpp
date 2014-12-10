/*
 * Data.hpp
 *	
 *  Created on: Sep 14, 2014
 *      Author: Pascal Kuthe
 */

#include "string"
#include "stdint-gcc.h"
#include "string"
#ifndef DATA_HPP_
#define DATA_HPP_
namespace BaseTypes{
class Data {
public:

	inline Data(uint64_t localID,uint16_t systemID,void * data,uint datasize): id(id),system(systemID),size(datasize),changed(false),data(malloc(datasize)){
		memcpy(this->data, data, datasize);
	}

//	inline Data(Data& data): id(data.getId()),data(data.getData()){}


	inline ~Data(){
		delete data;
	}
    inline void updateData(uint64_t datasize){
        size = datasize;
    }
	inline void updateData(void *newData,uint64_t datasize){
	    if(newData!=data){
		delete data;
		data = malloc(datasize);
	    memcpy(this->data, data, datasize);
	    }
	    updateData(datasize)
	}

	inline uint64_t getlocalId(){
		return id;
	}
	inline uint64_t getGlobalID(){
        int tmp = getlocalId();
        tmp<<16;
        tmp>>16;
        tmp|=(system>>48)
        return tmp;
	    
	}
	inline void* getData(){
		return data;
	}
	inline uint16_t getSystem(){
		return system;
	}
	//wheater the value has been changed since the kast hasChanged() call
	inline bool getHasChanged(){
	    return changed;
	}
	//wheater the value has been changed since the kast hasChanged() call
	inline bool hasChanged(){
	    bool tmp = getHasChanged();
	    changed = false;
		return tmp;
	}
	inline bool operator ==(const Data& d) const{
		return d.getGlobalID() == getGlobalID();
	}
private:
	uint64_t id;
	uint16_t system;
	uint64_t size;
	bool changed;
	void * data;
};
}
#endif /* DATA_HPP_ */
