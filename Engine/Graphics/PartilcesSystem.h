#pragma once
#include "Particles.h"
#include "core.h"

namespace nc
{
	class ParticlesSystem
	{
	public:
		void Startup();
		void Shutdown();

		void Update(float dt);
		void Draw(Core::Graphics& graphics);

		void Create(const Vector2& position,
			float angle,
			float angleRange,
			size_t count,
			float lifetime,
			const Color& color,
			float minSpeed,
			float maxSpeed);

	protected:
		Particles* GetFreeParticles();

	protected:
		Particles* m_particles;
		size_t m_size;
	};
}