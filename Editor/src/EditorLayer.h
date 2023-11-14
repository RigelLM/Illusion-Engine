#pragma once

#include <Engine.h>
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/LogPanel.h"

namespace Illusion
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Timestep timestep) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;

	private:
		glm::vec2 m_ViewportSize = { 0.0f,0.0f };

		Ref<FBO> m_FBO;

		Ref<Scene> m_ActiveScene;
		Entity m_SqureEntity;

		Entity m_EditorCamera;

		Entity m_Logger;

		bool m_ViewportFocused = false, m_ViewportHovered = false;

		// Panels
		SceneHierarchyPanel m_SceneHierachyPanel;
		LogPanel m_LogPanel;
	};
}

