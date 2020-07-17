#include "pch.h"
#include "Scene.h"
#include "Actor.h"

std::list<nc::Actor*> sceneActors;

namespace nc
{
	void Scene::Startup()
	{
		// nothing
	}

	void Scene::Shutdown()
	{
		// iterate through the actors and call delete on each actor
		// this will free up the memory for each actor

		// clear m_actors list
		for (nc::Actor* actor : sceneActors)
		{
			sceneActors.remove(actor);
			delete(actor);
		}
	}

	void Scene::Update(float dt)
	{
		// iterate through the actors and call Update on each actor
		for (nc::Actor* actor : sceneActors)
		{
			actor->Update(dt);
		}
	}

	void Scene::Draw(Core::Graphics& graphics)
	{
		// iterate through the actors and call Draw on each actor
		for (nc::Actor* actor : sceneActors)
		{
			actor->Draw(graphics);
		}
	}

	void Scene::AddActor(Actor* actor)
	{
		// set the scene for the actor, use this
		// push back the actor on the actors list
		sceneActors.push_back(actor);
	}

	void Scene::RemoveActor(Actor* actor)
	{
		std::list<Actor*>::iterator iter = std::find(m_actors.begin(), m_actors.end(), actor);
		if (iter != m_actors.end())
		{
			delete* iter;
			m_actors.erase(iter);
		}
	}
}
