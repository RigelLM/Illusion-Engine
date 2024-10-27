#pragma once

/*****************************************************************//**
 * \file   Scene.h
 * \brief  Scene class that represents the level of the game
 * 
 * \author Mian Li
 * \date   October 2024
 *********************************************************************/

#include "entt.hpp"
#include <Engine/Event/Events.h>
#include <Engine/Event/AppEvent.h>
#include <Engine/Core/Utils/Timestep.h>

namespace Illusion
{
	// Forward decleration
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