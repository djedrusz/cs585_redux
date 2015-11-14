/*
	Dominik Jedruszczak
*/

#include "collidable_box.hpp"

namespace StevensDev {
namespace mgcl { // My Game Collidables.

CollidableBox::CollidableBox()
:	rectangleBounds(0, 0, 64, 64) {
	;
}

void CollidableBox::moveBounds(float x, float y) {
	rectangleBounds.setPosition(
		rectangleBounds.getX() + x,
		rectangleBounds.getY() + y);
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
	return false;
}


}
}