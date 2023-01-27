/*
 * ===================== Application.h ========================
 *                         -- ils --
 *                                         CREATE -- 2023.01.12
 *                                         MODIFY --
 * ------------------------------------------------------------
 * The application class
 * Connect the Engine with the Game
 * Responsible for the runnin of the game
 * ----------------------------
 */

#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Core/Layer/LayerStack.h"
#include "Engine/Event/Events.h"
#include "Engine/Event/AppEvent.h"
#include "Engine/Core/Window/Window.h"
#include "Engine/ImGui/ImGuiLayer.h"

#include "Engine/Render/Utils/Shader.h"

#include "Engine/Render/Utils/Buffers.h"
#include "Engine/Render/Utils/VertexArray.h"

#include "Engine/Render/CameraSystem/Camera.h"

#include "Engine/Core/Utils/TimeStep.h"


//--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		//The function where application actually starts
		void Run();

		// Overall callback function
		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; };

		inline static Application& Get() { return *s_Instance; };
	private:
		// Callback function that close the window
		bool OnWindowClose(WindowCloseEvent& event);

		bool OnWindowResize(WindowResizeEvent& event);

	private:
		std::unique_ptr<Window> m_Window;

		bool m_Running = true;

		bool m_Minimized = false;

		ImGuiLayer* m_ImGuiLayer;

		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;

	};

	//The Creation function of the application
	//Should be implement by the user themselves
	//Since we don't know what they will call their apps and what they will do with their apps
	//There cannot be a uniform implementation of the creation function
	//It is implemented in the Game.cpp
	Application* CreateApplication();
//--------------------namespace: Illusion ends--------------------
}
