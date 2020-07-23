#pragma once
#include "pch.h"
#include "core.h"
#include <vector>
#include <list>

class Game;

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
		void RemoveAllActors();

		template <typename T>
		T* GetActor() 
		{
			T* actor{ nullptr };

			for (nc::Actor* a : m_actors)
			{
				actor = dynamic_cast<T*>(a);

				if (actor != nullptr) break;
			}

			return actor;
		}

		template <typename T>
		std::vector<T*> GetActors()
		{
			std::vector<T*> actors;
			for (Actor* a : m_actors)
			{
				T* actor = dynamic_cast<T*>(a);
				if (actor)
				{
					actors.push_back(actor);
				}
			}

			return actors;
		}

		void SetGame(Game* game) { m_game = game; }
		Game* GetGame() { return m_game; }

	private:
		Game* m_game;
		std::list<class Actor*> m_actors;
	};
}
