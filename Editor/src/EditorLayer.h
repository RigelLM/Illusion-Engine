#pragma once

#include <Engine.h>
#include "Panels/SceneHierarchyPanel.h"

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

		// Ref<Texture2D> m_CheckBoard;
		// Ref<Texture2D> m_SpriteSheet;

		Ref<SubTexture> m_TextureTree;

		Ref<FBO> m_FBO;

		Ref<Scene> m_ActiveScene;
		Entity m_SqureEntity;

		Entity m_EditorCamera;
		
		glm::vec4 m_Color = { 0.2f, 0.3f, 0.8f, 1.0f };

		//ParticleSystem pSys;
		//ParticleEmitter emitter;
		//ParticleEmitter emitter2;
		//ParticleProp prop;
		//ParticleProp prop2;

		bool m_ViewportFocused = false, m_ViewportHovered = false;

		// Panels
		SceneHierarchyPanel m_SceneHierachyPanel;
	};
}

