/*
 * ===================== Application.cpp ======================
 *                         -- ils --
 *                                         CREATE -- 2023.01.12
 *                                         MODIFY --
 * ------------------------------------------------------------
 * The application class
 * Connect the Engine with the Game
 * Responsible for the runnin of the game
 * ----------------------------
 */

#include "pch.h"
#include "Application.h"

#include "Engine/Core/Input/Input.h"
#include "Engine/Render/Renderer/Renderer.h"
#include "Engine/Core/Log/Log.h"

#include <GLFW/glfw3.h>

 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		ILLUSION_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		// Create a window
		m_Window = std::unique_ptr<Window>(Window::CreateIllusionWindow());

		// Bind OnEvent as a overall callback function glfw
		// The program would call OnEvent whenever there's an event
		m_Window->SetEventCallback(ENGINE_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		// Push the layer into the layerstack and call it to do some prepare work
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		// Push the overlay layer into the layerstack and call it to do some prepare work
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	// The overall callback function
	void Application::OnEvent(Event& event)
	{
		// Create a dispatcher which is bound to event
		EventDispatcher dispatcher(event);

		// If the event is OnWindowClose, the dispatcher would dispatch it and call the OnWindowClose function
		dispatcher.Dispatch<WindowCloseEvent>(ENGINE_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(ENGINE_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*(--it))->OnEvent(event);
			if (event.m_Handled)
				break;
		}
	}

	// The callback function to close the window
	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		m_Running = false;
		return true;
	}

	// The callback function to resize the window
	bool Application::OnWindowResize(WindowResizeEvent& event)
	{
		if (event.GetWidth() == 0 || event.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;

		Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());

		return false;
	}

	//The function where the app actually starts
	void Application::Run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime(); // Platform::GetTime();
			Timestep m_Timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				// Update Objects in the game base on the Layer order
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(m_Timestep);
			}

			// Render all ImGui windows
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			// Update everything
			m_Window->OnUpdate();
		}
	}
	//--------------------namespace: Illusion ends--------------------
}