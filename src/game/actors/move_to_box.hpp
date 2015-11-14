/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_MOVE_TO_BOX_HPP
#define INCLUDED_MOVE_TO_BOX_HPP

#include "../../engine/scene/iactor.hpp"
#include "../collidables/collidable_box.hpp"

namespace StevensDev {
namespace mga { // My Game Actors.

/* A move-to controlled box. */
class MoveToBox : public sgds::IActor {
	private:
		sgdr::RenderableSprite renderableSprite;
		mgcl::CollidableBox collidableBox;
		sgde::MappedEventDispatcher mappedEventDispatcher;
	public:
		/* Constructor(s). */
		MoveToBox();
		/* Inherited function(s). */
		// Actor.
		virtual sgdr::RenderableSprite* getRenderableSprite();
		virtual sgds::ICollidable* getCollidable();
		virtual sgde::MappedEventDispatcher* getEventDispatcher();
};

}
}

#endif