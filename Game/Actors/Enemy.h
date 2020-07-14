#pragma once
#include "Object/Actor.h"

class Enemy : public nc::Actor
{
public:
	Enemy() {}

	virtual bool Load(const std::string& filename) override;
	virtual void Update(float dt) override;

	void SetTarget(Actor* actor) { m_target = actor; }

protected:
	float m_speed{ 200.0f };
	Actor* m_target{ nullptr };
};
