/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_DEATH_EVENT
#define INCLUDED_DEATH_EVENT

/* Includes. */
// Local.
#include "../../engine/events/ievent.hpp"

namespace StevensDev {
namespace mge { // My Game Events.

/* A death event. */
class DeathEvent : public sgde::IEvent {
	public:
		/* Constructors. */
		DeathEvent();
		/* Inherited functions. */
		virtual const std::string& getType() const;
};

}
}

#endif