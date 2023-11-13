#include "EditorLayer.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CameraScript.h"

namespace Illusion
{
	EditorLayer::EditorLayer()
		:Layer("EditorLayer")
	{

	}

	void EditorLayer::OnAttach()
	{
		// m_CheckBoard.reset(new Texture2D("assets/textures/CheckerBoard.png"));
		// m_SpriteSheet.reset(new Texture2D("assets/textures/SpriteSheet.png"));
		//m_TextureTree = SubTexture::CreateFromCoords(m_SpriteSheet, { 2 , 1 }, { 128 , 128 }, { 1 , 2 });
		m_FBO.reset(new FBO(800, 600));
		
		m_ActiveScene = CreateRef<Scene>();

		m_SqureEntity = m_ActiveScene->CreateEntity("Square");
		m_SqureEntity.AddComponent<SpriteComponent>(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

		m_EditorCamera = m_ActiveScene->CreateEntity("Editor Camera");
		m_EditorCamera.AddComponent<CameraComponent>();
		m_EditorCamera.AddComponent<NativeScriptComponent>().Bind<CameraController>();

		//// Initialize the particle system with two emitters
		//pSys.AddEmitter(&emitter);
		//pSys.AddEmitter(&emitter2);

		//// Initialize the properties for each emitter
		//prop.ColorBegin = { 255 / 255.0f, 255 / 255.0f, 0 / 255.0f, 1.0f };
		//prop.ColorEnd = { 0 / 255.0f, 255 / 255.0f, 0 / 255.0f, 1.0f };
		//prop.SizeBegin = 0.5f, prop.SizeVariation = 0.3f, prop.SizeEnd = 0.0f;
		//prop.LifeTime = 1.0f;
		//prop.Velocity = { 0.0f, 0.0f };
		//prop.VelocityVariation = { 1.0f, 1.0f };
		//prop.Position = { 0.0f, 0.0f };
		//prop.Scale = 0.2f;

		//prop2.ColorBegin = { 254 / 255.0f, 0 / 255.0f, 0 / 255.0f, 1.0f };
		//prop2.ColorEnd = { 0 / 255.0f, 0 / 255.0f, 255 / 255.0f, 1.0f };
		//prop2.SizeBegin = 0.5f, prop2.SizeVariation = 0.3f, prop2.SizeEnd = 0.0f;
		//prop2.LifeTime = 1.0f;
		//prop2.Velocity = { 0.0f, 0.0f };
		//prop2.VelocityVariation = { 1.0f, 1.0f };
		//prop2.Position = { 0.0f, 0.0f };
		//prop2.Scale = 0.5f;

		// Panels
		m_SceneHierachyPanel.SetContext(m_ActiveScene);
	}

	void EditorLayer::OnDetach()
	{

	}

	void EditorLayer::OnUpdate(Timestep timestep)
	{
		// Update the camera
		// if(m_ViewportHovered)
			//m_CameraController.OnUpdate(timestep);

		//// Update the properties for each emitter
		//if (Input::IsMouseButtonPressed(ILLUSION_MOUSE_BUTTON_LEFT))
		//{
		//	// Figure out the position of the mouse cursor
		//	auto [x, y] = Input::GetMousePosition();
		//	auto width = Application::Get().GetWindow().GetWidth();
		//	auto height = Application::Get().GetWindow().GetHeight();

		//	auto bounds = m_CameraController.GetBounds();
		//	auto pos = m_CameraController.GetCamera().GetPosition();
		//	x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		//	y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
		//	prop.Position = { x + pos.x, y + pos.y };
		//	prop2.Position = { x + pos.x + 0.8f, y + pos.y };

		//	// Assign it to the position of the emitter
		//	emitter.Configure(prop);
		//	emitter2.Configure(prop2);

		//	// Emit 5 particles at once
		//	//for (int i = 0; i < 5; i++)
		//	pSys.Emit();
		//}

		//// Update the particle system
		//pSys.OnUpdate(timestep);

		// Render

		// Set the clear color
		// Clear the color buffer with the clear color

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
		if (opt_flags & ImGuiDockNodeFlags_PassthruDockspace)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", RunningStatus, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Dockspace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), opt_flags);
		}

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

		ImGui::Begin("Settings");
		ImGui::Separator();
		auto tag = m_SqureEntity.GetComponent<TagComponent>().Tag;
		ImGui::Text("%s", tag.c_str());
		auto& squareColor = m_SqureEntity.GetComponent<SpriteComponent>().Color;
		ImGui::ColorEdit3("Square Color", glm::value_ptr(squareColor));
		ImGui::Separator();
		ImGui::End();

		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& e)
	{
		m_ActiveScene->OnEvent(e);
		//m_CameraController.OnEvent(event);
	}
}
