#include "Player.h"
#include "Math/Math.h"
#include <fstream>

bool Player::Load(const std::string& filename)
{
	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open())
	{
		success = true;

		stream >> m_transform;

		std::string shapename;
		stream >> shapename;
		m_shape.Load(shapename);
	}

	return success;
}

void Player::Update(float dt)
{
	//Player

	nc::Vector2 force;
	if (Core::Input::IsPressed('W')) { force = nc::Vector2::forward * m_thrust; }

	force = nc::Vector2::Rotate(force, m_transform.angle);
	
	//sun gravity
	nc::Vector2 direction = nc::Vector2{ 400,300 } - m_transform.position;
	if (direction.Length() <= 400.0f)
	{
		float streangth = 1.0f - (direction.Length() / 200.0f);
		direction.Normalize();
		force = force + (direction * 400.0f * streangth);
	}

	m_velocity = m_velocity + (force * dt);
	m_transform.position = m_transform.position + (m_velocity * dt);
	m_velocity = m_velocity * 0.98f;

	direction = nc::Vector2::Rotate(direction, m_transform.angle);
	m_transform.position = m_transform.position + direction;

	if (m_transform.position.x > 800.0f) { m_transform.position.x = 0; }
	if (m_transform.position.x < 0.0f) { m_transform.position.x = 800; }
	if (m_transform.position.y > 600.0f) { m_transform.position.y = 0; }
	if (m_transform.position.y < 0.0f) { m_transform.position.y = 600; }

	if (Core::Input::IsPressed('A')) m_transform.angle -= dt * nc::DegreeToRadians(360.0f);
	if (Core::Input::IsPressed('D')) m_transform.angle += dt * nc::DegreeToRadians(360.0f);
}
