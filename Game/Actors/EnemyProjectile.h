#pragma once
#include "Object/Actor.h"

class EnemyProjectile : public nc::Actor
{
public:
	EnemyProjectile() {}

	virtual eType GetType() override { return eType::ENEMY_PROJECTILE; }

	virtual bool Load(const std::string& filename) override;
	virtual void Update(float dt) override;

	virtual void OnCollision(Actor* actor) override;

	void SetSpeed(float speed) { m_speed = speed; }

protected:
	float m_speed{ 200.0f };
	float m_lifetime{ 2 };
};

