/*
 * ========================== ParticleSystem.h ============================
 *								 -- ils --
 *													   CREATE -- 2023.01.25
 *													   MODIFY --
 * ------------------------------------------------------------------------
 * The ParticleSystem Class
 * Manages all emitters
 * ----------------------------
 */

#pragma once

#include "Engine/Render/ParticleSystem/ParticleEmitter.h"

//--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	class ParticleSystem
	{
	public:

		ParticleSystem();

		// Add emitter to the vector
		void AddEmitter(ParticleEmitter* emitter);

		// Update all emitters
		void OnUpdate(Timestep ts);

		// Manage emitters' render events
		void OnRender();

		// Manage emitters' render event
		void Emit();

	private:

		// All emitters
		std::vector<ParticleEmitter*> m_Emitters;
	};
	//--------------------namespace: Illusion ends--------------------
}
