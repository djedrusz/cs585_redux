/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_PLAYER_CONTROLLED_BOX_HPP
#define INCLUDED_PLAYER_CONTROLLED_BOX_HPP

#include "../../engine/scene/iactor.hpp"
#include "../collidables/collidable_box.hpp"

namespace StevensDev {
namespace mga { // My Game Actors.

/* A player controlled box. */
class PlayerControlledBox : public sgds::IActor {
	private:
		sgdr::RenderableSprite renderableSprite;
		mgcl::CollidableBox collidableBox;
		sgde::MappedEventDispatcher mappedEventDispatcher;
	public:
		/* Constructor(s). */
		PlayerControlledBox();
		/* Function(s). */
		void move(float x, float y);
		/* Inherited function(s). */
		// Actor.
		virtual sgdr::RenderableSprite* getRenderableSprite();
		virtual sgds::ICollidable* getCollidable();
		virtual sgde::MappedEventDispatcher* getEventDispatcher();
};

}
}

#endif