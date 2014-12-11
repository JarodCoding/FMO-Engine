/*
 * Registry.cpp
 *	
 *  Created on: Sep 17, 2014
 *      Author: Pascal Kuthe
 */
#include "unordered_map"
#include "Registry.hpp"
#include "stdint.h"
#include "string"
namespace Registry{
    std::unordered_map<std::string,uint16_t>* SystemNames;
    std::unordered_map<std::string,uint64_t>* DataNames;
    
    System** systems;

    void setup(uint16_t size){
        SystemNames = new std::unordered_map<std::string,uint16_t>();
        DataNames   = new std::unordered_map<std::string,uint64_t>();
        systems = new System*[size];
    }
	uint16_t registerSystem(std::string name){
	    static uint16_t i;
	    SystemNames->emplace(name,i++);
	    return i;
	}
	uint64_t registerData(std::string name){
	    static uint64_t i;
	    SystemNames->emplace(name,i++);
	    return i;
	}
	uint16_t getSystemID(std::string name){
	    return SystemNames->at(name);
	}
	uint64_t getDataID(uint16_t system,std::string name){
	   return  DataNames->at(name)|((uint64_t )system)<<48;
	}
	uint64_t getLocalDataID(std::string name){
	    return DataNames->at(name);
	}

	
	
uint64_t getDataID(std::string system,std::string name){
		return getDataID(getSystemID(system),name);
	}

}
