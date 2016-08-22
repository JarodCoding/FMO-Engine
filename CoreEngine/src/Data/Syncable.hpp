/*
 * Syncable.hpp
 *
 *  Created on: 22.08.2016
 *      Author: Jarod
 */

#ifndef COREENGINE_SRC_DATA_SYNCABLE_HPP_
#define COREENGINE_SRC_DATA_SYNCABLE_HPP_
#include "boost/lockfree/queue"
namespace Data {

class Syncable: public Clonable{
public:
	Syncable();
	virtual ~Syncable();
	virtual void sync(Syncable&) = 0;
	virtual void syncAll(Syncable&) ;
	virtual void notify(Syncable&) ;

protected:
	boost::lockfree::queue<Syncable&> changesLeft;
};

} /* namespace Data */

#endif /* COREENGINE_SRC_DATA_SYNCABLE_HPP_ */
