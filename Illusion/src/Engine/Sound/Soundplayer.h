#pragma once

#include <Engine.h>

#include "irrKlang.h"

namespace Illusion 
{
	class SoundPlayer
	{
	public:

		SoundPlayer(std::string source);

		~SoundPlayer();

		void Play();
		
		void OnUpdate();

		void Pause();

	private:

		irrklang::ISoundEngine* m_SoundEngine;

		std::string m_Source;

		bool m_IsPause = true;
	};
}


