#include "GameObject.h"

using namespace Jammer;

GameObject::GameObject(const String& name_) : name(name_), transform(Vector2(0.0f, 0.0f)){}

void GameObject::Update([[maybe_unused]] float deltaTime_){}