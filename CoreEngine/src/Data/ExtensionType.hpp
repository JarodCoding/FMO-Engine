/*
 * ExtensionType.hpp
 *
 *  Created on: 22.08.2016
 *      Author: Jarod
 */

#ifndef COREENGINE_SRC_DATA_EXTENSIONTYPE_HPP_
#define COREENGINE_SRC_DATA_EXTENSIONTYPE_HPP_
#include <stdint.h>

#include "Data.hpp"
namespace Data{
	typedef uint_fast32_t ExtensionTypeID;
	typedef Data::Extension *(*ExtensionInitFunction)(Universal::Extension);

	namespace ExtensionType{
	ExtensionTypeID registerExtensionType(ExtensionInitFunction,std::string);
	ExtensionInitFunction getInitFunction(ExtensionTypeID id);
	ExtensionTypeID getRuntimeID(std::string);

}
}





#endif /* COREENGINE_SRC_DATA_EXTENSIONTYPE_HPP_ */
