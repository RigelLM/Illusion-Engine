#pragma once


/*****************************************************************//**
 * \file   Window.h
 * \brief  Window class, wrapping glfw window
 *
 * \author Mian Li
 * \date   January 2023
 *********************************************************************/

#include "Engine/Core/Core.h"
#include "Engine/Event/Events.h"

#include <GLFW/glfw3.h>

 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		// Constrctor for the struct WindowProps
		WindowProps(const std::string& title = "Illusion Engine",
			unsigned int width = 1600,
			unsigned int height = 1200)
			: Title(title), Width(width), Height(height) {}
	};

	// Window Class
	class Window
	{
	public:
		// Creating a template funtion
		// Input: Event&
		// Output: void
		using EventCallbackFn = std::function<void(Event&)>;

		Window(const WindowProps& props = WindowProps());
		~Window();

		void OnUpdate();

		unsigned int GetWidth() const { return m_Data.Width; }
		unsigned int GetHeight() const { return m_Data.Height; }

		// Set the overall event callback function
		void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled);
		bool IsSync() const;

		// Expose the m_Window
		virtual GLFWwindow* GetNativeWindow() const { return m_Window; }

	private:
		// Initialize the window properties
		virtual void Init(const WindowProps& props);

		// Shut the window down
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;
		
		// Store all the data that a window maintains
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;

	};
	//--------------------namespace: Illusion ends--------------------
}

