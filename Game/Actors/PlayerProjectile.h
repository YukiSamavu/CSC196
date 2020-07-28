#pragma once
#include "Object/Actor.h"

class PlayerProjectile : public nc::Actor
{
public:
	PlayerProjectile() {}

	virtual eType GetType() override { return eType::PLAYER_PROJECTILE; }

	virtual bool Load(const std::string& filename) override;
	virtual void Update(float dt) override;

	virtual void OnCollision(Actor* actor) override;

	void SetSpeed(float speed) { m_speed = speed; }

protected:
	float m_speed{ 200.0f };
	float m_lifetime{ 2 };
};
