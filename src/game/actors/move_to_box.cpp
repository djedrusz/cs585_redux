/*
	Dominik Jedruszczak
*/

#include "move_to_box.hpp"

namespace StevensDev {
namespace mga { // My Game Actors.

MoveToBox::MoveToBox() 
:	collidableBox(mgcl::CollidableBox(this)) {
}

void MoveToBox::move(float x, float y) {
	renderableSprite.move(x, y);
	collidableBox.moveBounds(x, y);
}

sgdr::RenderableSprite* MoveToBox::getRenderableSprite() {
	return &renderableSprite;
}

sgds::ICollidable* MoveToBox::getCollidable() {
	return &collidableBox;
}

sgde::MappedEventDispatcher* MoveToBox::getEventDispatcher() {
	return &mappedEventDispatcher;
}


}
}