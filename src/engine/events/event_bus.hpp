/*
	Dominik Jedruszczak

	event_bus.hpp
	Declaration of the "EventBus" singleton.
*/

#ifndef INCLUDED_EVENT_BUS
#define INCLUDED_EVENT_BUS

#include "event_dispatcher.hpp"

namespace StevensDev {
namespace sgde { // Stevens Game Development Events.

/* An event dispatcher singleton. */
class EventBus {
	private:
		/* Constructor(s). */
		EventBus() = delete;
		EventBus(const EventBus& eventBus) = delete;
		/* Operator(s). */
		EventBus& operator = (const EventBus& eventBus) = delete;
	public:
		/* Function(s). */
		static EventDispatcher& getDispatcher();
};

}
}

#endif