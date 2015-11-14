/*
	Dominik Jedruszczak
*/

#include "move_to_box.hpp"

namespace StevensDev {
namespace mga { // My Game Actors.

MoveToBox::MoveToBox() {
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