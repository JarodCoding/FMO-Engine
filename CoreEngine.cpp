/*
 * CoreEngine.cpp
 *
 *  Created on: Aug 29, 2014
 *      Author: Pascal Kuthe
 */

#include "CoreEngine.hpp"




GameState state = SETUP;

void crash(std::string error){
	std::cerr << error<< std::endl;
	//TODO log
	state = CRASH;
}

void processInput(){
	SDL_Event e;
	while(SDL_PollEvent(&e)){
		switch (e.type) {
			// Window
			case SDL_QUIT:						// The window has been closed
					state = EXIT;
				break;

			//Input

			case SDL_MOUSEMOTION:				// The Mouse has been moved
					//TODO: Input Handling
				break;
			case SDL_MOUSEBUTTONDOWN:			// A Mouse Button has been Pressed
					//TODO: Input Handling
				break;
			case SDL_MOUSEBUTTONUP:				// A Mouse Button has been Released
					//TODO: Input Handling
				break;
			case SDL_KEYDOWN:					// A Key has been Pressed
					//TODO: Input Handling
				break;
			case SDL_KEYUP:						// A Key has been Released
					//TODO: Input Handling
				break;





			default:							// Unkown event. Carry on!

				break;
		}


	}
}
void gameLoop(){
	while(state == RUNNING){
		Display::Update();
		processInput();
	}
}
unsigned char run(){
	if(!Display::Init()){			  		// Setup has failed :/
		crash("Display has failed to Initialize");
		return 4;
	}
	state = RUNNING;
	gameLoop();
	Display::Destoroy();
	if(state == SETUP)return 3;   // Kinda weird O.o
	if(state == RUNNING)return 2; // WTF WHAT IS HAPPENING THE LOOP SHOULDN'T HAVE STOPED IN THE FIRST PLACE :D
	if(state == CRASH)return 1;   // *sadface* but at least we'v got an error :)
	return 0;                                // YAY
}










