/*
 * ClonableWrapper.cpp
 *
 *  Created on: 05.09.2016
 *      Author: Jarod
 */

#include "ClonableWrapper.hpp"

namespace Data {


template <class T> ClonableWrapper<T>::ClonableWrapper(T data) {
	upate(data);
}

template <class T> ClonableWrapper<T>::~ClonableWrapper() {
	// TODO Auto-generated destructor stub
}
template <class T> void ClonableWrapper<T>::upate(T data){
	this ->data = data;
}
template <class T> void ClonableWrapper<T>::clone(Clonable *cdest){
	if(!strcmp(cdest->getTypeName(),getTypeName()))return;
	ClonableWrapper *dest = (ClonableWrapper *) cdest;
	dest->data = T(data);
}
template <class T> char* ClonableWrapper<T>::getTypeName(){
	return "ClonableWrapper";
}
template <class T> Clonable *ClonableWrapper<T>::ClonableWrapper::clone(){
	return new ClonableWrapper(T(data));
}


} /* namespace Data */
