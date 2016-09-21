/*
 * CallbackFuture.cpp
 *
 *  Created on: 18.09.2016
 *      Author: Jarod
 */

#include "CallbackFuture.hpp"

namespace Execution {
namespace Util{
CallbackFuture::CallbackFuture():callbackFunction(nullptr),data(nullptr),asyncCallback(false){}
CallbackFuture::CallbackFuture(void(*p_callbackFunction)()):callbackFunction(p_callbackFunction),data(nullptr),asyncCallback(false){}
CallbackFuture::CallbackFuture(void(*p_callbackFunction)(),bool p_asyncCallback):callbackFunction(p_callbackFunction),data(nullptr),asyncCallback(p_asyncCallback){}
CallbackFuture::CallbackFuture(bool p_asyncCallback):callbackFunction(nullptr),data(nullptr),asyncCallback(p_asyncCallback){}

CallbackFuture::~CallbackFuture() {
	// TODO Auto-generated destructor stub
}
void CallbackFuture::ready(){
	if(asyncCallback)Execution::TaskManager::queueTask(callbackFunction,2);
	else callbackFunction();

}
}
} /* namespace Data */
