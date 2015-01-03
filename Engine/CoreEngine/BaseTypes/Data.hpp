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

	 Data(uint64_t localID,uint16_t systemID,void * data,uint datasize);


	~Data();
    void updateData(uint64_t datasize);
	void updateData(void *newData,uint64_t datasize);

	uint64_t getlocalId();
	uint64_t getGlobalID();
	void* getData();
	uint16_t getSystem();
	//wheater the value has been changed since the kast hasChanged() call
	bool getHasChanged();
	//wheater the value has been changed since the kast hasChanged() call
	bool hasChanged();
	bool operator ==(const Data& d) const;
private:
	uint64_t id;
	uint16_t system;
	uint64_t size;
	bool changed;
	void * data;
};
}
#endif /* DATA_HPP_ */
