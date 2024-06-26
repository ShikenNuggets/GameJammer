//Disable warnings from external code that we can't/won't modify - WNF
#pragma warning(disable : 26819) //Unannotated fallthrough in switch statement
#include <SDL.h>
#pragma warning(default : 26819)

#include <App.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]){
	Jammer::App app;
	app.Run();

	return 0;
}