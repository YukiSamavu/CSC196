#include "SpeedBoost.h"
#include "Math/Math.h"
#include "Graphics/PartilcesSystem.h"
#include "../Game.h"
#include "Audio/AudioSystem.h"
#include <fstream>

bool SpeedBoost::Load(const std::string& filename)
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

void SpeedBoost::Update(float dt)
{
	m_transform.Update();
}

void SpeedBoost::OnCollision(Actor* actor)
{
	if (actor->GetType() == eType::PLAYER)
	{
		m_destroy = true;

		g_particlesSystem.Create(m_transform.position, m_transform.angle + nc::PI, 180, 100, 1, nc::Color{ 0, 1, 0 }, 100, 200);

		g_audioSystem.PlayAudio("PowerUp");
	}
}
