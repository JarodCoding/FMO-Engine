/*
 * Module.h
 *
 *  Created on: 22.08.2016
 *      Author: JarodCoding
 */

#ifndef COREENGINE_SRC_EXECUTION_MODULE_HPP_
#define COREENGINE_SRC_EXECUTION_MODULE_HPP_
namespace Execution {
	typedef uint8_t ModuleID;
	class Module;
}

namespace Execution {

class Module {
public:
	Module();
	virtual ~Module();
};

} /* namespace Execution */

#endif /* COREENGINE_SRC_EXECUTION_MODULE_HPP_ */
