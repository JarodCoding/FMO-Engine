/*
 * CallbackFuture.h
 *
 *  Created on: 18.09.2016
 *      Author: Jarod
 */

#ifndef COREENGINE_SRC_EXECUTION_UTIL_CALLBACKFUTURE_HPP_
#define COREENGINE_SRC_EXECUTION_UTIL_CALLBACKFUTURE_HPP_

namespace Execution {
namespace Util{

class CallbackFuture {
public:
	CallbackFuture();
	CallbackFuture(void(*p_callbackFunction)());
	CallbackFuture(void(*p_callbackFunction)(),bool p_asyncCallback);
	CallbackFuture(bool p_asyncCallback);

	void *data;
	bool asyncCallback;
	void(*callbackFunction)();
	void ready();
};
}
} /* namespace Execution */

#endif /* COREENGINE_SRC_EXECUTION_UTIL_CALLBACKFUTURE_HPP_ */
