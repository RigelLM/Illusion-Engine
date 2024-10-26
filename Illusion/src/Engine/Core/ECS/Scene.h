#pragma once

#include "entt.hpp"
#include <Engine/Event/Events.h>
#include <Engine/Event/AppEvent.h>
#include <Engine/Core/Utils/Timestep.h>

namespace Illusion
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());

		void DestroyEntity(Entity entity);

		void OnUpdate(Timestep ts);

		void OnEvent(Event& event);

	private:
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		entt::registry m_Registry;

		friend class Entity;
		friend class SceneHierarchyPanel;
		friend class LogPanel;
		friend class Serializer;
	};

}