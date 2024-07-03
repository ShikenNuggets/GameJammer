#include "Renderable.h"

#include "App.h"
#include "Game/GameObject.h"

using namespace Jammer;

Renderable::Renderable() : parent(nullptr), image(nullptr), imagePtr(nullptr){}

Renderable::Renderable(GameObject* parent_, const String& imageName_) : parent(parent_), image(nullptr), imagePtr(nullptr){
	image = App::GetInstance().GetResourceManager().GetResource(imageName_);
	J_BASIC_ASSERT(image != nullptr);

	imagePtr = image.As<Image>();
	J_BASIC_ASSERT(imagePtr);
}

void Renderable::Render(SDL_Window* window_) const{
	J_BASIC_ASSERT(imagePtr != nullptr);
	J_BASIC_ASSERT(parent != nullptr);
	J_BASIC_ASSERT(window_ != nullptr);

	if(parent == nullptr){
		JLOG_WARNING("Renderable has no object parent!");
		return;
	}

	if(window_ == nullptr){
		JLOG_WARNING("Tried to render to a null window!");
		return;
	}

	if(imagePtr == nullptr){
		JLOG_WARNING("Tried to render to a null image!");
		return;
	}

	SDL_Rect destRect{};
	destRect.x = Math::Round(parent->Position().x * static_cast<double>(App::GetInstance().GetPixelScale()));
	destRect.y = Math::Round(parent->Position().y * static_cast<double>(App::GetInstance().GetPixelScale()));

	SDL_BlitSurface(imagePtr->GetSurface(), nullptr, SDL_GetWindowSurface(window_), &destRect);
}