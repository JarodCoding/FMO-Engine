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
	ClonableWrapper(T data);
	virtual ~ClonableWrapper();
	void upate(T data);
	virtual Clonable *clone();
	virtual void clone(Clonable *dest);
	char* getTypeName();
private:

};

} /* namespace Data */

#endif /* COREENGINE_SRC_DATA_CLONABLEWRAPPER_HPP_ */
