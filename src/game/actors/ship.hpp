/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_SHIP
#define INCLUDED_SHIP

#include "../../src/engine/scene/iactor.hpp"

namespace StevensDev {
namespace actors {

/* A ship of the line. */
class Ship : public sgde::IActor {
	private:
		/* Data member(s). */
		sgdr::RenderableSprite shipSprite;
	public:
		/* Constructor(s). */
		Ship();
		/* Inherited function(s). */
		// IActor.
		virtual sgdr::RenderableSprite* getRenderableSprite();
		virtual sgdi::ICollidable* getCollidable();
		virtual sgde::MappedEventDispatcher* getEventDispatcher();
};

}
}

#endif