/*
	Dominik Jedruszczak
*/

/* Includes. */
// Local.
#include "pacman_factory.hpp"

namespace StevensDev {
namespace mgf { // My Game Factories.

mga::Pacman* PacmanFactory::createActor() {
	mga::Pacman* pacman =
		new mga::Pacman(
			PACMAN_STARTING_POSITION_X,
			PACMAN_STARTING_POSITION_Y);

	pacman->getRenderableSprite()
		->getSprite()
			.setTexture(sgda::TextureManager::get("pacman"));

	sgds::SceneManager::getSceneGraph()
		.addCollidable(
			pacman->getCollidable());

	sgdr::RenderManager::getRenderer()
			.addRenderableSprite(
				pacman->getRenderableSprite());

	sgds::Scene::getInstance()
		.addTickable(
			pacman->getEventDispatcher());

	return pacman;
}

mgc::PacmanController* PacmanFactory::createController() {
	mgc::PacmanController* pacmanController =
		new mgc::PacmanController();

	sgds::Scene::getInstance()
		.addTickable(
			pacmanController);

	return pacmanController;
}

void PacmanFactory::destroyActor(mga::Pacman* pacman) {
	sgds::SceneManager::getSceneGraph()
		.removeCollidable(
			pacman->getCollidable());

	sgdr::RenderManager::getRenderer()
			.removeRenderableSprite(
				pacman->getRenderableSprite());

	sgds::Scene::getInstance()
		.removeTickable(
			pacman->getEventDispatcher());

	//delete pacman;
}

void PacmanFactory::destroyController(mgc::PacmanController* pacmanController) {
	sgds::Scene::getInstance()
		.removeTickable(
			pacmanController);

	//delete pacmanController;
}

}
}