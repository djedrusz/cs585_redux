/*
	Dominik Jedruszczak
*/

#include "collision_event.hpp"

namespace StevensDev {
namespace sgde { // Stevens Game Development Events.

CollisionEvent::CollisionEvent(float x, float y)
:	x(x),
	y(y),
	type("collision") {
	;
}

const float CollisionEvent::getX() const {
	return x;
}

const float CollisionEvent::getY() const {
	return y;
}

const std::string& CollisionEvent::getType() const {
	return type;
}

}
}