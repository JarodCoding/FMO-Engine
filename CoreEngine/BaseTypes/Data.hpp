/*
 * Data.hpp
 *	
 *  Created on: Sep 14, 2014
 *      Author: Pascal Kuthe
 */
#include "string"
#include "stdint-gcc.h"
#include "boost/any.hpp"
#include "string"
#ifndef DATA_HPP_
#define DATA_HPP_
namespace BaseTypes{
class Data {
public:

	inline Data(uint64_t id,void * data,uint datasize): id(id),data(malloc(datasize)){
		memcpy(this->data, data, datasize);
	}

//	inline Data(Data& data): id(data.getId()),data(data.getData()){}


	inline ~Data(){
		delete data;
	}

	inline void updateData(void *newData,uint datasize){
		delete data;
		data = malloc(datasize);
		memcpy(this->data, data, datasize);
	}

	inline uint64_t getId(){
		return id;
	}

	inline void* getData(){
		return data;
	}
	inline uint32_t getSystem(){
		return id >> 32;
	}
	inline uint32_t getChange(){
		return (id << 32) >> 32;
	}
	inline bool operator ==(const Data& d) const{
		return d.id == id;
	}
private:
	uint64_t id;
	void * data;
};
}
#endif /* DATA_HPP_ */
