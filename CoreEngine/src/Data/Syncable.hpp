/*
 * Syncable.hpp
 *
 *  Created on: 22.08.2016
 *      Author: Jarod
 */

#ifndef COREENGINE_SRC_DATA_SYNCABLE_HPP_
#define COREENGINE_SRC_DATA_SYNCABLE_HPP_
#include "boost/lockfree/queue.hpp"
#include "Clonable.hpp"
#include "Property.hpp"
namespace Data {

class Syncable: public Clonable{
public:
	Syncable();
	virtual void sync(Property *) = 0;
	void syncAll() ;
	void notify(Property&) ;

protected:
	boost::lockfree::queue<Property *> changesLeft;
};



} /* namespace Data */

#endif /* COREENGINE_SRC_DATA_SYNCABLE_HPP_ */
