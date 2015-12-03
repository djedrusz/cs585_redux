/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_PACMAN_LEVEL
#define INCLUDED_PACMAN_LEVEL

/* Includes. */
// Local.
#include "../../engine/events/event_bus.hpp"
#include "../events/reset_event.hpp"
#include "../factories/ghost_factory.hpp"
#include "../factories/pacman_factory.hpp"
#include "../factories/wall_factory.hpp"

/* Definitions. */
#define NUM_GHOSTS 4

namespace StevensDev {
namespace mgl { // My Game Levels.

/* A pacman level. */
class PacmanLevel {
	private:
		/* Data members. */
		static mga::Ghost* ghosts[NUM_GHOSTS];
		static mgc::GhostController* ghostControllers[NUM_GHOSTS];
		static mga::Pacman* pacman;
		static mgc::PacmanController* pacmanController;
		static sgdc::DynamicArray< mga::Wall* > walls;
		/* Constructors. */
		PacmanLevel();
		PacmanLevel(const PacmanLevel& pacmanLevel) = delete;
		/* Operators. */
		PacmanLevel& operator = (const PacmanLevel& pacmanLevel) = delete;
	public:
		/* Functions. */
		static void init();
		static void reset();
		static void end();
};

}
}

#endif