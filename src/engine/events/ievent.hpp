/*
	Dominik Jedruszczak

	ievent.hpp
	Declaration of the "IEvent" interface.
*/

#ifndef INCLUDED_IEVENT_HPP
#define INCLUDED_IEVENT_HPP

#include <string>

namespace StevensDev {
namespace sgde { // Stevens Game Development Events.

/* An event. */
class IEvent {
	public:
		virtual const std::string& getType() const = 0;
};

}
}

#endif