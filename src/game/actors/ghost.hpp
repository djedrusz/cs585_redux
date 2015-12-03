/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_GHOST
#define INCLUDED_GHOST

/* Includes. */
// System.
#include <cmath>
#include <utility>
// Local.
#include "../../engine/containers/dynamic_array.hpp"
#include "../../engine/scene/iactor.hpp"
#include "../collidables/collidable_box.hpp"
#include "pacman.hpp" // For flags, since this game engine
					  // doesn't have typed collidables.

/* Definitions. */
#define GHOST_FLAGS 4
#define GHOST_MOVEMENT_SPEED 5

namespace StevensDev {
namespace mga {

/* AI-controlled ghost which follows a preset path. */
class Ghost : public sgds::IActor {
	private:
		/* Data members. */
		sgdr::RenderableSprite renderableSprite;
		mgcl::CollidableBox collidableBox;
		sgde::MappedEventDispatcher mappedEventDispatcher;
		sgdc::DynamicArray< std::pair< float, float > > path;
		unsigned int currentTarget;
	public:
		/* Enums. */
		enum Color {
			RED
		};
		/* Contructors. */
		Ghost(sgdc::DynamicArray< std::pair< float, float > > path);
		/* Inherited functions. */
		// IActor.
		virtual sgdr::RenderableSprite* getRenderableSprite();
		virtual sgds::ICollidable* getCollidable();
		virtual sgde::MappedEventDispatcher* getEventDispatcher();
		/* Functions. */
		void move();
};

}
}

#endif