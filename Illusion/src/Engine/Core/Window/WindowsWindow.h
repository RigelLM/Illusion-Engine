
/*
 * ===================== WindowsWindow.h ========================
 *                         -- ils --
 *                                         CREATE -- 2023.01.12
 *                                         MODIFY --
 * ------------------------------------------------------------
 * The WindowsWindow class for Windows platform
 * ----------------------------
 */
#pragma once

#include "Window.h"

#include "Engine/Render/Utils/GraphicContext.h"

 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	// WindowsWindow Class
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		// Set the overall event callback function
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsSync() const override;

		// Expose the m_Window
		inline virtual void* GetNativeWindow() const { return m_Window; }

	private:
		// Initialize the window properties
		virtual void Init(const WindowProps& props);

		// Shut the window down
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;

		GraphicContext* m_Context;
		
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

