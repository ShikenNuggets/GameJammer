#ifndef JAMMER_APP_H
#define JAMMER_APP_H

#include <glad/glad.h>

//Hide warnings from external code that we can't/won't modify - WNF
#pragma warning(disable : 26819) //Unnanotated fallthrough in switch statement
#include <SDL.h>
#pragma warning(default : 26819)

#include "Audio/AudioSource.h"
#include "Data/String.h"
#include "Game/GameObject.h"
#include "Game/PlayComponent.h"
#include "Graphics/Renderable.h"
#include "Memory/UniquePtr.h"
#include "Physics/PhysicsBody.h"
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

		Renderable* AddRenderable(GameObject* parent_, const String& image_);
		void RemoveRenderable(Renderable* renderable_);

		ResourceManager& GetResourceManager(){ return resourceManager; }
		int16_t GetPixelScale() const{ return pixelScale; }

		void SetWindowName(const String& name_);
		void SetPixelScale(const int16_t pixelScale_);

	private:
		static UniquePtr<App> instance;

		String gameName;
		SDL_Window* sdlWindow;
		SDL_Surface* sdlScreenSurface;
		SDL_GLContext glContext;
		ResourceManager resourceManager;
		int16_t pixelScale = 100; //100 pixels = 1 meter
		bool isRunning;

		Array<Renderable*> renderables;

		void HandleEvents();
		void Update();
		void Render();

		static void __stdcall GLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
	};
}

#endif //!JAMMER_APP_H