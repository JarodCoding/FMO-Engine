/*
 * Clonable.h
 *
 *  Created on: 22.08.2016
 *      Author: Jarod
 */

#ifndef COREENGINE_SRC_DATA_CLONABLE_HPP_
#define COREENGINE_SRC_DATA_CLONABLE_HPP_

namespace Data {

class Clonable {
public:
	virtual Clonable& clone() = 0;
	virtual char* getTypeName() = 0;
};

} /* namespace Data */

#endif /* COREENGINE_SRC_DATA_CLONABLE_HPP_ */
