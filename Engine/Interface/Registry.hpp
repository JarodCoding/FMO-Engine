/*
 * Registry.hpp
 *	
 *  Created on: Sep 17, 2014
 *      Author: Pascal Kuthe
 */

#ifndef REGISTRY_HPP_
#define REGISTRY_HPP_
#include "string"

class ISystem;
namespace Registry{
	uint16_t registerSystem(std::string name);
	uint64_t registerData(uint16_t system, std::string name);
	uint64_t registerData(std::string system, std::string name);
	uint64_t registerData(std::string name);

	void unregisterSystem(std::string name);	//Only Removes Link but this method shouldn't be called in the first place
	void unregisterData(std::string name);		//Only Removes Link but this method shouldn't be called in the first place

	uint16_t getSystemID(std::string name);
	uint64_t getDataID(uint16_t system,std::string name);
	uint64_t getLocalDataID(std::string name);
	
	ISystem* getSystem(uint16_t id);
	ISystem* getSystem(std::string name);
	
}




#endif /* REGISTRY_HPP_ */
