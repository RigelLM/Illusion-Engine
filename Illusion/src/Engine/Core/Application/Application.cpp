/*****************************************************************//**
 * \file   Application.cpp
 * \brief  Appliacton class that connects the engine with
 * the applications, and it is responsible to run the main function
 * 
 * \author Mian Li
 * \date   January 2023
 *********************************************************************/

#include "pch.h"
#include "Application.h"

#include "Engine/Render/Renderer/Renderer2D.h"
#include "Engine/Core/Log/Log.h"

 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	Application* Application::s_Instance = nullptr;

	Application::Application(unsigned int width, unsigned int height)
	{
		ILLUSION_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		// Create a window
		m_Window.reset(new Window(WindowProps("Illusion Editor", width, height)));

		// Bind OnEvent as a overall callback function glfw
		// The program would call OnEvent whenever there's an event
		m_Window->SetEventCallback(ENGINE_BIND_EVENT_FN(Application::OnEvent));

		Renderer2D::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::Application()
	{
		ILLUSION_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		// Create a window
		m_Window.reset(new Window(WindowProps("Illusion Editor", 800, 600)));

		// Bind OnEvent as a overall callback function glfw
		// The program would call OnEvent whenever there's an event
		m_Window->SetEventCallback(ENGINE_BIND_EVENT_FN(Application::OnEvent));

		Renderer2D::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		Renderer2D::Shutdown();
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

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			(*it)->OnEvent(event);
			if (event.m_Handled)
				break;
		}
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

		Renderer2D::OnWindowResize(event.GetWidth(), event.GetHeight());

		return false;
	}
	//--------------------namespace: Illusion ends--------------------
}