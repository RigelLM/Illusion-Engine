#include "EditorLayer.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CameraScript.h"
#include "Tracker.h"

#include "StringDataComponent.h"

namespace Illusion
{
	EditorLayer::EditorLayer()
		:Layer("EditorLayer")
	{

	}

	void EditorLayer::OnAttach()
	{
		FBOSpecification fbspec;
		fbspec.Width = 800;
		fbspec.Height = 600;
		fbspec.Attachments = { FBOTextureFormat::RGBA8, FBOTextureFormat::Depth };
		m_FBO = CreateRef<FBO>(fbspec);

		m_ActiveScene = CreateRef<Scene>();

		m_SqureEntity = m_ActiveScene->CreateEntity("Square");
		m_SqureEntity.AddComponent<SpriteComponent>(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

		m_Logger = m_ActiveScene->CreateEntity("Tracker");
		m_Logger.AddComponent<StringDataComponent>();
		m_Logger.AddComponent<NativeScriptComponent>().Bind<Logger>();

		m_EditorCamera = m_ActiveScene->CreateEntity("Editor Camera");
		m_EditorCamera.AddComponent<CameraComponent>();
		m_EditorCamera.AddComponent<NativeScriptComponent>().Bind<CameraController>();

		// Panels
		m_SceneHierachyPanel.SetContext(m_ActiveScene);
		m_LogPanel.SetContext(m_ActiveScene);
	}

	void EditorLayer::OnDetach()
	{

	}

	void EditorLayer::OnUpdate(Timestep timestep)
	{
		m_LogPanel.OnUpdate();

		m_FBO->Bind();

		m_ActiveScene->OnUpdate(timestep);

		m_FBO->Unbind();
	}

	void EditorLayer::OnImGuiRender()
	{
		bool* RunningStatus = Application::GetRunningStatus();

		static bool opt_fullscreen_persistant = true;
		static ImGuiDockNodeFlags opt_flags = ImGuiDockNodeFlags_None;
		bool opt_fullscreen = opt_fullscreen_persistant;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruDockspace, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (opt_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace", RunningStatus, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Dockspace
		ImGuiIO& io = ImGui::GetIO();

		ImGuiStyle& style = ImGui::GetStyle();
		float minWinSizeX = style.WindowMinSize.x;
		style.WindowMinSize.x = 400.0f;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), opt_flags);
		}
		style.WindowMinSize.x = minWinSizeX;

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Quit", NULL, false, RunningStatus != NULL))
					*RunningStatus = false;
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		// The Scene window
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });
		ImGui::Begin("Viewport");

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();

		Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

		ImVec2 viewportSize = ImGui::GetContentRegionAvail();
		if (m_ViewportSize != glm::vec2{ viewportSize.x, viewportSize.y })
		{
			m_FBO->Resize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
			m_ViewportSize = { viewportSize.x, viewportSize.y };
		}

		uint32_t texture = m_FBO->GetColorAttachment();
		ImGui::Image((void*)(uint64_t)texture, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0,1 }, ImVec2{ 1,0 });
		ImGui::End();
		ImGui::PopStyleVar();

		// Panels

		m_SceneHierachyPanel.OnImGuiRender();
		m_LogPanel.OnImGuiRender();
		
		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& e)
	{
		m_ActiveScene->OnEvent(e);
	}
}
