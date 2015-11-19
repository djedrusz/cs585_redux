/*
	Dominik Jedruszczak
	icollidable.hpp
	Declaration of the "ICollidable" interface.
*/

#ifndef INCLUDED_ICOLLIDABLE
#define INCLUDED_ICOLLIDABLE

#include <string>

#include "rectangle_bounds.hpp"

namespace StevensDev {
namespace sgds { // Stevens Game Development Scene.

/* A collidable object. */
class ICollidable {
	public:
		/* Function(s). */
		virtual const RectangleBounds& getBounds() const = 0;
		virtual unsigned short getFlags() const = 0;
		virtual bool canCollide(const unsigned short flags) const = 0;
		virtual bool collides(const RectangleBounds& rectangleBounds) const = 0;
};

}
}

#endif