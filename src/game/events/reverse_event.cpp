/*
	Dominik Jedruszczak
*/

/* Includes. */
// Local.
#include "reverse_event.hpp"

namespace StevensDev {
namespace mge { // My Game Events.

ReverseEvent::ReverseEvent() {
	;
}

const std::string& ReverseEvent::getType() const {
	static std::string type = "reverse";

	return type;
}

}
}