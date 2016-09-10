/*
 * ClonableWrapper.hpp
 *
 *  Created on: 05.09.2016
 *      Author: Jarod
 */

#ifndef COREENGINE_SRC_DATA_CLONABLEWRAPPER_HPP_
#define COREENGINE_SRC_DATA_CLONABLEWRAPPER_HPP_

#include "Clonable.hpp"

namespace Data {

template <class T> class ClonableWrapper: public Clonable {
public:
	T data;
	inline ClonableWrapper(T p_data):data(p_data){

	}
	inline ~ClonableWrapper(){

	}
	inline void upate(T p_data){
		data = p_data;
	}
	inline Clonable *clone(){
		return new ClonableWrapper(T(data));

	}
	inline void clone(Clonable *cdest){
		if(cdest->getTypeName().compare(getTypeName()))return;
		ClonableWrapper *dest = (ClonableWrapper *) cdest;
		dest->data = T(data);
	}
	inline std::string getTypeName(){
		return "ClonableWrapper";
	}
private:

};

} /* namespace Data */
#endif
