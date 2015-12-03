/*
	Dominik Jedruszczak
*/

#include "collidable_box.hpp"

namespace StevensDev {
namespace mgcl { // My Game Collidables.

CollidableBox::CollidableBox(sgds::IActor* actor)
:	actor(actor),
	rectangleBounds(0, 0, 64, 64) {
	;
}

CollidableBox::CollidableBox(sgds::IActor* actor, unsigned short flags)
:	actor(actor),
	flags(flags),
	rectangleBounds(0, 0, 64, 64) {
	;
}

void CollidableBox::moveBounds(float x, float y) {
	rectangleBounds.setPosition(
		rectangleBounds.getX() + x,
		rectangleBounds.getY() + y);
}

sgds::IActor* CollidableBox::getActor() {
	return actor;
}

const sgds::RectangleBounds& CollidableBox::getBounds() const {
	return rectangleBounds;
}

unsigned short CollidableBox::getFlags() const {
	return flags;
}

bool CollidableBox::canCollide(const unsigned short flags) const {
	return this->flags & flags;
}

bool CollidableBox::collides(const sgds::RectangleBounds& rectangleBounds) const {
	return this->rectangleBounds.collides(rectangleBounds);
}


}
}