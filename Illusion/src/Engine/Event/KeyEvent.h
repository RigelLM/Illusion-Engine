#pragma once

/*****************************************************************//**
 * \file   KeyEvent.h
 * \brief  All key input events
 * 
 * \author Mian Li
 * \date   January 2023
 *********************************************************************/

#include "Events.h"
#include "Engine/Core/Input/KeyCode.h"

 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	// KeyEvent
	class KeyEvent : public Event
	{
	public:
		KeyCode GetKeyCode() const { return m_KeyCode; }

		// Bint it with EventCategoryKeyboard and EventCategoryInput
		// Implements this function:
		// virtual int GetCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		// Bind it with a certain key
		KeyEvent(const KeyCode keycode)
			: m_KeyCode(keycode) {}

		KeyCode m_KeyCode;
	};

	// Keypressed Event
	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(const KeyCode keycode, int repeatCount)
			:KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		// Bind it to KeyPressed EventType
		// Implements these functions: 
		// static EventType GetStaticType() { return EventType::KeyPressed; }
		// virtual EventType GetEventType() const override { return GetStaticType(); }
		// virtual const char* GetName() const override { return "KeyPressed"; }
		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_RepeatCount;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(const KeyCode keycode)
			: KeyEvent(keycode) {}


		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		// Bind it to KeyReleased EventType
		// Implements these functions: 
		// static EventType GetStaticType() { return EventType::KeyReleased; }
		// virtual EventType GetEventType() const override { return GetStaticType(); }
		// virtual const char* GetName() const override { return "KeyReleased"; }
		EVENT_CLASS_TYPE(KeyReleased)
	};


	// Keytyped Event
	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(const KeyCode keycode)
			:KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		// Bind it to KeyTyped EventType
		// Implements these functions: 
		// static EventType GetStaticType() { return EventType::KeyTyped; }
		// virtual EventType GetEventType() const override { return GetStaticType(); }
		// virtual const char* GetName() const override { return "KeyTyped"; }
		EVENT_CLASS_TYPE(KeyTyped)

	};
	//--------------------namespace: Illusion ends--------------------
}