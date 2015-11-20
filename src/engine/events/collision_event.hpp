/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_COLLISION_EVENT
#define INCLUDED_COLLISION_EVENT

#include "ievent.hpp"

namespace StevensDev {
namespace sgde { // Stevens Game Development Events.

/* A collision event. */
class CollisionEvent : public IEvent {
	private:
		/* Data member(s). */
		const float x; // The center of the dispatcher.
		const float y; // ''
		std::string type;
	public:
		/* Constructor(s). */
		CollisionEvent(float x, float y);
		/* Function(s). */
		const float getX() const;
		const float getY() const;
		/* Inherited function(s). */
		// IEvent.
		virtual const std::string& getType() const;
};

}
}

#endif