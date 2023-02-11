#pragma once

#include "Engine/Render/Utils/Texture.h"

#include <glm/glm.hpp>

namespace Illusion
{
	class SequenceAnimation
	{

	public:

		SequenceAnimation(uint32_t framecount, const std::string& filepath, const std::string& name);
		~SequenceAnimation(){}

		void Play(glm::vec3 loc, glm::vec2 size, float time, bool once);
		void Play(glm::vec3 loc, glm::vec2 size, float time);

		const bool Check() { return m_End; }

	private:

		uint32_t m_FrameCount;
		float m_CurrentFrame;

		// Store the file path for the animation
		std::string m_FolderPath;
		std::string m_Name;

		std::vector<Ref<Texture2D>> m_Frames;

		bool m_End = false;
	};

}
