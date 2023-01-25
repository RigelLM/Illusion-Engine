#include "pch.h"
#include "ParticleEmitter.h"

#include "Engine/Core/Utils/Random.h"
#include "Engine/Render/Renderer/Renderer2D.h"

#include <glm/gtc/constants.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

namespace Illusion
{


	ParticleEmitter::ParticleEmitter()
	{
		m_ParticlePool.resize(1000);
	}

	void ParticleEmitter::OnUpdate(Timestep ts)
	{
		for (auto& particle : m_ParticlePool)
		{
			if (!particle.Active)
				continue;

			if (particle.LifeRemaining <= 0.0f)
			{
				particle.Active = false;
				continue;
			}

			particle.LifeRemaining -= ts;
			particle.Position += particle.Velocity * (float)ts;
			particle.Rotation += 0.01f * ts;
		}
	}

	void ParticleEmitter::OnRender()
	{
		for (auto& particle : m_ParticlePool)
		{
			if (!particle.Active)
				continue;

			// Fade away particles
			float life = particle.LifeRemaining / particle.LifeTime;
			glm::vec4 color = glm::lerp(particle.ColorEnd, particle.ColorBegin, life);
			//color.a = color.a * life;

			float size = glm::lerp(particle.SizeEnd, particle.SizeBegin, life) * particle.Scale;

			// Render
			Renderer2D::DrawRotatedQuad(particle.Position, particle.Rotation, { size, size }, color);
		}
	}

	void ParticleEmitter::Configure(const ParticleProp& particleProp)
	{
		m_Prop = particleProp;
	}

	void ParticleEmitter::Emit()
	{
		Particle& particle = m_ParticlePool[m_PoolIndex];
		particle.Active = true;
		particle.Position = m_Prop.Position;
		particle.Rotation = Random::Float() * 2.0f * glm::pi<float>();

		// Velocity
		particle.Velocity = m_Prop.Velocity;
		particle.Velocity.x += m_Prop.VelocityVariation.x * (Random::Float() - 0.5f);
		particle.Velocity.y += m_Prop.VelocityVariation.y * (Random::Float() - 0.5f);

		// Color
		particle.ColorBegin = m_Prop.ColorBegin;
		particle.ColorEnd = m_Prop.ColorEnd;

		particle.LifeTime = m_Prop.LifeTime;
		particle.LifeRemaining = m_Prop.LifeTime;
		particle.SizeBegin = m_Prop.SizeBegin + m_Prop.SizeVariation * (Random::Float() - 0.5f);
		particle.SizeEnd = m_Prop.SizeEnd;
		particle.Scale = m_Prop.Scale;

		m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
	}
}