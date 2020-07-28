#pragma once
#include "Object/Actor.h"

class Boss : public nc::Actor
{
public:
	Boss() {}

	virtual eType GetType() override { return eType::BOSS; }

	virtual bool Load(const std::string& filename) override;
	virtual void Update(float dt) override;

	virtual void OnCollision(Actor* actor) override;

	void SetTarget(Actor* actor) { m_target = actor; }
	void SetSpeed(float speed) { m_speed = speed; }

protected:
	float m_speed{ 0.0f };
	int m_BossLife{ 100 };
	Actor* m_target{ nullptr };
};
