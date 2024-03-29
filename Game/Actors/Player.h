#pragma once
#include"Object/Actor.h"

class Player : public nc::Actor
{
public:
	Player() {}

	virtual eType GetType() override { return eType::PLAYER; }

	virtual bool Load(const std::string& filename) override;
	virtual void Update(float dt) override;

	virtual void OnCollision(Actor* actor) override;

protected:
	float m_speedTimer{ 0 };
	float m_boostTime{ 10 };
	float m_thrust{ 200.0f };

	float m_rotation{ 360.0f };

	float m_fireRate{ 0.2f };
	float m_fireTimer{ 0 };

	bool m_prevButtonPress{ false };
	
	nc::Vector2 m_velocity;
	float m_angularVelocity{ 0 };
};