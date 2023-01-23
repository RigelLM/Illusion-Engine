/*
 * ========================== AppEvent.h ==========================
 *                           -- ils --
 *                                             CREATE -- 2023.01.12
 *                                             MODIFY --
 * ---------------------------------------------------------------
 * AppEvent
 * ----------------------------
 */
#pragma once

#include "Events.h"

 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	// Window Resize Event
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }
		
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		// Bind it to WindowResize EventType
		// Implements these functions: 
		// static EventType GetStaticType() { return EventType::WindowResize; }
		// virtual EventType GetEventType() const override { return GetStaticType(); }
		// virtual const char* GetName() const override { return "WindowResize"; }
		EVENT_CLASS_TYPE(WindowResize)
		// Bint it with EventCategoryApplication
		// Implements this function:
		// virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		unsigned int m_Width, m_Height;
	};

	// Window Close Event
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}
		// Bind it to WindowClose EventType
		// Implements these functions: 
		// static EventType GetStaticType() { return EventType::WindowClose; }
		// virtual EventType GetEventType() const override { return GetStaticType(); }
		// virtual const char* GetName() const override { return "WindowClose"; }
		EVENT_CLASS_TYPE(WindowClose)
		// Bint it with EventCategoryApplication
		// Implements this function:
		// virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	// App Tick Event
	class AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		// Bind it to AppTick EventType
		// Implements these functions: 
		// static EventType GetStaticType() { return EventType::AppTick; }
		// virtual EventType GetEventType() const override { return GetStaticType(); }
		// virtual const char* GetName() const override { return "AppTick"; 
		EVENT_CLASS_TYPE(AppTick)
		// Bint it with EventCategoryApplication
		// Implements this function:
		// virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	// App Update Event
	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		// Bind it to AppUpdate EventType
		// Implements these functions: 
		// static EventType GetStaticType() { return EventType::AppUpdate; }
		// virtual EventType GetEventType() const override { return GetStaticType(); }
		// virtual const char* GetName() const override { return "AppUpdate"; 
		EVENT_CLASS_TYPE(AppUpdate)
		// Bint it with EventCategoryApplication
		// Implements this function:
		// virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	// App Render Event
	class AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		// Bind it to AppRender EventType
		// Implements these functions: 
		// static EventType GetStaticType() { return EventType::AppRender; }
		// virtual EventType GetEventType() const override { return GetStaticType(); }
		// virtual const char* GetName() const override { return "AppRender"; 
		EVENT_CLASS_TYPE(AppRender)
		// Bint it with EventCategoryApplication
		// Implements this function:
		// virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}
