/*
 * ExtensionType.cpp
 *
 *  Created on: 22.08.2016
 *      Author: Jarod Kuthe
 */
#include "ExtensionType.hpp"
#include "vector"
#include "Data.hpp"


namespace Data{
	namespace ExtensionType{
		std::vector<ExtensionInitFunction> ExtensionTypes = std::vector<ExtensionInitFunction>();

		ExtensionTypeID registerExtensionType(ExtensionInitFunction func){
			ExtensionTypes.push_back(func);
			return ExtensionTypes.size()-1;
		}
		ExtensionInitFunction getInitFunction(ExtensionTypeID id){
			return ExtensionTypes[id];
			}

		}
	}




