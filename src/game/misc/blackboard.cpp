/*
	Dominik Jedruszczak
*/

/* Includes. */
// Local.
#include "blackboard.hpp"

namespace StevensDev {
namespace mgm { // My Game Misc.

/* Initialize static data members. */
unsigned int Blackboard::ghostCount = 4;
unsigned int Blackboard::pacmanCount = 1;

void Blackboard::onDeathEvent(const sgde::IEvent* event) {
	mge::DeathEvent* deathEvent = (mge::DeathEvent*)event;
	if (deathEvent->getDeathFlags() == 2) {
		ghostCount--;
	}
	else {
		pacmanCount--;
	}
}

void Blackboard::onResetEvent(const sgde::IEvent* event) {
	ghostCount = 4;
	pacmanCount = 1;
}

unsigned int Blackboard::getGhostCount() {
	return ghostCount;
}

unsigned int Blackboard::getPacmanCount() {
	return pacmanCount;
}

}
}