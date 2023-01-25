/*
 * ========================== ParticleSystem.cpp ==========================
 *								 -- ils --
 *													   CREATE -- 2023.01.25
 *													   MODIFY --
 * ------------------------------------------------------------------------
 * The ParticleSystem Class
 * Manages all emitters
 * ----------------------------
 */

#include "pch.h"
#include "ParticleSystem.h"

//--------------------namespace: Illusion starts--------------------
namespace Illusion
{

	ParticleSystem::ParticleSystem()
	{

	}

	// Add emitter to the vector
	void ParticleSystem::AddEmitter(ParticleEmitter* emitter)
	{
		m_Emitters.emplace_back(emitter);
	}

	// Update all emitters
	void ParticleSystem::OnUpdate(Timestep ts)
	{
		for (ParticleEmitter* emitter : m_Emitters)
		{
			emitter->OnUpdate(ts);
		}
	}

	// Manage emitters' render events
	void ParticleSystem::OnRender()
	{
		for (ParticleEmitter* emitter : m_Emitters)
		{
			emitter->OnRender();
		}
	}

	// Manage emitters' render event
	void ParticleSystem::Emit()
	{
		for (ParticleEmitter* emitter : m_Emitters)
		{
			emitter->Emit();
		}
	}

	//--------------------namespace: Illusion ends--------------------
}