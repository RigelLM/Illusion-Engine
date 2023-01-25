#pragma once

#include "Engine/Render/ParticleSystem/ParticleEmitter.h"

namespace Illusion
{
	class ParticleSystem
	{
	public:

		ParticleSystem();

		void AddEmitter(ParticleEmitter* emitter);

		void OnUpdate(Timestep ts);
		void OnRender();

		void Emit();

	private:

		std::vector<ParticleEmitter*> m_Emitters;
	};

}
