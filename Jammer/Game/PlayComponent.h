#ifndef JAMMER_GAME_PLAY_COMPONENT_H
#define JAMMER_GAME_PLAY_COMPONENT_H

namespace Jammer{
	class GameObject;

	class PlayComponent{
	public:
		PlayComponent(GameObject* parent_) : parent(parent_), hasStarted(false){}
		virtual ~PlayComponent() = default;

		virtual void OnStart(){ hasStarted = true; }
		virtual void OnUpdate([[maybe_unused]] float deltaTime_){}
		virtual void OnDestroy(){}

	private:
		GameObject* parent;
		bool hasStarted;
	};
}

#endif //!JAMMER_GAME_PLAY_COMPONENT_H