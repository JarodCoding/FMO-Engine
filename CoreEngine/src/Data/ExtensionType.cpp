/*
 * ExtensionType.cpp
 *
 *  Created on: 22.08.2016
 *      Author: Jarod Kuthe
 */
#include "ExtensionType.hpp"

#include "Data.hpp"
#include "vector"
#include "string"


namespace Data{
	namespace ExtensionType{
		std::vector<ExtensionInitFunction> ExtensionTypes = std::vector<ExtensionInitFunction>();
		std::vector<std::string> names = std::vector<std::string>();

		ExtensionTypeID registerExtensionType(ExtensionInitFunction func,std::string name){
			ExtensionTypes.push_back(func);
			return ExtensionTypes.size()-1;
		}
		ExtensionInitFunction getInitFunction(ExtensionTypeID id){
			return ExtensionTypes[id];
		}
		ExtensionTypeID getRuntimeID(std::string name){
			unsigned int i = 0;
			while(i < names.size()){
				if(names[i].compare(name))return i;
				i++;
			}
			return -1;
		}

		}
	}




