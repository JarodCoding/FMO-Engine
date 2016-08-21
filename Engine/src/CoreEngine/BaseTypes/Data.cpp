#include "Data.hpp"
#include "stdint.h"
namespace BaseTypes{
    //Data:
        Data::Data(uint64_t localID,uint16_t systemID): id(localID),system(systemID){
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
        uint16_t Data::getSystem(){
		    return system;
	    }
        bool Data::operator ==(const Data& d) const{
		    return d.system == system && d.id == id;
        }

   //NormalData:
        template<class T>
    	NormalData<T>::NormalData(T &data,uint64_t localID,uint16_t systemID):Data(localID,systemID),data(data){

    	}
        template<class T>
    	T &NormalData<T>::getData(){
    		return data;
    	}
        template<class T>
        virtual void NormalData<T>::sync(Data *src){
        	if(src->system != this->system&&src->id!=this->id)return;
        	NormalData<T> *tmp = src;
            memcpy(&data,&tmp->getData(),sizeof(T));
        }

        template<class T>
    	PointerData<T>::PointerData(T *data, uint64_t localID,uint16_t systemID):Data(localID,systemID),data(data){

        }
        template<class T>
        T* PointerData<T>::getData(){
        	return data;
        }

        template<class T>
        void PointerData<T>::update(T* newLocation){
        	data = newLocation;
        }
        template<class T>
        virtual void PointerData<T>::sync(Data *src){
        	if(src->system != this->system&&src->id!=this->id)return;
        	PointerData<T> *tmp = src;
        	memcpy(data,tmp->getData(),sizeof(T));
        }

        CustomData::CustomData(void *data,uint64_t size, uint64_t localID,uint16_t systemID):PointerData(data,localID,systemID),size(size){

        }


        uint64_t CustomData::getSize(){
        	return size;
        }
        void CustomData::update(uint64_t newSize){
        	size = newSize;
        }
    	void CustomData::update(void* newLocation,uint64_t newSize){
    		data = newLocation;
    		size = newSize;
    	}

        ManagedCustomData::ManagedCustomData(void *data,uint64_t size, uint64_t localID,uint16_t systemID):CustomData(data,size,localID,systemID){

        }
        ManagedCustomData::~ManagedCustomData(){
        	delete data;
        }



}


