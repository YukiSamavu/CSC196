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
	//Enemy
    nc::Vector2 direction = m_target->GetTransform().position - m_transform.position;
	direction.Normalize();
	nc::Vector2 enemyVelocity = direction * m_speed;
	m_transform.position = m_transform.position + (enemyVelocity * dt);
	m_transform.angle = std::atan2(direction.y, direction.x) + nc::DegreeToRadians(90.0f);

	m_transform.Update();
}
