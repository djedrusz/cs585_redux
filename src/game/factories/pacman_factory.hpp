/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_PACMAN_FACTORY
#define INCLUDED_PACMAN_FACTORY

/* Includes. */
// Local.
#include "../../engine/assets/texture_manager.hpp"
#include "../../engine/rendering/render_manager.hpp"
#include "../../engine/scene/scene.hpp"
#include "../../engine/scene/scene_manager.hpp"
#include "../../game/actors/pacman.hpp"
#include "../../game/controllers/pacman_controller.hpp"

/* Definitions. */
#define PACMAN_STARTING_POSITION_X 512
#define PACMAN_STARTING_POSITION_Y 512

namespace StevensDev {
namespace mgf { // My Game Factories.

/* A singleton factory which creates Pacmen and their controllers. */
class PacmanFactory {
	private:
		/* Constructor(s). */
		PacmanFactory() {};
		PacmanFactory(const PacmanFactory& pacmanFactory) = delete;
		/* Operator(s). */
		PacmanFactory& operator =
			(const PacmanFactory& pacmanFactory) = delete;
	public:
		/* Function(s). */
		static mga::Pacman* createActor();
		static mgc::PacmanController* createController();
};

}
}

#endif