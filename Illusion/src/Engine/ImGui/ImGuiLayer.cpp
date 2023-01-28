/*
 * ======================= ImGuiLayer.h ===========================
 *						     -- ils --
 *												CREATE -- 2023.01.13
 *												MODIFY --
 * ----------------------------------------------------------------
 * The ImGuiLayer Class that stores all the render logic 
 * for the overlay layer
 * ----------------------------
 */


#include "pch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "examples/imgui_impl_glfw.cpp"
#include "examples/imgui_impl_opengl3.h"

#include "Engine/Core/Application/Application.h"

// Temp
#include <GLFW/glfw3.h>
#include <glad/glad.h>


//--------------------namespace: Illusion starts--------------------
namespace Illusion
{

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
		
	}

	ImGuiLayer::~ImGuiLayer()
	{

	}

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
		
		// Set up ImGui Style
		ImGui::StyleColorsDark();

		// When viewports are enabled, tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

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
		static bool show = true;
		//ImGui::ShowDemoWindow(&show);

	}
}//--------------------namespace: Illusion ends--------------------