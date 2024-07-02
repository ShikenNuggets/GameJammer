#ifndef JAMMER_GRAPHICS_RENDERABLE_H
#define JAMMER_GRAPHICS_RENDERABLE_H

#include "Graphics/Image.h"

namespace Jammer{
	class GameObject;

	class Renderable{
	public:
		Renderable(GameObject* parent_, const String& imageName_);
		~Renderable() = default;

		void Render(SDL_Window* window_);

	private:
		GameObject* parent;
		SharedPtr<Resource> image;
		Image* imagePtr;
	};
}

#endif //!JAMMER_GRAPHICS_RENDERABLE