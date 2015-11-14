/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_COLLIDABLE_BOX
#define INCLUDED_COLLIDABLE_BOX

#include "../../engine/scene/icollidable.hpp"

namespace StevensDev {
namespace mgcl { // My Game Collidables.

/* A collidable box. */
class CollidableBox : public sgds::ICollidable {
	private:
		sgds::RectangleBounds rectangleBounds;
		unsigned short flags;
	public:
		/* Constructor(s). */
		CollidableBox();
		/* Function(s). */
		void moveBounds(float x, float y);
		/* Inherited function(s). */
		// Collidable.
		virtual const sgds::RectangleBounds& getBounds() const;
		virtual unsigned short getFlags() const;
		virtual bool canCollide(const unsigned short flags) const;
		virtual bool collides(const sgds::RectangleBounds& rectangleBounds) const;

};

}
}

#endif