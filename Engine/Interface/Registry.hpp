/*
 * Registry.hpp
 *	
 *  Created on: Sep 17, 2014
 *      Author: Pascal Kuthe
 */

#ifndef REGISTRY_HPP_
#define REGISTRY_HPP_
#include "string"
namespace Registry{
	uint16_t registerSystem(std::string name);
	uint64_t registerData(uint16_t system, std::string name);
	uint64_t registerData(std::string system, std::string name);
	uint64_t registerData(std::string name);

	void unregisterSystem(uint16_t system);
	void unregisterData(uint64_t data);
	void unregisterData(uint16_t id, std::string name);
	void unregisterData(std::string system, std::string name);

	uint16_t getSystemID(std::string name);
	uint64_t getDataID(uint16_t system,std::string name);
	uint64_t getLocalDataID(std::string name);
	
	class System;
	System* getSystem(uint16_t id);
	System* getSystem(std::string name);
	
}




#endif /* REGISTRY_HPP_ */
