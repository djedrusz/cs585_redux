/*
	Dominik Jedruszczak

	mapped_event_dispatcher.cpp
	Implemention of the "MappedEventDispatcher" class.
	This will likely replace the current "EventDispatcher" class.
*/

#include "mapped_event_dispatcher.hpp"

namespace StevensDev {
namespace sgde { // Stevens Game Development Events.

MappedEventDispatcher::Mapping::Mapping()
:	event(NULL),
	listener(NULL) {
	;
}

MappedEventDispatcher::Mapping::Mapping(
	const IEvent* event,
	const std::function< void(const IEvent*) >* listener)
:	event(event),
	listener(listener) {
	;
}

MappedEventDispatcher::Mapping::Mapping(const Mapping& mapping)
:	event(mapping.event),
	listener(listener) {
	;
}

MappedEventDispatcher::Mapping::Mapping(Mapping&& mapping)
:	event(mapping.event),
	listener(listener) {
	;
}

MappedEventDispatcher::Mapping&
MappedEventDispatcher::Mapping::operator = (const Mapping& mapping) {
	event = mapping.event;
	listener = mapping.listener;
}

MappedEventDispatcher::Mapping&
MappedEventDispatcher::Mapping::operator = (Mapping&& mapping) {
	event = mapping.event;
	listener = mapping.listener;
}

const IEvent* 
MappedEventDispatcher::Mapping::getEvent() const {
	return event;
}

const std::function< void(const IEvent*) >* 
MappedEventDispatcher::Mapping::getListener() const {
	return listener;
}

MappedEventDispatcher::MappedEventDispatcher() {
	;
}

MappedEventDispatcher::MappedEventDispatcher(
	const MappedEventDispatcher& mappedEventDispatcher)
:	listeners(mappedEventDispatcher.listeners),
	events(mappedEventDispatcher.events),
	addedMappings(mappedEventDispatcher.addedMappings),
	removedMappings(mappedEventDispatcher.removedMappings) {
	;
}

MappedEventDispatcher::MappedEventDispatcher(
	MappedEventDispatcher&& mappedEventDispatcher)
:	listeners(std::move(mappedEventDispatcher.listeners)),
	events(std::move(mappedEventDispatcher.events)),
	addedMappings(std::move(mappedEventDispatcher.addedMappings)),
	removedMappings(std::move(mappedEventDispatcher.removedMappings)) {
	;
}

MappedEventDispatcher::~MappedEventDispatcher() {
	for (unsigned int i = 0; i < listeners.getKeys().getSize(); i++) {
		delete listeners.get(listeners.getKeys().get(i));
	}
}

MappedEventDispatcher& MappedEventDispatcher::operator = 
	(const MappedEventDispatcher& mappedEventDispatcher) {
	listeners = mappedEventDispatcher.listeners;
	events = mappedEventDispatcher.events;
	addedMappings = mappedEventDispatcher.addedMappings;
	removedMappings = mappedEventDispatcher.removedMappings;
}

MappedEventDispatcher& MappedEventDispatcher::operator = 
	(MappedEventDispatcher&& mappedEventDispatcher) {
	listeners = std::move(mappedEventDispatcher.listeners);
	events = std::move(mappedEventDispatcher.events);
	addedMappings = std::move(mappedEventDispatcher.addedMappings);
	removedMappings = std::move(mappedEventDispatcher.removedMappings);
}

void MappedEventDispatcher::preTick() {
	/* Add the added mappings. */
	for (unsigned int i = 0; i < addedMappings.getSize(); i++) {
		if (!listeners.has(addedMappings.get(i).getEvent()->getType())) {
			listeners.put(
				addedMappings.get(i).getEvent()->getType(),
				new sgdc::DynamicArray<
						const std::function<
							void(const IEvent*) >* >());
		}
		listeners.get(addedMappings.get(i).getEvent()->getType())->append(addedMappings.get(i).getListener());
	}
	addedMappings = std::move(sgdc::DynamicArray< Mapping >());

	/* Add the added events. */
	for (unsigned int i = 0; i < addedEvents.getSize(); i++) {
		events.append(addedEvents.get(i));
	}
	addedEvents = std::move(sgdc::DynamicArray< const IEvent* >());
}

void MappedEventDispatcher::tick(float deltaTime) {
	for (unsigned int i = 0; i < events.getSize(); i++) {
		if (listeners.has(events.get(i)->getType())) {
			for (unsigned int j = 0; 
				j < listeners.get(events.get(i)->getType())->getSize(); 
				j++) {
				(*listeners.get(events.get(i)->getType())->get(j))(events.get(i));
			}
		}
	}
	events = std::move(sgdc::DynamicArray< const IEvent* >());
}

void MappedEventDispatcher::postTick() {
	/* Remove the removed mappings. */
	for (unsigned int i = 0; i < removedMappings.getSize(); i++) {
		if (listeners.has(removedMappings.get(i).getEvent()->getType())) {
			for (unsigned int j = 0;
				j < listeners.get(removedMappings.get(i).getEvent()->getType())->getSize();
				j++) {
				if (listeners.get(removedMappings.get(i).getEvent()->getType())->get(j)
					== removedMappings.get(i).getListener()) {
					listeners.get(removedMappings.get(i).getEvent()->getType())->remove(j);
					j--;
				}
			}
			if (listeners.get(removedMappings.get(i).getEvent()->getType())->getSize() == 0) {
				delete listeners.get(removedMappings.get(i).getEvent()->getType());
				listeners.remove(removedMappings.get(i).getEvent()->getType());
			}
		}
	}
	removedMappings = std::move(sgdc::DynamicArray< Mapping >());

	/* Remove the removed events. */
	for (unsigned int i = 0; i < removedEvents.getSize(); i++) {
		for (unsigned int j = 0; j < events.getSize(); j++) {
			if (removedEvents.get(i) == events.get(j)) {
				events.remove(j);
				j--;
			}
		}
	}
	removedEvents = std::move(sgdc::DynamicArray< const IEvent* >());
}

void MappedEventDispatcher::addListener(
	const IEvent* event,
	const std::function< void(const IEvent*) >* listener) {
	addedMappings.append(Mapping(event, listener));
}

void MappedEventDispatcher::removeListener(
	const IEvent* event,
	const std::function< void(const IEvent*) >* listener) {
	removedMappings.append(Mapping(event, listener));
}

void MappedEventDispatcher::addEvent(const IEvent* event) {
	addedEvents.append(event);
}

void MappedEventDispatcher::removeEvent(const IEvent* event) {
	removedEvents.append(event);
}

}
}