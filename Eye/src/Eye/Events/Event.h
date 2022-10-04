#pragma once

#include "eyepch.h"
#include "Eye/Core/Core.h"

namespace Eye
{

	// Events in Eye Engine are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to **buffer** events in an event
	// bus and process them during the "event" part of the update stage.

	// Event Type defination
	enum class EventType
	{
		None = 0,
		// Window Events ( Application Category )
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		// Application Events ( Application Category )
		AppTick, AppUpdate, AppRender,
		// Key Events ( Keyboard + Input Category )
		KeyPressed, KeyReleased, KeyTyped,
		// Mouse Events ( Mouse/MouseButton + Input Category )
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// Event Category for filtering event
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput       = BIT(1),
		EventCategoryKeyboard    = BIT(2),
		EventCategoryMouse       = BIT(3),
		EventCategoryMouseButton = BIT(4),
	};

// macros for easily override virtual functions of Event
// tips: `#` used for stringfication, `##` used for concatenate two tokens
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
							   virtual EventType GetEventType() const override { return GetStaticType(); }\
                               virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class EYE_API Event
	{
	public:
		bool Handled = 0;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category; // because all categories are bit
		}
	};

	// Dispatch an event depend on its type
	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event) {}

		template<typename T, typename F>
		bool Dispatch(F& func)
		{
			// if type of the event == the type of the func event param
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(static_cast<T&>(m_Event)); // cast from &Event to &XXXEvent
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
}
