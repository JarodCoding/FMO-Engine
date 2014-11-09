/*
 * Registry.hpp
 *	
 *  Created on: Sep 17, 2014
 *      Author: Pascal Kuthe
 */

#ifndef REGISTRY_HPP_
#define REGISTRY_HPP_
#include "string"
#include "System.hpp"
namespace Registry{
	uint32_t registerSystem(std::string name);
	uint64_t registerData(uint32_t system, std::string name);
	uint64_t registerData(std::string system, std::string name);

	void unregisterSystem(uint32_t system);
	void unregisterData(uint64_t data);
	void unregisterData(std::string system, std::string name);

	uint32_t getSystemID(std::string name);
	uint64_t getDataID(uint32_t system,std::string name);
	uint64_t getDataID(std::string system,std::string name);
}




#endif /* REGISTRY_HPP_ */
