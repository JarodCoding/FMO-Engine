/*
 * Clonable.h
 *
 *  Created on: 22.08.2016
 *      Author: Jarod
 */

#ifndef COREENGINE_SRC_DATA_CLONABLE_HPP_
#define COREENGINE_SRC_DATA_CLONABLE_HPP_
#include "string"
namespace Data {

class Clonable {
public:
	virtual ~Clonable() = default;
	virtual Clonable *clone() = 0;
	virtual void clone(Clonable *dest) = 0;
	virtual std::string getTypeName() = 0;
};

} /* namespace Data */

#endif /* COREENGINE_SRC_DATA_CLONABLE_HPP_ */
