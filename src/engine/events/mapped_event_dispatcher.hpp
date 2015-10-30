/*
	Dominik Jedruszczak

	mapped_event_dispatcher.hpp
	Declaration of the "MappedEventDispatcher" class.
	This will likely replace the current "EventDispatcher" class.
*/

#ifndef INCLUDED_MAPPED_EVENT_DISPATCHER
#define INCLUDED_MAPPED_EVENT_DISPATCHER

#include "../scene/itickable.hpp"
#include "ievent.hpp"
#include <functional>
#include "../containers/dynamic_array.hpp"
#include "../containers/map.hpp"

namespace StevensDev {
namespace sgde { // Stevens Game Development Events.

/* An event dispatcher with events mapped to listeners. */
class MappedEventDispatcher : public sgds::ITickable {
	private:
		/* Class(es). */
		class Mapping {
			private:
				/* Data member(s). */
				std::string event;
				std::function< void(const IEvent*) >* listener;
			public:
				/* Constructor(s). */
				Mapping();
				Mapping(
					const std::string& event,
					std::function< void(const IEvent*) >* listener);
				Mapping(const Mapping& mapping);
				Mapping(Mapping&& mapping);
				/* Operator(s). */
				Mapping& operator = (const Mapping& mapping);
				Mapping& operator = (Mapping&& mapping);
				/* Function(s). */
				const std::string& getEvent() const;
				std::function< void(const IEvent*) >* getListener() const;
		};
		/* Data member(s). */
		sgdc::Map<
			sgdc::DynamicArray<
				std::function<
					void(const IEvent*) >* >* > listeners;
		sgdc::DynamicArray< Mapping > addedMappings;
		sgdc::DynamicArray< Mapping > removedMappings;
		sgdc::DynamicArray< const IEvent* > events;
		sgdc::DynamicArray< const IEvent* > addedEvents;
		sgdc::DynamicArray< const IEvent* > removedEvents;
	public:
		/* Constructor(s). */
		MappedEventDispatcher();
		MappedEventDispatcher(const MappedEventDispatcher& mappedEventDispatcher);
		MappedEventDispatcher(MappedEventDispatcher&& mappedEventDispatcher);
		/* Operator(s). */
		MappedEventDispatcher& operator = (const MappedEventDispatcher& mappedEventDispatcher);
		MappedEventDispatcher& operator = (MappedEventDispatcher&& mappedEventDispatcher);
		/* Function(s). */
		void preTick();
		void tick(float deltaTime);
		void postTick();
		void addListener(
			const IEvent* event,
			std::function< void(const IEvent*) >* listener);
		void removeListener(
			const IEvent* event,
			std::function< void(const IEvent*) >* listener);
		void addEvent(const IEvent* event);
		void removeEvent(const IEvent* event);
};

}
}

#endif