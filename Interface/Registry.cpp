/*
 * Registry.cpp
 *	
 *  Created on: Sep 17, 2014
 *      Author: Pascal Kuthe
 */

namespace Registry{

uint64_t getDataID(std::string system,std::string name){
		return getDataID(getSystemID(system),name);
	}
}
