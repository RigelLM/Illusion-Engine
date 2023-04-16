/*
 * ===================== Window.h ========================
 *                         -- ils --
 *                                         CREATE -- 2023.01.12
 *                                         MODIFY --
 * ------------------------------------------------------------
 * The Window class for Windows platform
 * ----------------------------
 */
#pragma once

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
			unsigned int width = 1280,
			unsigned int height = 720)
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

		inline unsigned int GetWidth() const { return m_Data.Width; }
		inline unsigned int GetHeight() const { return m_Data.Height; }

		// Set the overall event callback function
		inline void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled);
		bool IsSync() const;

		// Expose the m_Window
		inline virtual GLFWwindow* GetNativeWindow() const { return m_Window; }

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

