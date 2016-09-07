/*
 * Property.h
 *
 *  Created on: 31 Aug 2016
 *      Author: Jarod
 */

#ifndef COREENGINE_SRC_DATA_PROPERTY_HPP_
#define COREENGINE_SRC_DATA_PROPERTY_HPP_
#include "Clonable.hpp"
#include "string"
namespace Data{
	extern char PropertyTypeName[];
	class Property: public Clonable{
	public:
		Property(std::string,Clonable *);
		virtual ~Property();
		std::string name;
		Clonable * data;
		virtual Clonable *clone();
		virtual void clone(Clonable *dest);
		std::string getTypeName();

	};
}
#endif /* COREENGINE_SRC_DATA_PROPERTY_HPP_ */
