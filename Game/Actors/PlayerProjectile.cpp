#include "PlayerProjectile.h"
#include "Math/Math.h"
#include "Graphics/PartilcesSystem.h"
#include "Math/Random.h"
#include <fstream>

bool PlayerProjectile::Load(const std::string& filename)
{
	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open())
	{
		success = true;

		stream >> m_transform;

		std::string shapename;
		std::getline(stream, shapename);
		m_shape.Load(shapename);
	}

	return success;
}

void PlayerProjectile::Update(float dt)
{
	m_lifetime -= dt;
	if (m_lifetime <= 0)
	{
		m_destroy = true;
	}

	nc::Vector2 direction = nc::Vector2::Rotate(nc::Vector2::forward, m_transform.angle);
	nc::Vector2 velocity = direction * m_speed;
	m_transform.position = m_transform.position + (velocity * dt);

	g_particlesSystem.Create(m_transform.position, m_transform.angle + nc::PI, 20, 1, 1, nc::Color{ nc::random(0,1),nc::random(0,1),nc::random(0,1) }, 100, 200);

	m_transform.Update();
}

void PlayerProjectile::OnCollision(Actor* actor)
{
	if (actor->GetType() == eType::ENEMY || actor->GetType() == eType::ENEMY_PROJECTILE)
	{
		m_destroy = true;
	}
}
