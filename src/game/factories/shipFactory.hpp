/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_SHIP_FACTORY
#define INCLUDED_SHIP_FACTORY

#include "../actors/ship.hpp"

namespace StevenDev {
namespace factories {

/* A factory for creating ships. */
class ShipFactory {
	private:
	public:
		/* Function(s). */
		static Ship* newShip();
};

}
}

#endif