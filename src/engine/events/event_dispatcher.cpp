/*
	Dominik Jedruszczak

	event_dispatcher.cpp
	Implementation of the "EventDispatcher" class.
*/

#include "event_dispatcher.hpp"

namespace StevensDev {
namespace sgde { //Stevens Game Development Events.

EventDispatcher::EventDispatcher() {
	;
}

EventDispatcher::EventDispatcher(const EventDispatcher& eventDispatcher)
:	listeners(eventDispatcher.listeners),
	addedListeners(eventDispatcher.addedListeners),
	removedListeners(eventDispatcher.removedListeners) {
	;
}

EventDispatcher::EventDispatcher(EventDispatcher&& eventDispatcher)
:	listeners(std::move(eventDispatcher.listeners)),
	addedListeners(std::move(eventDispatcher.addedListeners)),
	removedListeners(std::move(eventDispatcher.removedListeners)) {
	;
}

EventDispatcher& EventDispatcher::operator = (const EventDispatcher& eventDispatcher) {
	listeners = eventDispatcher.listeners;
	addedListeners = eventDispatcher.addedListeners;
	removedListeners = eventDispatcher.removedListeners;
}

EventDispatcher& EventDispatcher::operator = (EventDispatcher&& eventDispatcher) {
	listeners = std::move(eventDispatcher.listeners);
	addedListeners = std::move(eventDispatcher.addedListeners);
	removedListeners = std::move(eventDispatcher.removedListeners);
}

void EventDispatcher::addListener(std::function< void(const IEvent&) >* listener) {
	addedListeners.append(listener);
}

void EventDispatcher::removeListener(std::function< void(const IEvent&) >* listener) {
	removedListeners.append(listener);
}

void EventDispatcher::dispatch(const IEvent& event) {
	for (unsigned int i = 0; i < listeners.getSize(); i++) {
		(*listeners.get(i))(event);
	}
}

void EventDispatcher::preTick() {
	;
}

void EventDispatcher::tick(float deltaTime) {
	;
}

void EventDispatcher::postTick() {
	/* Add the added listeners. */
	for (unsigned int i = 0; i < addedListeners.getSize(); i++) {
		listeners.append(addedListeners.get(i));
	}

	/* Remove the removed listeners. */
	for (unsigned int i = 0; i < removedListeners.getSize(); i++) {
		for (unsigned int j = 0; j < listeners.getSize(); j++) {
			if (removedListeners.get(i) == listeners.get(j)) {
				listeners.remove(j);
			}
		}
	}
}

}
}