/*
	Dominik Jedruszczak
*/

/* Includes. */
// Local.
#include "pacman.hpp"

namespace StevensDev {
namespace mga { // My Game Actors.

Pacman::Pacman(float x, float y)
:	collidableBox(mgcl::CollidableBox(this, PACMAN_FLAGS)) {
	collidableBox.moveBounds(x, y);
	renderableSprite.move(x, y);
}

sgdr::RenderableSprite* Pacman::getRenderableSprite() {
	return &renderableSprite;
}

sgds::ICollidable* Pacman::getCollidable() {
	return &collidableBox;
}

sgde::MappedEventDispatcher* Pacman::getEventDispatcher() {
	return &mappedEventDispatcher;
}

void Pacman::move(float x, float y) {
	renderableSprite.move(x, y);
	collidableBox.moveBounds(x, y);
}

}
}