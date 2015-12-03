/*
	Dominik Jedruszczak
*/

/* Includes. */
// Local.
#include "pacman.hpp"

namespace StevensDev {
namespace mga { // My Game Actors.

Ghost::Ghost(sgdc::DynamicArray< std::pair< float, float > > path)
:	collidableBox(mgcl::CollidableBox(this, GHOST_FLAGS)),
	path(path),
	currentTarget(1) {
	collidableBox.moveBounds(path.get(0).first, path.get(0).second);
	renderableSprite.move(path.get(0).first, path.get(0).second);
}

sgdr::RenderableSprite* Ghost::getRenderableSprite() {
	return &renderableSprite;
}

sgds::ICollidable* Ghost::getCollidable() {
	return &collidableBox;
}

sgde::MappedEventDispatcher* Ghost::getEventDispatcher() {
	return &mappedEventDispatcher;
}

void Ghost::move() {
	float dx = 
		path.get(currentTarget).first
		- collidableBox.getBounds().getX();
	float dy = 
		path.get(currentTarget).second
		- collidableBox.getBounds().getY();
	float distance = sqrt(dx * dx + dy * dy);

	if (distance == 0) {
		currentTarget = (currentTarget + 1) % path.getSize();;
		return;
	}

	dx = dx / distance;
	dy = dy / distance;

	if (GHOST_MOVEMENT_SPEED < distance) {
		dx = GHOST_MOVEMENT_SPEED * dx;
		dy = GHOST_MOVEMENT_SPEED * dy;
	}

	renderableSprite.move(dx, dy);
	collidableBox.moveBounds(dx, dy);
}

}
}