/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_PACMAN
#define INCLUDED_PACMAN

/* Includes. */
// Local.
#include "../../engine/scene/iactor.hpp"
#include "../collidables/collidable_box.hpp"
#include "ghost.hpp"	// For flags, since this game engine doesn't have 
#include "wall.hpp"		// typed collidables.

/* Definitions. */
#define PACMAN_FLAGS 2
#define PACMAN_SIZE 48

namespace StevensDev {
namespace mga {

/* Player-controlled pacman. */
class Pacman : public sgds::IActor {
	private:
		/* Data member(s). */
		sgdr::RenderableSprite renderableSprite;
		mgcl::CollidableBox collidableBox;
		sgde::MappedEventDispatcher mappedEventDispatcher;
	public:
		/* Constructor(s). */
		Pacman(float x, float y);
		/* Inherited function(s). */
		// IActor.
		virtual sgdr::RenderableSprite* getRenderableSprite();
		virtual sgds::ICollidable* getCollidable();
		virtual sgde::MappedEventDispatcher* getEventDispatcher();
		/* Function(s). */
		void move(float x, float y);
};

}
}

#endif