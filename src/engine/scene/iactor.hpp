/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_IACTOR
#define INCLUDED_IACTOR

#include "../rendering/renderable_sprite.hpp"
//#include "icollidable.hpp"
#include "../events/mapped_event_dispatcher.hpp"

namespace StevensDev {
namespace sgds { // Stevens Game Development Scene.

class ICollidable;

/* An abstract actor object. */
class IActor {
	public:
		/* Function(s). */
		virtual sgdr::RenderableSprite* getRenderableSprite() = 0;
		virtual ICollidable* getCollidable() = 0;
		virtual sgde::MappedEventDispatcher* getEventDispatcher() = 0;
};

}
}

#endif