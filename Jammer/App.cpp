#include "App.h"

//Disable warnings from external code that we can't/won't modify - WNF
#pragma warning(disable : 26819) //Unannotated fallthrough in switch statement
#include <SDL.h>
#pragma warning(default : 26819)

#include "Debug.h"
#include "JammerEnums.h"
#include "Timer.h"
#include "Graphics/Image.h"

using namespace Jammer;

UniquePtr<App> App::instance = UniquePtr<App>(nullptr);

App& App::GetInstance(){
	if(instance.Get() == nullptr){
		instance.AssignPtr(new App());
	}

	J_ASSERT(instance.Get() != nullptr, "App instance was somehow nullptr!");
	return *instance.Get();
}

void App::DeleteInstance(){
	instance.Reset();
}

App::App() : gameName("GameJammer"), sdlWindow(nullptr), sdlScreenSurface(nullptr), glContext(nullptr), resourceManager(), isRunning(false){
	if(SDL_Init(SDL_INIT_EVERYTHING) > 0){
		JTHROW_FATAL_ERROR("SDL could not be initialized! SDL Error: " + String(SDL_GetError()), ErrorCode::SDL_Error);
	}

	Uint32 windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

	sdlWindow = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, windowFlags);
	if(sdlWindow == nullptr){
		JTHROW_FATAL_ERROR("Could not create SDL Window! SDL Error: " + String(SDL_GetError()), ErrorCode::SDL_Error);
	}

	sdlScreenSurface = SDL_GetWindowSurface(sdlWindow);
	if(sdlScreenSurface == nullptr){
		JTHROW_FATAL_ERROR("Could not get SDL Window Surface! SDL Error: " + String(SDL_GetError()), ErrorCode::SDL_Error);
	}

	SDL_JoystickEventState(SDL_ENABLE);

	glContext = SDL_GL_CreateContext(sdlWindow);
	if(glContext == nullptr){
		JTHROW_FATAL_ERROR("Could not create OpenGL Context! SDL Error: " + String(SDL_GetError()), ErrorCode::SDL_Error);
	}

	int status = SDL_GL_SetSwapInterval(-1); //Adaptive sync
	if(status != 0){
		SDL_GL_SetSwapInterval(1); //Adaptive sync not supported, try again with regular vsync
	}

	if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)){
		JTHROW_FATAL_ERROR("Failed to initialize Glad!", ErrorCode::OpenGL_Error);
	}

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glDepthFunc(GL_LESS);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SDL_GL_SwapWindow(sdlWindow);

#ifdef JAMMER_DEBUG
	if(glDebugMessageCallback){
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback((GLDEBUGPROC)App::GLDebugCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, true);
	}else{
		JLOG_WARNING("Could not set up OpenGL callback, OpenGL issues will not be logged!");
	}
#endif //JAMMER_DEBUG
}

App::~App(){
	SDL_GL_DeleteContext(glContext);
	sdlScreenSurface = nullptr; //Window owns the screen surface
	SDL_DestroyWindow(sdlWindow);
}

void App::Run(){
	isRunning = true;

	Timer timer;
	timer.Start();

	while(isRunning){
		timer.Update();

		HandleEvents();
		Update();
		Render();

		timer.Delay();
	}
}

void App::HandleEvents(){
	SDL_Event e;
	while(SDL_PollEvent(&e) != 0){
		switch(e.type){
			case SDL_QUIT:
				isRunning = false;
				return;
			case SDL_WINDOWEVENT: [[fallthrough]];
			case SDL_KEYDOWN: [[fallthrough]];
			case SDL_KEYUP: [[fallthrough]];
			case SDL_MOUSEMOTION: [[fallthrough]];
			case SDL_MOUSEBUTTONDOWN: [[fallthrough]];
			case SDL_MOUSEBUTTONUP: [[fallthrough]];
			case SDL_MOUSEWHEEL: [[fallthrough]];
			case SDL_JOYDEVICEADDED: [[fallthrough]];
			case SDL_JOYDEVICEREMOVED: [[fallthrough]];
			case SDL_JOYAXISMOTION: [[fallthrough]];
			case SDL_JOYBUTTONDOWN: [[fallthrough]];
			case SDL_JOYBUTTONUP: [[fallthrough]];
			case SDL_JOYHATMOTION:
				break;
			default:
				break;
		}
	}
}

