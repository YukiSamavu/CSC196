#include "Boss.h"
#include "Math/Math.h"
#include "Graphics/PartilcesSystem.h"
#include "Math/Random.h"
#include "Object/Scene.h"
#include "../Game.h"
#include "Audio/AudioSystem.h"
#include <fstream>

bool Boss::Load(const std::string& filename)
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

void Boss::Update(float dt)
{
	nc::Vector2 targetPosition = (m_target) ? m_target->GetTransform().position : nc::Vector2{ 400,300 };
	nc::Vector2 direction = targetPosition - m_transform.position;
	direction.Normalize();
	nc::Vector2 Velocity = (direction * m_speed) / 3;
	m_transform.position = m_transform.position + (Velocity * dt);
	m_transform.angle = std::atan2(direction.y, direction.x) + nc::DegreeToRadians(90.0f);

	m_transform.Update();
}

void Boss::OnCollision(Actor* actor)
{
	m_BossLife = m_BossLife - 1;

	if (m_BossLife <= 0)
	{
		m_destroy = true;

		// set game points/score
		m_scene->GetGame()->AddPoints(100);

		g_particlesSystem.Create(m_transform.position, m_transform.angle + nc::PI, 180, 2500, 1, nc::Color{ nc::random(0,1),nc::random(0,1),nc::random(0,1) }, 100, 200);

		g_audioSystem.PlayAudio("Explosion");

		m_scene->GetGame()->SetState(Game::eState::GAME);
	}
}
