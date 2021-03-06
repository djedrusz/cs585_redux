/*
	Dominik Jedruszczak
*/

/* Includes. */
// Local.
#include "death_event.hpp"

namespace StevensDev {
namespace mge { // My Game Events.

DeathEvent::DeathEvent(unsigned short deathFlag)
:	deathFlag(deathFlag) {
	;
}

const std::string& DeathEvent::getType() const {
	static std::string type = "death";

	return type;
}

unsigned short DeathEvent::getDeathFlags() {
	return deathFlag;
}

}
}