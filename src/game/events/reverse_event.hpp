/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_REVERSE_EVENT
#define INCLUDED_REVERSE_EVENT

/* Includes. */
// Local.
#include "../../engine/events/ievent.hpp"

namespace StevensDev {
namespace mge { // My Game Events.

/* A reverse event, the hunter now becomes the hunted. */
class ReverseEvent : public sgde::IEvent {
	public:
		/* Constructors. */
		ReverseEvent();
		/* Inherited functions. */
		virtual const std::string& getType() const;
};

}
}

#endif