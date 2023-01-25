#pragma once

#include <glm/glm.hpp>

#include "Engine/Core/Utils/Timestep.h"

namespace Illusion
{
	struct ParticleProp
	{
		glm::vec2 Position;
		glm::vec2 Velocity, VelocityVariation;
		glm::vec4 ColorBegin, ColorEnd;
		float Scale, SizeBegin, SizeEnd, SizeVariation;
		float LifeTime = 1.0f;
	};

	class ParticleEmitter
	{

	public:

		ParticleEmitter();
		
		void OnUpdate(Timestep ts);
		void OnRender();

		void Configure(const ParticleProp& particleProp);

		void Emit();

	private:

		struct Particle
		{
			glm::vec2 Position;
			glm::vec2 Velocity;
			glm::vec4 ColorBegin, ColorEnd;
			float Rotation = 0.0f;
			float SizeBegin, SizeEnd;
			float Scale = 1.0f;
			float LifeTime = 1.0f;
			float LifeRemaining = 0.0f;

			bool Active = false;
		};

		ParticleProp m_Prop;
		std::vector<Particle> m_ParticlePool;
		uint32_t m_PoolIndex = 999;

	};

}


