#include <iostream>

//Disable warnings from external code that we can't/won't modify - WNF
#pragma warning(disable : 26819) //Unannotated fallthrough in switch statement
#include <SDL.h>
#pragma warning(default : 26819)

#include <App.h>
#include <Graphics/Image.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]){
	try{
		Jammer::App& app = Jammer::App::GetInstance();

		app.SetWindowName("TestGame");
		app.GetResourceManager().AddResource(new Jammer::ImageContainer("TestImage", "Resources/Test.png"));
		
		app.Run();

	#ifdef JAMMER_DEBUG
		app.DeleteInstance(); //Not strictly necessary but good for testing proper shutdown
	#endif //JAMMER_DEBUG
	}catch(std::runtime_error e){
		_ASSERT(false);
	}

#ifdef JAMMER_DEBUG
	std::cout << "The program is now complete." << std::endl;
#endif //JAMMER_DEBUG

	return 0;
}