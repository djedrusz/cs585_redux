/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_IACTOR
#define INCLUDED_IACTOR

#include "../rendering/renderable_sprite.hpp"
#include "icollidable.hpp"

namespace StevensDev {
namespace sgds { // Stevens Game Development Scene.

/* An abstract actor object. */
class IActor {
	public:
		/* Function(s). */
		virtual sgdr::RenderableSprite* getRenderableSprite() = 0;
		virtual ICollidable* getCollidable() = 0;
};

}
}

#endif