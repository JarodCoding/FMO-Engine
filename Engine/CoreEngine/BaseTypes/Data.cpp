#include "Data.hpp"
#include "stdint.h"
namespace BaseTypes{
    //Initaliazing of Data:
        Data::Data(uint64_t localID,uint16_t systemID,void * data,uint datasize): id(localID),system(systemID),size(datasize),changed(false),data(malloc(datasize)){
         	memcpy(this->data, data, datasize);
        }
        
        Data::~Data(){
		    free(data);
	    }
        void Data::updateData(uint64_t datasize){
            size = datasize;
        }
        void Data::updateData(void *newData,uint64_t datasize){
	        if(newData!=data)
		        free( data);
		    data = malloc(datasize);
	        memcpy(this->data, data, datasize);
	    }

        uint64_t Data::getlocalId(){
		    return id;
	    }
        uint64_t Data::getGlobalID(){
		    uint64_t tmp = getlocalId();
            tmp = tmp<<16;
            tmp =  tmp>>16;
            tmp|=(((uint64_t) system)<<48);
            return tmp;
	    
	    }
        void* Data::getData(){
		    return data;
	    }
        uint16_t Data::getSystem(){
		    return system;
	    }
        bool Data::getHasChanged(){
	        return changed;
	    }
        bool Data::hasChanged(){
	        bool tmp = getHasChanged();
	        changed = false;
		    return tmp;
	    }
        bool Data::operator ==(const Data& d) const{
		    return d.system == system && d.id == id;
	    }
	}


