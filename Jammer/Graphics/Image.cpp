#include "Image.h"

#include <SDL_image.h>

using namespace Jammer;

Image::Image(const String& path_) : Resource(){
	imageSurface = IMG_Load(path_.CStr());
	if(imageSurface == nullptr){
		JTHROW_FATAL_ERROR("Could not load image [" + path_ + "! SDL Error: " + String(SDL_GetError()), ErrorCode::SDL_Error);
	}
}

Image::~Image(){
	SDL_FreeSurface(imageSurface);
}