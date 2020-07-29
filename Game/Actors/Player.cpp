#include "Player.h"
#include "Enemy.h"
#include "Math/Math.h"
#include "PlayerProjectile.h"
#include "Object/Scene.h"
#include "Graphics/PartilcesSystem.h"
#include "Math/Random.h"
#include "../Game.h"
#include "Audio/AudioSystem.h"
#include <fstream>

bool Player::Load(const std::string& filename)
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

void Player::Update(float dt)
{
	m_fireTimer += dt;
	m_speedTimer += dt;

	if (Core::Input::IsPressed(VK_SPACE) && m_fireTimer >= m_fireRate)
	{
		m_fireTimer = 0;
		g_audioSystem.PlayAudio("Laser");

		PlayerProjectile* projectile = new PlayerProjectile;
		projectile->Load("projectile.txt");
		projectile->GetTransform().position = m_transform.position;
		projectile->GetTransform().angle = m_transform.angle;

		m_scene->AddActor(projectile);
	}

	if (m_speedTimer >= m_boostTime)
	{
		m_speedTimer = 0;
		m_thrust = 200;
	}

	//Player
	nc::Vector2 force;
	if (Core::Input::IsPressed('W')) { force = nc::Vector2::forward * m_thrust; }

	force = nc::Vector2::Rotate(force, m_transform.angle);
	
	//sun gravity
	nc::Vector2 direction = nc::Vector2{ 400,300 } - m_transform.position;
	if (direction.Length() <= 200.0f)
	{
		float streangth = 1.0f - (direction.Length() / 200.0f);
		direction.Normalize();
		force = force + (direction * 100.0f * streangth);
	}

	m_velocity = m_velocity + (force * dt);
	m_transform.position = m_transform.position + (m_velocity * dt);
	m_velocity = m_velocity * 0.98f;

	if (m_transform.position.x > 800.0f) { m_transform.position.x = 0; }
	if (m_transform.position.x < 0.0f) { m_transform.position.x = 800; }
	if (m_transform.position.y > 600.0f) { m_transform.position.y = 0; }
	if (m_transform.position.y < 0.0f) { m_transform.position.y = 600; }

	//rotations
	float torque{ 0 };
	if (Core::Input::IsPressed('A')) torque = -20.0f;
	if (Core::Input::IsPressed('D')) torque = 20.0f;

	m_angularVelocity = m_angularVelocity + (torque * dt);
	m_angularVelocity = m_angularVelocity * 0.97f;
	m_transform.angle = m_transform.angle + (m_angularVelocity * dt);

	if (force.LengthSqr() > 0)
	{
		Actor* child = m_children[0];

		g_particlesSystem.Create(child->GetTransform().matrix.GetPosition(), child->GetTransform().matrix.GetAngle() + nc::PI, 20, 1, 1, nc::Color{ nc::random(0,1),nc::random(0,1),nc::random(0,1) }, 100, 200);

		child = m_children[1];

		g_particlesSystem.Create(child->GetTransform().matrix.GetPosition(), child->GetTransform().matrix.GetAngle() + nc::PI, 20, 1, 1, nc::Color{ nc::random(0,1),nc::random(0,1),nc::random(0,1) }, 100, 200);
	}

	if (Core::Input::IsPressed('Q') && !m_prevButtonPress)
	{
		m_transform.position = nc::Vector2{ nc::random(0, 800), nc::random(0,600) };
		m_transform.angle = nc::random(0, nc::TWO_PI);
	}
	m_prevButtonPress = Core::Input::IsPressed('Q');

	m_transform.Update();

	// update children
	for (auto child : m_children)
	{
		child->Update(dt);
	}
}

void Player::OnCollision(Actor* actor)
{
	if (!m_destroy && (actor->GetType() == eType::ENEMY || actor->GetType() == eType::ENEMY_PROJECTILE))
	{
		m_destroy = true;

		//Set Target to null
		auto enemies = m_scene->GetActors<Enemy>();
		for (auto enemy : enemies)
		{
			enemy->SetTarget(nullptr);
		}

		g_particlesSystem.Create(m_transform.position, m_transform.angle + nc::PI, 180, 2500, 1, nc::Color{ nc::random(0,1),nc::random(0,1),nc::random(0,1) }, 100, 200);

		g_audioSystem.PlayAudio("Explosion");

		m_scene->GetGame()->SetState(Game::eState::PLAYER_DEAD);
	}

	if (actor->GetType() == eType::SPEEDBOOST)
	{
		m_thrust = 400;
	}
}
