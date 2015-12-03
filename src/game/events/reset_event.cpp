/*
	Dominik Jedruszczak
*/

/* Includes. */
// Local.
#include "reset_event.hpp"

namespace StevensDev {
namespace mge { // My Game Events.

ResetEvent::ResetEvent() {
	;
}

const std::string& ResetEvent::getType() const {
	static std::string type = "reset";

	return type;
}

}
}