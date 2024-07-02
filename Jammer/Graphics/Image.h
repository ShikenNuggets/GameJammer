#ifndef JAMMER_GRAPHICS_IMAGE_H
#define JAMMER_GRAPHICS_IMAGE_H

//Hide warnings from external code that we can't/won't modify - WNF
#pragma warning(disable : 26819) //Unnanotated fallthrough in switch statement
#include <SDL.h>
#pragma warning(default : 26819)

#include "Resource/Resource.h"

namespace Jammer{
	class Image : public Resource{
	public:
		Image(const String& path_);
		~Image();

		SDL_Surface* GetSurface() const{ return imageSurface; }

	private:
		SDL_Surface* imageSurface;
	};

	class ImageContainer : public ResourceContainer{
	public:
		ImageContainer(const String& name_, const String& path_) : ResourceContainer(name_, path_){}

	protected:
		virtual Resource* LoadResource() const override{ return new Image(Path()); }
	};
}

#endif //!JAMMER_GRAPHICS_IMAGE_H