/*****************************************************************//**
 * \file   Application.h
 * \brief   Appliacton class that connects the engine with
 * the applications, and it is responsible to run the main function
 * 
 * \author Mian Li
 * \date   October 2024
 *********************************************************************/

#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Core/Layer/LayerStack.h"
#include "Engine/ImGui/ImGuiLayer.h"
#include "Engine/Event/Events.h"
#include "Engine/Event/AppEvent.h"
#include "Engine/Core/Window/Window.h"

#include "Engine/Render/Utils/Shader.h"

#include "Engine/Render/Utils/Buffers.h"
#include "Engine/Render/Utils/VertexArray.h"

#include "Engine/Core/Utils/TimeStep.h"

int main(int argc, char** argv);
//--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	class Application
	{
	public:
		Application();
		Application(unsigned int width, unsigned int height);

		virtual ~Application();

		//The function where application actually starts
		void Run();

		// Overall callback function
		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);


		// Helper functions
		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		Window& GetWindow() { return *m_Window; };

		static Application& Get() { return *s_Instance; };

		static bool* GetRunningStatus() { return &s_Instance->m_Running; }

	private:
		// Callback function that close the window
		bool OnWindowClose(WindowCloseEvent& event);

		bool OnWindowResize(WindowResizeEvent& event);

	private:
		Scope<Window> m_Window;

		bool m_Running = true;

		bool m_Minimized = false;

		ImGuiLayer* m_ImGuiLayer;

		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;

	private:
		friend int ::main(int argc, char** argv);
	};

	//The Creation function of the application
	//Should be implement by the user themselves
	//Since we don't know what they will call their apps and what they will do with their apps
	//There cannot be a uniform implementation of the creation function
	//It is implemented in the Game.cpp
	Application* CreateApplication();
//--------------------namespace: Illusion ends--------------------
}
