#include "App.h"

//Disable warnings from external code that we can't/won't modify - WNF
#pragma warning(disable : 26819) //Unannotated fallthrough in switch statement
#include <SDL.h>
#pragma warning(default : 26819)

#include "Debug.h"

using namespace Jammer;

App::App(){}

void App::Run(){
	JLOG("Test");
	SDL_Init(SDL_INIT_EVERYTHING);
}