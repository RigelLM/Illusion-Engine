/*
 * ========================== MouseEvent.h ==========================
 *                             -- ils --
 *                                               CREATE -- 2023.01.12
 *                                               MODIFY --
 * ---------------------------------------------------------------
 * MouseEvent
 * ----------------------------
 */

#pragma once

#include "Events.h"

 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	// Mouse Moved Event
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		// Bind it to MouseMoved EventType
		// Implements these functions: 
		// static EventType GetStaticType() { return EventType::MouseMoved; }
		// virtual EventType GetEventType() const override { return GetStaticType(); }
		// virtual const char* GetName() const override { return "MouseMoved"; }
		EVENT_CLASS_TYPE(MouseMoved)
		// Bint it with EventCategoryMouse and EventCategoryInput
		// Implements this function:
		// virtual int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_MouseX, m_MouseY;
	};

	// Mouse Scolled Event
	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		// Bind it to MouseScrolled EventType
		// Implements these functions: 
		// static EventType GetStaticType() { return EventType::MouseScrolled; }
		// virtual EventType GetEventType() const override { return GetStaticType(); }
		// virtual const char* GetName() const override { return "MouseScrolled"; }
		EVENT_CLASS_TYPE(MouseScrolled)
		// Bint it with EventCategoryMouse and EventCategoryInput
		// Implements this function:
		// virtual int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_XOffset, m_YOffset;
	};


	// Mouse Button Event
	class MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_Button; }

		// Bint it with EventCategoryMouse and EventCategoryInput
		// Implements this function:
		// virtual int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		MouseButtonEvent(int button)
			: m_Button(button) {}

		int m_Button;
	};

	// Mouse Button Pressed Event
	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		// Bind it to MouseButtonPressed EventType
		// Implements these functions: 
		// static EventType GetStaticType() { return EventType::MouseButtonPressed; }
		// virtual EventType GetEventType() const override { return GetStaticType(); }
		// virtual const char* GetName() const override { return "MouseButtonPressed"; }
		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	// Mouse Button Released Event
	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		// Bind it to MouseButtonReleased EventType
		// Implements these functions: 
		// static EventType GetStaticType() { return EventType::MouseButtonReleased; }
		// virtual EventType GetEventType() const override { return GetStaticType(); }
		// virtual const char* GetName() const override { return "MouseButtonReleased"; }
		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

	//--------------------namespace: Illusion ends--------------------
}