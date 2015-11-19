/*
	Dominik Jedruszczak
*/

#include "collidable_box.hpp"

namespace StevensDev {
namespace mgcl { // My Game Collidables.

CollidableBox::CollidableBox(/*const std::string& actorKey*/)
:	/*actorKey(actorKey),*/
	rectangleBounds(0, 0, 64, 64) {
	;
}

void CollidableBox::moveBounds(float x, float y) {
	rectangleBounds.setPosition(
		rectangleBounds.getX() + x,
		rectangleBounds.getY() + y);
}

/*const std::string& CollidableBox::getActorKey() {
	return actorKey;
}*/

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