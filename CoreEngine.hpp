/*
 * CoreEngine.hpp
 *	
 *  Created on: Aug 29, 2014
 *      Author: Pascal Kuthe
 */

#include "Display.hpp"
#include "GL/glew.h"
#include "string"
#include "SDL2/SDL.h"

#ifndef COREENGINE_HPP_
#define COREENGINE_HPP_

enum GameState{EXIT,RUNNING,CRASH,SETUP};

void crash(std::string error);
void launchTask();


#endif /* COREENGINE_HPP_ */
