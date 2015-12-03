/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_RESET_EVENT
#define INCLUDED_RESET_EVENT

/* Includes. */
// Local.
#include "../../engine/events/ievent.hpp"

namespace StevensDev {
namespace mge { // My Game Events.

/* A reset event, recreate the level. */
class ResetEvent : public sgde::IEvent {
	public:
		/* Constructors. */
		ResetEvent();
		/* Inherited functions. */
		virtual const std::string& getType() const;
};

}
}

#endif