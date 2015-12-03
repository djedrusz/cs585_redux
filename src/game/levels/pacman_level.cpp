/*
	Dominik Jedruszczak
*/

/* Includes. */
// Local.
#include "pacman_level.hpp"

namespace StevensDev {
namespace mgl { // My Game Levels.

/* Initialize static variables. */
mga::Ghost* PacmanLevel::ghosts[NUM_GHOSTS];
mgc::GhostController* PacmanLevel::ghostControllers[NUM_GHOSTS];
mga::Pacman* PacmanLevel::pacman;
mgc::PacmanController* PacmanLevel::pacmanController;
sgdc::DynamicArray< mga::Wall* > PacmanLevel::walls;

void PacmanLevel::init() {
	/* Create walls. */
	static bool firstInit = true;
	if (firstInit) {
		walls = std::move(mgf::WallFactory::createWalls());
		firstInit = false;
	}

	/* Create ghosts. */
	ghosts[0] = mgf::GhostFactory::createActor(mga::Ghost::Color::BLUE);
	ghosts[1] = mgf::GhostFactory::createActor(mga::Ghost::Color::GREEN);
	ghosts[2] = mgf::GhostFactory::createActor(mga::Ghost::Color::RED);
	ghosts[3] = mgf::GhostFactory::createActor(mga::Ghost::Color::YELLOW);
	for (unsigned int i = 0; i < NUM_GHOSTS; i++) {
		ghostControllers[i] = mgf::GhostFactory::createController();
		ghostControllers[i]->possess(ghosts[i]);
	}

	/* Create pacman. */
	pacman = mgf::PacmanFactory::createActor();
	pacmanController = mgf::PacmanFactory::createController();
	pacmanController->possess(pacman);
}

void PacmanLevel::end() {
	/* Destroy ghosts. */
	for (unsigned int i = 0; i < NUM_GHOSTS; i++) {
		mgf::GhostFactory::destroyActor(ghosts[i]);
		mgf::GhostFactory::destroyController(ghostControllers[i]);
	}

	/* Destroy pacman. */
	mgf::PacmanFactory::destroyActor(pacman);
	mgf::PacmanFactory::destroyController(pacmanController);
}

void PacmanLevel::reset() {
	end();
	init();

	static mge::ResetEvent resetEvent;
	sgde::EventBus::getDispatcher().dispatch(&resetEvent);
}

}
}