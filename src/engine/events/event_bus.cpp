/*
	Dominik Jedruszczak

	event_bus.cpp
	Implementation of the "EventBus" singleton.
*/

#include "event_bus.hpp"

namespace StevensDev {
namespace sgde { // Stevens Game Development Events.

MappedEventDispatcher& EventBus::getDispatcher() {
	static MappedEventDispatcher mappedEventDispatcher;

	return mappedEventDispatcher;
}

}
}