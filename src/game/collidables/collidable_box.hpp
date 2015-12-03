/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_COLLIDABLE_BOX
#define INCLUDED_COLLIDABLE_BOX

#include "../../engine/scene/icollidable.hpp"

namespace StevensDev {
namespace mgcl { // My Game Collidables.

#define COLLIDABLE_BOX_SIZE 64

/* A collidable box. */
class CollidableBox : public sgds::ICollidable {
	private:
		sgds::RectangleBounds rectangleBounds;
		unsigned short flags;
		sgds::IActor* actor;
	public:
		/* Constructor(s). */
		CollidableBox(sgds::IActor* actor);
		CollidableBox(sgds::IActor* actor, unsigned short flags);
		CollidableBox(sgds::IActor* actor, unsigned short flags, float size);
		/* Function(s). */
		void moveBounds(float x, float y);
		/* Inherited function(s). */
		// Collidable.
		virtual sgds::IActor* getActor();
		virtual const sgds::RectangleBounds& getBounds() const;
		virtual unsigned short getFlags() const;
		virtual bool canCollide(const unsigned short flags) const;
		virtual bool collides(const sgds::RectangleBounds& rectangleBounds) const;

};

}
}

#endif