/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_BLACKBOARD
#define INCLUDED_BLACKBOARD

/* Includes. */
// Local.
#include "../events/death_event.hpp"

namespace StevensDev {
namespace mgm { // My Game Misc.

/* Keeps track of how many ghosts are alive. */
class Blackboard {
	private:
		/* Data members. */
		static unsigned int ghostCount;
		static unsigned int pacmanCount;
		/* Constructors. */
		Blackboard();
		Blackboard(const Blackboard& blackboard) = delete;
		/* Operators. */
		Blackboard& operator = (const Blackboard& blackboard) = delete;
	public:
		/* Functions. */
		static void onDeathEvent(const sgde::IEvent* event);
		static void onResetEvent(const sgde::IEvent* event);
		static unsigned int getGhostCount();
		static unsigned int getPacmanCount();
};

}
}

#endif