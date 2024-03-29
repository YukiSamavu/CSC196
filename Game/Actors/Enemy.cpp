#include "Enemy.h"
#include "Math/Math.h"
#include "EnemyProjectile.h"
#include "Graphics/PartilcesSystem.h"
#include "Math/Random.h"
#include "Object/Scene.h"
#include "../Game.h"
#include "Audio/AudioSystem.h"
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
	m_fireTimer += dt;

	nc::Vector2 targetPosition = (m_target) ? m_target->GetTransform().position : nc::Vector2{400,300};
    nc::Vector2 direction = targetPosition - m_transform.position;
	direction.Normalize();
	nc::Vector2 Velocity = (direction * m_speed) / 3;
	m_transform.position = m_transform.position + (Velocity * dt);
	m_transform.angle = std::atan2(direction.y, direction.x) + nc::DegreeToRadians(90.0f);

	if (m_fireTimer >= m_fireRate)
	{
		m_fireTimer = 0;
		g_audioSystem.PlayAudio("Laser");

		EnemyProjectile* projectile = new EnemyProjectile;
		projectile->Load("projectile.txt");
		projectile->GetTransform().position = m_transform.position;
		projectile->GetTransform().angle = m_transform.angle;

		m_scene->AddActor(projectile);
	}

	m_transform.Update();
}

void Enemy::OnCollision(Actor* actor)
{
	if (actor->GetType() == eType::PLAYER_PROJECTILE)
	{
		m_destroy = true;

		// set game points/score
		m_scene->GetGame()->AddPoints(1);

		g_particlesSystem.Create(m_transform.position, m_transform.angle + nc::PI, 180, 2500, 1, nc::Color{ nc::random(0,1),nc::random(0,1),nc::random(0,1) }, 100, 200);

		g_audioSystem.PlayAudio("Explosion");
	}
}
