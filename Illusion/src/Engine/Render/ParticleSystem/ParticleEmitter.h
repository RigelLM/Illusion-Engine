/*
 * ========================== ParticleEmitter.h ============================
 *								 -- ils --
 *														CREATE -- 2023.01.25
 *														MODIFY --
 * -------------------------------------------------------------------------
 * The ParticleEmitter Class
 * Handles particle properties
 * ----------------------------
 */

#pragma once

#include <glm/glm.hpp>

#include "Engine/Core/Utils/Timestep.h"

 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	// Holds all properties a particle has
	struct ParticleProp
	{
		glm::vec2 Position;
		glm::vec2 Velocity, VelocityVariation;
		glm::vec4 ColorBegin, ColorEnd;
		float Scale = 1.0f;
		float SizeBegin, SizeEnd, SizeVariation;
		float LifeTime = 1.0f;
	};

	// The ParticleEmitter Class
	class ParticleEmitter
	{

	public:

		ParticleEmitter();

		// Update all the particles after they are emitted
		// Calculate position,, rotation and life
		void OnUpdate(Timestep ts);

		// Draw all particles
		void OnRender();

		// Configure the particle properties
		void Configure(const ParticleProp& particleProp);

		// Emit particles according to the particle properties and update their state
		void Emit();

	private:

		// Particles
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
	//--------------------namespace: Illusion ends--------------------
}


