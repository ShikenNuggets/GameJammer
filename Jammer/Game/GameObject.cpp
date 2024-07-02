#include "GameObject.h"

#include "App.h"

using namespace Jammer;

GameObject::GameObject(const String& name_) : name(name_), transform(Vector2(0.0f, 0.0f)), audioSource(nullptr), playComponent(nullptr), renderable(nullptr), physicsBody(nullptr){}

GameObject::~GameObject(){
	if(renderable != nullptr){
		App::GetInstance().RemoveRenderable(renderable);
		delete renderable;
	}
}

void GameObject::Update([[maybe_unused]] float deltaTime_){}

void GameObject::AddRenderable(const String& imageName_){
	renderable = App::GetInstance().AddRenderable(this, imageName_);
	J_BASIC_ASSERT(renderable != nullptr);
}