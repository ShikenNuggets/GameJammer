#ifndef JAMMER_APP_H
#define JAMMER_APP_H

#include <glad/glad.h>

//Hide warnings from external code that we can't/won't modify - WNF
#pragma warning(disable : 26819) //Unnanotated fallthrough in switch statement
#include <SDL.h>
#pragma warning(default : 26819)

#include "Data/String.h"
#include "Memory/UniquePtr.h"
#include "Resource/ResourceManager.h"

namespace Jammer{
	class App{
	public:
		App();
		~App();

		App(const App&) = delete;
		App(const App&&) = delete;
		App& operator=(const App&) = delete;
		App& operator=(const App&&) = delete;

		static App& GetInstance();
		static void DeleteInstance();

		void Run();

		ResourceManager& GetResourceManager(){ return resourceManager; }

		void SetWindowName(const String& name_);

	private:
		static UniquePtr<App> instance;

		String gameName;
		SDL_Window* sdlWindow;
		SDL_Surface* sdlScreenSurface;
		SDL_GLContext glContext;
		ResourceManager resourceManager;
		bool isRunning;

		void HandleEvents();
		void Update();
		void Render();

		static void __stdcall GLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
	};
}

#endif //!JAMMER_APP_H