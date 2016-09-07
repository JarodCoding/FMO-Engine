/*
 * Syncable.cpp
 *
 *  Created on: 22.08.2016
 *      Author: Jarod
 */

#include "Syncable.hpp"
#include <string.h>
namespace Data {
void Syncable::syncAll(){
	Property *tmp;
	while(changesLeft.pop(tmp)){
		sync(tmp);
		delete tmp;
	}

}
void Syncable::notify(Property &changedVersion){

	changesLeft.push((Property *)changedVersion.clone());
}
Syncable::Syncable(): changesLeft(0){

}
} /* namespace Data */
