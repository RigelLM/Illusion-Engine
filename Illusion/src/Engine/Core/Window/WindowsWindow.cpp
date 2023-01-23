/*
 * ===================== WindowsWindow.cpp ========================
 *                         -- ils --
 *                                         CREATE -- 2023.01.12
 *                                         MODIFY --
 * ------------------------------------------------------------
 * The WindowsWindow class for Windows platform
 * ----------------------------
 */

#include "pch.h"
#include "WindowsWindow.h"

#include "Engine/Event/AppEvent.h"
#include "Engine/Event/MouseEvent.h"
#include "Engine/Event/KeyEvent.h"

 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	// Make sure GLFW has been initialized when it is called
	static bool s_GLFWInitialized = false;

	// A simple Error processor
	static void GLFWErrorCallback(int error, const char* description)
	{
		ENGINE_CORE_ERROR("GLFW ERROR ({0}): {1}", error, description);
	}

	// Create the Window for the program
	Window* Window::CreateIllusionWindow(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	// The constructor of the WindowsWindow class
	// Initialize the properties of the window
	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	// The destructor of the WindowsWindow class
	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	// Initialization of the properties of the window
	void WindowsWindow::Init(const WindowProps& props)
	{
		// Unpack the data input
		// Store all the data that window maintains
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		// Log the data
		ENGINE_CORE_INFO("Window Created: {0} ({1},{2})", m_Data.Title, m_Data.Width, m_Data.Height);

		// Initialize GLFW
		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			ILLUSION_CORE_ASSERT(success, "Could not intialize GLFW!");
			// Set up the error callback function
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		// Create the window with the data that the window maintains
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		
		m_Context = new GraphicContext(m_Window);
		m_Context->Init();

		// The user pointer could be used to store whatever you what
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW callbacks
		// Use Lambda expressions that generate a callable funtion and set it to be the callback function
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			// Retrieve the data that we stored in the user pointer
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			// Store the change
			data.Width = width;
			data.Height = height;
			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case  GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});


		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});


		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});

	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		// Everytime it is updataed, process the event in the queue
		glfwPollEvents();

		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsSync() const
	{
		return m_Data.VSync;
	}
	//--------------------namespace: Illusion ends--------------------
}