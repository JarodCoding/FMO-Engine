//TODO: Move to Rendering System

/*
 * Display.hpp

 *	
 *  Created on: Aug 30, 2014
 *      Author: Pascal Kuthe
 */

#include "SDL2/SDL.h"
#include "GL/glew.h"
#include "Config.hpp"
#include "Info.hpp"
#include "iostream"

#ifndef DISPLAY_HPP_
#define DISPLAY_HPP_


namespace Display{

SDL_Window *window;
SDL_GLContext GraphicsContext;

bool inline Init(){
	//init SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	//Set OpenGL Settings
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
	//Create The Window
	window = SDL_CreateWindow(GameName,0,0,Config::Video::resolutionWidth,Config::Video::resolutionHeight,SDL_WINDOW_OPENGL|SDL_WINDOW_FULLSCREEN);
	GraphicsContext = SDL_GL_CreateContext(window);
	GLenum status = glewInit();
	glClearColor(0,0,0,1);

	if(status != GLEW_OK){
		std::cerr << "GLEW: Init failed";
		return false;
	}
	return true;
}

void inline Destoroy(){
	SDL_GL_DeleteContext(GraphicsContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void inline Update(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	SDL_GL_SwapWindow(window);

}
}



#endif /* DISPLAY_HPP_ */
