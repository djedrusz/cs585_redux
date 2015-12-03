/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_WALL
#define INCLUDED_WALL

/* Includes. */
// Local.
#include "../../engine/scene/iactor.hpp"
#include "../collidables/collidable_box.hpp"

/* Definitions. */
#define WALL_FLAGS 1

namespace StevensDev {
namespace mga { // My Game Actors.

/* A wall. */
class Wall : public sgds::IActor {
	private:
		/* Data member(s). */
		sgdr::RenderableSprite renderableSprite;
		mgcl::CollidableBox collidableBox;
		sgde::MappedEventDispatcher mappedEventDispatcher;
	public:
		/* Constructor(s). */
		Wall(float x, float y);
		/* Inherited function(s). */
		// IActor.
		virtual sgdr::RenderableSprite* getRenderableSprite();
		virtual sgds::ICollidable* getCollidable();
		virtual sgde::MappedEventDispatcher* getEventDispatcher();
};

}
}

#endif