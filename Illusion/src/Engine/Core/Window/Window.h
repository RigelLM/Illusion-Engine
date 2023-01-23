/*
 * ======================= Window.h ===========================
 *						  -- ils --
 *                                         CREATE -- 2023.01.12
 *                                         MODIFY --
 * ------------------------------------------------------------
 * The abstract Window class for all platforms
 * ----------------------------
 */
#pragma once

#include "pch.h"

#include "Engine/Core/Core.h"
#include "Engine/Event/Events.h"

 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	// The Window properties
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

	// The abstact class Window for all platforms
	class Window
	{
	public:
		// Creating a template funtion
		// Input: Event&
		// Output: void
		using EventCallbackFn = std::function<void(Event&)>;
		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsSync() const = 0;

		// Expose the m_Window
		virtual void* GetNativeWindow() const = 0;

		static Window* CreateIllusionWindow(const WindowProps& props = WindowProps());
	};

	//--------------------namespace: Illusion ends--------------------
}