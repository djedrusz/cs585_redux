/*
	Dominik Jedruszczak
*/

/* Includes. */
// Local.
#include "wall.hpp"

namespace StevensDev {
namespace mga { // My Game Actors.

Wall::Wall(float x, float y)
:	collidableBox(mgcl::CollidableBox(this, WALL_FLAGS)) {
	collidableBox.moveBounds(x, y);
	renderableSprite.move(x, y);
}

sgdr::RenderableSprite* Wall::getRenderableSprite() {
	return &renderableSprite;
}

sgds::ICollidable* Wall::getCollidable() {
	return &collidableBox;
}

sgde::MappedEventDispatcher* Wall::getEventDispatcher() {
	return &mappedEventDispatcher;
}

}
}