void App::Update(){

}

void App::Render(){
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(size_t i = 0; i < renderables.Size(); i++){
		if(renderables[i] == nullptr){
			JLOG_WARNING("One of the listed Renderables was nullptr!");
			continue;
		}

		renderables[i]->Render(sdlWindow);
	}

	SDL_UpdateWindowSurface(sdlWindow);

	//SDL_GL_SwapWindow(sdlWindow);
}

Renderable* App::AddRenderable(GameObject* parent_, const String& imageName_){
	renderables.Add(new Renderable(parent_, imageName_));
	return renderables[renderables.Size() - 1];
}

void App::RemoveRenderable(Renderable* renderable_){
	for(int i = 0; i < renderables.Size(); i++){
		if(renderables[i] == renderable_){
			renderables.RemoveAt(i);
			return;
		}
	}
}

void App::SetWindowName(const String& name_){
	gameName = name_;
	if(sdlWindow != nullptr){
		SDL_SetWindowTitle(sdlWindow, gameName.CStr());
	}
}

void App::SetPixelScale(int16_t pixelScale_){
	J_ASSERT(pixelScale_ != 0, "Pixel scale cannot be zero");
	if(pixelScale_ == 0){
		return;
	}else if(pixelScale_ < 0){
		JLOG_WARNING(String("Pixel scale is a negative number [") + pixelScale_ + "], is this intended?");
	}

	pixelScale = pixelScale_;
}

void __stdcall App::GLDebugCallback(GLenum source_, GLenum type_, GLuint id_, GLenum severity_, GLsizei, const GLchar* message_, const void*){
	//Suppress useless messages
	switch(id_){
		case 131169: [[fallthrough]];	//The driver allocated storage for renderbuffer - This should not be considered a warning
		case 131185:					//Buffer object will use VIDEO memory - Irrelevant
			return;
		default:
			break;
	}

	String finalMessage = "OpenGL ";

	switch(source_){
		case GL_DEBUG_SOURCE_API:
			finalMessage += "API ";
			break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			finalMessage += "Window System ";
			break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:
			finalMessage += "Third Party ";
			break;
		case GL_DEBUG_SOURCE_APPLICATION:
			finalMessage += "Application ";
			break;
		case GL_DEBUG_SOURCE_OTHER:
			break;
		default:
			break;
	}

	switch(type_){
		case GL_DEBUG_TYPE_ERROR:
			finalMessage += "Error";
			break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			finalMessage += "Deprecated Behaviour";
			break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			finalMessage += "Undefined Behaviour";
			break;
		case GL_DEBUG_TYPE_PORTABILITY:
			finalMessage += "Portability";
			break;
		case GL_DEBUG_TYPE_PERFORMANCE:
			finalMessage += "Performance";
			break;
		case GL_DEBUG_TYPE_MARKER:
			finalMessage += "Marker";
			break;
		case GL_DEBUG_TYPE_PUSH_GROUP:
			finalMessage += "Push Group";
			break;
		case GL_DEBUG_TYPE_POP_GROUP:
			finalMessage += "Pop Group";
			break;
		case GL_DEBUG_TYPE_OTHER: [[fallthrough]];
		default:
			finalMessage += "Other";
			break;
	}

	finalMessage += id_ + ": " + String(static_cast<const char*>(message_));

	switch(severity_){
		case GL_DEBUG_SEVERITY_HIGH:
			Debug::LogError(finalMessage);
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			Debug::LogWarning(finalMessage);
			break;
		case GL_DEBUG_SEVERITY_LOW: [[fallthrough]];
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			Debug::Log(finalMessage);
			break;
	}
}