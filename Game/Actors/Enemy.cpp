#include "Enemy.h"
#include "Math/Math.h"
#include <fstream>

bool Enemy::Load(const std::string& filename)
{
	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open())
	{
		success = true;

		stream >> m_transform;
	}

	std::string shapename;
	stream >> shapename;
	m_shape.Load(shapename);

	return success;
}

void Enemy::Update(float dt)
{
    nc::Vector2 direction = m_target->GetTransform().position - m_transform.position;
	direction.Normalize();
	nc::Vector2 Velocity = direction * m_speed;
	//m_transform.position = m_transform.position + (Velocity * dt);
	m_transform.angle = std::atan2(direction.y, direction.x) + nc::DegreeToRadians(90.0f);

	m_transform.Update();
}

void Enemy::OnCollision(Actor* actor)
{
	if (actor->GetType() == eType::PROJECTILE)
	{
		m_destroy = true;
	}
}
