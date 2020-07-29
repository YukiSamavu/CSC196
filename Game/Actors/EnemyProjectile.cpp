#include "EnemyProjectile.h"
#include "Math/Math.h"
#include "Graphics/PartilcesSystem.h"
#include "Math/Random.h"
#include <fstream>

bool EnemyProjectile::Load(const std::string& filename)
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

void EnemyProjectile::Update(float dt)
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

void EnemyProjectile::OnCollision(Actor* actor)
{
	if (actor->GetType() == eType::PLAYER || actor->GetType() == eType::PLAYER_PROJECTILE)
	{
		g_particlesSystem.Create(m_transform.position, m_transform.angle + nc::PI, 180, 100, 1, nc::Color{ nc::random(0,1),nc::random(0,1),nc::random(0,1) }, 100, 200);

		m_destroy = true;
	}
}
