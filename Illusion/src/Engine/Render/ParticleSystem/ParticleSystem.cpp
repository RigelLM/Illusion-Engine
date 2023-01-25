#include "pch.h"
#include "ParticleSystem.h"

namespace Illusion
{

	ParticleSystem::ParticleSystem()
	{

	}

	void ParticleSystem::AddEmitter(ParticleEmitter* emitter)
	{
		m_Emitters.emplace_back(emitter);
	}

	void ParticleSystem::OnUpdate(Timestep ts)
	{
		for (ParticleEmitter* emitter : m_Emitters)
		{
			emitter->OnUpdate(ts);
		}
	}

	void ParticleSystem::OnRender()
	{
		for (ParticleEmitter* emitter : m_Emitters)
		{
			emitter->OnRender();
		}
	}

	void ParticleSystem::Emit()
	{
		for (ParticleEmitter* emitter : m_Emitters)
		{
			emitter->Emit();
		}
	}


}