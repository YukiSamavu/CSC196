#include "pch.h"
#include "PartilcesSystem.h"
#include "Math/Random.h"
#include "Math/Math.h"

nc::ParticlesSystem g_particlesSystem;

namespace nc
{
    void ParticlesSystem::Startup()
    {
        m_size = 1000000;
        m_particles = new Particles[m_size];
    }

    void ParticlesSystem::Shutdown()
    {
        delete[] m_particles;
    }

    void ParticlesSystem::Update(float dt)
    {
        for (size_t i = 0; i < m_size; i++)
        {
            Particles* p = &m_particles[i];
            if (p->active)
            {
                p->lifetime = p->lifetime - dt;
                p->active = (p->lifetime > 0);

                p->prevPosition = p->position;
                p->position = p->position + (p->velocty * dt);
            }
        }
    }

    void ParticlesSystem::Draw(Core::Graphics& graphics)
    {
        for (size_t i = 0; i < m_size; i++)
        {
            Particles* p = &m_particles[i];
            if (p->active)
            {
                graphics.SetColor(p->color);
                graphics.DrawLine(p->position.x, p->position.y, p->prevPosition.x, p->prevPosition.y);
            }
        }
    }

    void ParticlesSystem::Create(const Vector2& position, 
                                 float angle,  
                                 float angleRange, 
                                 size_t count, 
                                 float lifetime,   
                                 const Color& color,   
                                 float minSpeed,   
                                 float maxSpeed)
    {
        for (size_t i = 0; i < count; i++)
        {
            Particles* p = GetFreeParticles();
            if (p)
            {
                p->active = true;
                p->lifetime = lifetime;
                p->position = position;
                p->prevPosition = position;
                p->color = color;

                float angleRandom = nc::DegreeToRadians(nc::random(-angleRange, angleRange));
                Vector2 direction = nc::Vector2::Rotate(nc::Vector2::forward, angle + angleRandom);
                p->velocty = direction * nc::random(minSpeed, maxSpeed);
            }
        }
    }

    Particles* ParticlesSystem::GetFreeParticles()
    {
        for (size_t i = 0; i < m_size; i++)
        {
            Particles* p = &m_particles[i];
            if (!p->active)
            {
                return p;
            }
        }

        return nullptr;
    }
}
