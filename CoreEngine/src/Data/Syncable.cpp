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
	Syncable *tmp;
	while(changesLeft.pop(tmp)){
		sync(*tmp);
	}

}
void Syncable::notify(Clonable &changedVersion){
	changesLeft.push(changedVersion.clone());
}
Syncable::Syncable(): changesLeft(){

}
} /* namespace Data */
