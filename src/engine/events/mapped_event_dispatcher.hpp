/*
	Dominik Jedruszczak

	mapped_event_dispatcher.hpp
	Declaration of the "MappedEventDispatcher" class.
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
				const IEvent* event;
				const std::function< void(const IEvent*) >* listener;
			public:
				/* Constructor(s). */
				Mapping();
				Mapping(
					const IEvent* event,
					const std::function< void(const IEvent*) >* listener);
				Mapping(const Mapping& mapping);
				Mapping(Mapping&& mapping);
				/* Operator(s). */
				Mapping& operator = (const Mapping& mapping);
				Mapping& operator = (Mapping&& mapping);
				/* Function(s). */
				const IEvent* getEvent() const;
				const std::function< void(const IEvent*) >* getListener() const;
		};
		/* Data member(s). */
		sgdc::Map<
			sgdc::DynamicArray<
				const std::function<
					void(const IEvent*) >* >* > listeners;
		sgdc::DynamicArray< Mapping > addedMappings;
		sgdc::DynamicArray< Mapping > removedMappings;
	public:
		/* Constructor(s). */
		MappedEventDispatcher();
		MappedEventDispatcher(const MappedEventDispatcher& mappedEventDispatcher);
		MappedEventDispatcher(MappedEventDispatcher&& mappedEventDispatcher);
		/* Destructor(s). */
		~MappedEventDispatcher();
		/* Operator(s). */
		MappedEventDispatcher& operator = 
			(const MappedEventDispatcher& mappedEventDispatcher);
		MappedEventDispatcher& operator = 
			(MappedEventDispatcher&& mappedEventDispatcher);
		/* Function(s). */
		void preTick();
		void tick(float deltaTime);
		void postTick();
		void addListener(
			const IEvent* event,
			const std::function< void(const IEvent*) >* listener);
		void removeListener(
			const IEvent* event,
			const std::function< void(const IEvent*) >* listener);
		void dispatch(const IEvent* event);
};

}
}

#endif