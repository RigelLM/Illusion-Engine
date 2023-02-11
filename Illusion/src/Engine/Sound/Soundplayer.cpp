#include "pch.h"

#include "Soundplayer.h"

namespace Illusion
{

	SoundPlayer::SoundPlayer(std::string source)
		:m_Source(source)
	{
		m_SoundEngine = irrklang::createIrrKlangDevice();
	}

	SoundPlayer::~SoundPlayer()
	{
		m_SoundEngine->drop();
	}

	void SoundPlayer::Play()
	{
		if (m_IsPause)
		{
			m_IsPause = false;
			m_SoundEngine->play2D(m_Source.c_str(), false);
		}
	}

	void SoundPlayer::OnUpdate()
	{
		if (m_IsPause)
			m_SoundEngine->stopAllSounds();
	}

	void SoundPlayer::Pause()
	{
		m_IsPause = true;
	}
}