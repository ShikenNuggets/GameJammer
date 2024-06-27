#ifndef JAMMER_GAME_OBJECT_H
#define JAMMER_GAME_OBJECT_H

#include "Math/Vector.h"

namespace Jammer{
	struct Transform{
		constexpr Transform(const Vector2& pos_, float rot_ = 0.0f, const Vector2& scale_ = Vector2::Fill(0.0f)) : position(pos_), rotation(rot_), scale(scale_){}

		Vector2 position;
		float rotation;
		Vector2 scale;
	};

	class GameObject{
	public:
		GameObject(const String& name_);

		void Update(float deltaTime_);

	private:
		String name;
		Transform transform;
	};
}

#endif //!JAMMER_GAME_OBJECT_H