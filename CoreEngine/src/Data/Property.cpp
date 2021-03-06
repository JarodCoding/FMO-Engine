/*
 * Property.cpp
 *
 *  Created on: 31 Aug 2016
 *      Author: Jarod
 */

#include "Property.hpp"
#include "string"
#include <cstring>
namespace Data{
#define PropertyTypeName "PropertyTypeName"
	Property::Property(std::string p_name,Clonable * p_data):name(p_name),data(p_data) {

	}

	Property::~Property() {
		delete data;
	}
	Clonable *Property::clone(){
		return new Property(name,data->clone());
	}
	void Property::clone(Clonable *dest){
		if(dest->getTypeName().compare(dest->getTypeName()))return;
		((Property *)dest)->name = name;
		((Property *)dest)->data = data->clone();

	}
	std::string Property::getTypeName(){
		return PropertyTypeName;
	}
}
