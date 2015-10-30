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
:	event(""),
	listener(NULL) {
	;
}

MappedEventDispatcher::Mapping::Mapping(
	const std::string& event,
	std::function< void(const IEvent*) >* listener)
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

const std::string& 
MappedEventDispatcher::Mapping::getEvent() const {
	return event;
}

std::function< void(const IEvent*) >* 
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
	/* Add the added mappings. 
	for (unsigned int i = 0; i < addedMappings.getSize(); i++) {
		if (!listeners.has(addedMappings[i].getEvent())) {
			listeners.put(
				addedMappings[i].getEvent(),
				std::move(
					sgdc::DynamicArray< 
						std::function< 
							void(const IEvent*) >* >()));
		}
	}
	addedMappings = std::move(sgdc::DynamicArray< Mapping >());*/
	for (unsigned int i = 0; i < addedMappings.getSize(); i++) {
		if (!listeners.has(addedMappings.get(i).getEvent())) {
			listeners.put(
				addedMappings.get(i).getEvent(),
				new sgdc::DynamicArray<
						std::function<
							void(const IEvent*) >* >());
			listeners.get(addedMappings.get(i).getEvent())->append(addedMappings.get(i).getListener());
		}
	}
	addedMappings = std::move(sgdc::DynamicArray< Mapping >());

	/* Add the added events. */
	for (unsigned int i = 0; i < addedEvents.getSize(); i++) {
		events.append(addedEvents.get(i));
	}
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
	/* Remove the removed mappings. 
	for (unsigned int i = 0; i < removedMappings.getSize(); i++) {
		if (listeners.has(removedMappings[i].getEvent())) {
			for (unsigned int j = 0; 
				j < listeners.get(removedMappings[i].getEvent()).getSize(); 
				j++) {
				if (listeners.get(removedMappings[i].getEvent()).get(j)
					== removedMappings[i].getListener()) {
					;
				}
			}
		}
	}
	removedMappings = std::move(sgdc::DynamicArray< Mapping >());*/
	for (unsigned int i = 0; i < removedMappings.getSize(); i++) {
		if (listeners.has(removedMappings.get(i).getEvent())) {
			for (unsigned int j = 0;
				j < listeners.get(removedMappings.get(i).getEvent())->getSize();
				j++) {
				if (listeners.get(removedMappings.get(i).getEvent())->get(j)
					== removedMappings.get(i).getListener()) {
					listeners.get(removedMappings.get(i).getEvent())->remove(j);
					j--;
				}
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
}

void MappedEventDispatcher::addListener(
	const IEvent* event,
	std::function< void(const IEvent*) >* listener) {
	addedMappings.append(Mapping(event->getType(), listener));
}

void MappedEventDispatcher::removeListener(
	const IEvent* event,
	std::function< void(const IEvent*) >* listener) {
	removedMappings.append(Mapping(event->getType(), listener));
}

void MappedEventDispatcher::addEvent(const IEvent* event) {
	addedEvents.append(event);
}

void MappedEventDispatcher::removeEvent(const IEvent* event) {
	removedEvents.append(event);
}

}
}