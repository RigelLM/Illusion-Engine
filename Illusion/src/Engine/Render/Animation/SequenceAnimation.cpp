#include "pch.h"
#include "SequenceAnimation.h"
#include "Engine/Render/Renderer/Renderer2D.h"
#include <stb_image.h>

namespace Illusion
{
	SequenceAnimation::SequenceAnimation(uint32_t framecount, const std::string& folderpath, const std::string& name)
		:m_FrameCount(framecount), m_CurrentFrame(0.0f), m_FolderPath(folderpath), m_Name(name), m_End(false)
	{
		char filepath[256];
		for (int i = 0; i < m_FrameCount; i++)
		{
			memset(filepath, 0, 256);
			sprintf(filepath, "%s/%s (%d).png", m_FolderPath.c_str(), m_Name.c_str(), i + 1);
			Ref<Texture2D> texture;
			texture.reset(new Texture2D(filepath));
			m_Frames.push_back(texture);
		}
	}

	void SequenceAnimation::Play(glm::vec3 loc, glm::vec2 size, float time, bool once)
	{
		float step = (m_FrameCount / time) / 60;
		Illusion::Renderer2D::DrawQuad(loc, size, m_Frames[(int)m_CurrentFrame]);

		/*m_CurrentFrame = m_CurrentFrame + 16.0f / 60.0f;*/
		m_CurrentFrame += step;
		if (!once)
		{
			if ((uint32_t)m_CurrentFrame == m_FrameCount)
				m_CurrentFrame = 0.0f;
		}
		else
		{
			if ((uint32_t)m_CurrentFrame == m_FrameCount)
			{
				m_CurrentFrame = m_FrameCount - 1;
				m_End = true;
			}
		}
	}

	void SequenceAnimation::Play(glm::vec3 loc, glm::vec2 size, float time)
	{
		float step = (m_FrameCount / time) / 60;
		Illusion::Renderer2D::DrawUIQuad(loc, size, m_Frames[(int)m_CurrentFrame]);

		m_CurrentFrame += step;
		if ((uint32_t)m_CurrentFrame == m_FrameCount)
		{
			m_CurrentFrame = m_FrameCount - 1;
			m_End = true;
		}
	}
}
