/*
	Dominik Jedruszczak
*/

#include "player_controlled_box.hpp"

namespace StevensDev {
namespace mga { // My Game Actors.

PlayerControlledBox::PlayerControlledBox() {
	;
}

void PlayerControlledBox::move(float x, float y) {
	renderableSprite.getSprite().move(x, y);
	collidableBox.moveBounds(x, y);
}

sgdr::RenderableSprite* PlayerControlledBox::getRenderableSprite() {
	return &renderableSprite;
}

sgds::ICollidable* PlayerControlledBox::getCollidable() {
	return &collidableBox;
}

sgde::MappedEventDispatcher* PlayerControlledBox::getEventDispatcher() {
	return &mappedEventDispatcher;
}


}
}