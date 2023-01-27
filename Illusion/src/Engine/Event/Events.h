/*
 * ========================== Events.h ==========================
 *                          -- ils --
 *                                           CREATE -- 2023.01.12
 *                                           MODIFY --
 * ---------------------------------------------------------------
 * Events abstract class
 * EventDispatcher class
 * ----------------------------
 * 
 */

#pragma once

#include "pch.h"
#include "Engine/Core/Core.h"

//--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	enum class EventType 
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// Implemented in BitField
	// Like many flags, representing categories
	// An event could be in two or more category at the same time
	// 
	// Example:
	// 
	// EventCategoryMouseButton | EventCategoryMouse | EventCategoryInput
	// =>10000 | 1000 | 10
	// =>10000 | 01000 | 00010
	// =>11010
	enum EventCategory 
	{
		None = 0,
		EventCategoryApplication		= BIT(0), //1
		EventCategoryInput				= BIT(1), //10
		EventCategoryKeyboard			= BIT(2), //100
		EventCategoryMouse				= BIT(3), //1000
		EventCategoryMouseButton		= BIT(4)  //10000
	};

	//Macros used to implement GetStaticType/GetEventType/GetName/GetCategoryFlags in the inherited class
	// # is used to transform type into a string
	// GetStaticType can be used as a static method, could be used without an object
	// GetEventType can be used as a property method, can only be used with an instance/object
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }


	// Abstract event class
	// All kinds of events inherates from event

	class Event
	{
		// Make the Dispatcher to be a friend class
		// Authorize the Dispatcher to edit m_Handled
		friend class EventDispatcher;

	public:
		// = 0 means pure virtual/ it has to be implemented elsewhere in inherited class
		// const means the function would not change the property of the class
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags()const = 0;
		virtual std::string ToString() const { return GetName(); }

		// Check whether the input is in certain category
		inline bool IsInCategory(EventCategory category)
		{
			// GetCategoryFlags returns flags Such as 10000/01000/00001
			// category usually used as EventCategoryMouseButton | EventCategoryMouse | EventCategoryInput
			// the code is equivelent to (example):
			// return 10000 & 11010, which is 10000
			// For bool, if there's at least on bit not 0, the return would be true.
			return GetCategoryFlags() & category;
		}

		// Check whether the event still have to be handled
		bool m_Handled = false;
	};


	// Class Event Dispatcher
	class EventDispatcher
	{
		// Define EventFn() Template
		// Input: T&
		// Output: bool
		template<typename T>
		// Set EventFn as another name for std::function<bool(T&)>
		using EventFn = std::function<bool(T&)>;

	public:
		// Bind the event to the dispatcher
		// Each dispatcher could only bind with one kind of event
		EventDispatcher(Event& event)
			: m_Event(event) {}

		// Make a template funtion to dipatche the event
		// Input: a function
		// Output: bool
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			// Compare the bound event with the input event associated with the function
			// GetStaticType is implemented in class inherited from Event, in this context it is T
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				// Call the input function with *(T*)&m_Event, which means:
				// &m_Event		= the address of the event bound to the dipatcher
				// (T*)			= the cast to the pointer towards the type T
				// *			= dereference the pointer
				// The output of the function determins wheter to consume the event or not
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

	//--------------------namespace: Illusion ends--------------------
}