/*
 * Registry.cpp
 *	
 *  Created on: Sep 17, 2014
 *      Author: Pascal Kuthe
 */
#include "unorderedmap"
namespace Registry{
    std::unorderedmap<std::string,uint16_t>* SystemNames;
    std::unorderedmap<std::string,uint64_t>* DataNames;
    
    System* systems;

    void setup(){
        SystemNames = new std::unorderedmap<std::string,uint16_t>();
        DataNames   = new std::unorderedmap<std::string,uint64_t>();#
        system = new System();
    }
	uint16_t registerSystem(std::string name){
	    static uint16_t i;
	    Systems->put(name,i++);
	}
	uint64_t registerData(std::string name){
	    static uint64_t i;
	    Names->put(name,i++)
	}
	uint16_t getSystemID(std::string name){
	    return SystemNames.at(name);
	}
	uint64_t getDataID(uint16_t system,std::string name){
	    DataNames.at(name)|((uint64_t )system)<<48
	}
	uint64_t getLocalDataID(std::string name){
	    return DataNames.at(name);
	}

	
	
uint64_t getDataID(std::string system,std::string name){
		return getDataID(getSystemID(system),name);
	}

}
