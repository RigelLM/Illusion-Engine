#pragma once

#include <Engine/Core/Core.h>
#include <Engine/Core/ECS/Scene.h>
#include <Engine/Core/ECS/Entity.h>

namespace Illusion
{
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& context);

		void SetContext(const Ref<Scene>& context);

		void OnImGuiRender();
	
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};
}
