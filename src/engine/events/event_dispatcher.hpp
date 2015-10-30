/*
	Dominik Jedruszczak

	event_dispatcher.hpp
	Declaration of the "EventDispatcher" class.
*/

#ifndef INCLUDED_EVENT_DISPATCHER
#define INCLUDED_EVENT_DISPATCHER

#include "../scene/itickable.hpp"
#include "ievent.hpp"
#include <functional>
#include "../containers/dynamic_array.hpp"

namespace StevensDev {
namespace sgde { // Stevens Game Development Events.

/* An event dispatcher. */
class EventDispatcher : public sgds::ITickable {
	private:
		/* Data member(s). */
		sgdc::DynamicArray< std::function< void(const IEvent&) >* > listeners;
		sgdc::DynamicArray< std::function< void(const IEvent&) >* > addedListeners;
		sgdc::DynamicArray< std::function< void(const IEvent&) >* > removedListeners;
	public:
		/* Constructor(s). */
		EventDispatcher();
		EventDispatcher(const EventDispatcher& eventDispatcher);
		EventDispatcher(EventDispatcher&& eventDispatcher);
		/* Operator(s). */
		EventDispatcher& operator = (const EventDispatcher& eventDispatcher);
		EventDispatcher& operator = (EventDispatcher&& eventDispatcher);
		/* Function(s). */
		void addListener(std::function< void(const IEvent&) >* listener);
		void removeListener(std::function< void(const IEvent&) >* listener);
		void dispatch(const IEvent& event);
		void preTick();
		void tick(float deltaTime);
		void postTick();
};

}
}

#endif