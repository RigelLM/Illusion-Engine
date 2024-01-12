#pragma once

#include "Engine/Core/ECS/Scene.h"

namespace Illusion
{
	class Serializer
	{
	public:
		Serializer(const Ref<Scene>& scene);

		void Serialize(const std::string& path);

		void Deserialize(const std::string& path);

	private:
		Ref<Scene> m_Scene;

	};

}
