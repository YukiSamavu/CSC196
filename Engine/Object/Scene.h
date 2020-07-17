#pragma once
#include "core.h"
#include <list>

namespace nc
{
	class Scene
	{
	public:
		void Startup();
		void Shutdown();

		void Update(float dt);
		void Draw(Core::Graphics& graphics);

		void AddActor(class Actor* actor);
		void RemoveActor(class Actor* object);

		template <typename T>
		T* GetActor() 
		{
			nc::Actor* actor{ nullptr };

			for (nc::Actor* a : sceneActors)
			{
				actor = dynamic_cast<T*>(a);

				if (actor != nullptr) break;
			}

			return actor;
		}

		template <typename T>
		std::vector<T*> GetActors() {}

	private:
		std::list<class Actor*> m_actors;
	};
}
