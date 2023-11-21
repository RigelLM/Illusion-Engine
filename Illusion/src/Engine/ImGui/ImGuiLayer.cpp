/*
 * ======================= ImGuiLayer.h ===========================
 *						     -- ils --
 *												CREATE -- 2023.01.13
 *												MODIFY -- 2023.02.14  
 * ----------------------------------------------------------------
 * The ImGuiLayer Class that stores all the render logic 
 * for the overlay layer
 * ----------------------------
 */

#include "pch.h"

#include "ImGuiLayer.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.cpp"
#include "backends/imgui_impl_opengl3.h"

#include "Engine/Core/Application/Application.h"

//--------------------namespace: Illusion starts--------------------
namespace Illusion
{

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{ }

	ImGuiLayer::~ImGuiLayer()
	{ }

	// Call when it is put into the layerstack
	void ImGuiLayer::OnAttach()
	{
		//Set up the ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		// Enable keyboard controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		// Enable docking
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		// Enable Multi_Viewports
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		
		// Set the default fonts for imgui
		io.Fonts->AddFontFromFileTTF("assets/fonts/OpenSans/static/OpenSans-Bold.ttf", 20.0f);
		io.Fonts->AddFontFromFileTTF("assets/fonts/Recursive/static/Recursive_Monospace-Regular.ttf", 20.0f);
		io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/OpenSans/static/OpenSans-Regular.ttf", 20.0f);

		// Set up ImGui Style
		//ImGui::StyleColorsLight();
		ImGui::StyleColorsDark();

		// When viewports are enabled, tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		SetDarkThemeColor();

		// Setup Platform/Renderer bindings
		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		// Initialize the implementation of OpenGL3
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	// Call when it is taken from the layerstack
	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnEvent(Event& e)
	{
		if (m_BlockEvents)
		{
			ImGuiIO& io = ImGui::GetIO();
			e.m_Handled |= e.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
			e.m_Handled |= e.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
		}
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		// RENDERING
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGuiLayer::OnImGuiRender()
	{
		 /*static bool show = true;
		 ImGui::ShowDemoWindow(&show);*/
	}

	void ImGuiLayer::SetDarkThemeColor()
	{
		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

		// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

		// Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	}
}//--------------------namespace: Illusion ends--------------------