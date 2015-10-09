/*
	Dominik Jedruszczak

	itickable.hpp
	Declaration of the "ITickable" interface.
*/

#ifndef INCLUDED_ITICKABLE
#define INCLUDED_ITICKABLE

namespace StevensDev {
namespace sgds { // Stevens Game Development Scene.

/* The interface for objects which react to game time. */
class ITickable {
	private:
	public:
		/* Function(s). */
		virtual void preTick() = 0; /* Pre-tick logic. */
		virtual void tick(float deltaTime) = 0; /* Tick logic. */
		virtual void postTick() = 0; /* Post-tick logic. */
};

}
}

#endif