/*
	Dominik Jedruszczak
*/

/* Includes. */
// Local.
#include "ghost_factory.hpp"

namespace StevensDev {
namespace mgf { // My Game Factories.

mga::Ghost* GhostFactory::createActor(mga::Ghost::Color color) {
	static sgdc::DynamicArray< std::pair< float, float > > bluePath;
	static sgdc::DynamicArray< std::pair< float, float > > greenPath;
	static sgdc::DynamicArray< std::pair< float, float > > redPath;
	static sgdc::DynamicArray< std::pair< float, float > > yellowPath;

	static bool created = false;
	if (created == false) {
		// For now, create paths because JSON parser is broken :(
		bluePath.append(std::pair< float, float >(1 * 64, 7 * 64));
		bluePath.append(std::pair< float, float >(1 * 64, 4 * 64));
		bluePath.append(std::pair< float, float >(4 * 64, 4 * 64));
		bluePath.append(std::pair< float, float >(4 * 64, 7 * 64));
		bluePath.append(std::pair< float, float >(6 * 64, 7 * 64));
		bluePath.append(std::pair< float, float >(6 * 64, 4 * 64));
		bluePath.append(std::pair< float, float >(9 * 64, 4 * 64));
		bluePath.append(std::pair< float, float >(9 * 64, 7 * 64));
		bluePath.append(std::pair< float, float >(11 * 64, 7 * 64));
		bluePath.append(std::pair< float, float >(11 * 64, 4 * 64));
		bluePath.append(std::pair< float, float >(14 * 64, 4 * 64));
		bluePath.append(std::pair< float, float >(14 * 64, 11 * 64));
		bluePath.append(std::pair< float, float >(11 * 64, 11 * 64));
		bluePath.append(std::pair< float, float >(11 * 64, 8 * 64));
		bluePath.append(std::pair< float, float >(9 * 64, 8 * 64));
		bluePath.append(std::pair< float, float >(9 * 64, 11 * 64));
		bluePath.append(std::pair< float, float >(6 * 64, 11 * 64));
		bluePath.append(std::pair< float, float >(6 * 64, 8 * 64));
		bluePath.append(std::pair< float, float >(4 * 64, 8 * 64));
		bluePath.append(std::pair< float, float >(4 * 64, 11 * 64));
		bluePath.append(std::pair< float, float >(1 * 64, 11 * 64));

		greenPath.append(std::pair< float, float >(4 * 64, 1 * 64));
		greenPath.append(std::pair< float, float >(4 * 64, 14 * 64));
		greenPath.append(std::pair< float, float >(6 * 64, 14 * 64));
		greenPath.append(std::pair< float, float >(6 * 64, 8 * 64));
		greenPath.append(std::pair< float, float >(9 * 64, 8 * 64));
		greenPath.append(std::pair< float, float >(9 * 64, 14 * 64));
		greenPath.append(std::pair< float, float >(11 * 64, 14 * 64));
		greenPath.append(std::pair< float, float >(11 * 64, 1 * 64));
		greenPath.append(std::pair< float, float >(9 * 64, 1 * 64));
		greenPath.append(std::pair< float, float >(9 * 64, 7 * 64));
		greenPath.append(std::pair< float, float >(6 * 64, 7 * 64));
		greenPath.append(std::pair< float, float >(6 * 64, 1 * 64));

		redPath.append(std::pair< float, float >(1 * 64, 1 * 64));
		redPath.append(std::pair< float, float >(14 * 64, 1 * 64));
		redPath.append(std::pair< float, float >(14 * 64, 14 * 64));
		redPath.append(std::pair< float, float >(1 * 64, 14 * 64));

		yellowPath.append(std::pair< float, float >(13 * 64, 8 * 64));
		yellowPath.append(std::pair< float, float >(2 * 64, 8 * 64));
		yellowPath.append(std::pair< float, float >(2 * 64, 7 * 64));
		yellowPath.append(std::pair< float, float >(13 * 64, 7 * 64));

		created = true;
	}

	/* Color switch. */
	// In here we would parse the path from config file.
	sgdc::DynamicArray< std::pair< float, float > > path;
	std::string texture;
	switch (color) {
		case mga::Ghost::Color::BLUE: {
			path = bluePath;
			texture = "blue_ghost";
			break;
		}
		case mga::Ghost::Color::GREEN: {
			path = greenPath;
			texture = "green_ghost";
			break;
		}
		case mga::Ghost::Color::RED: {
			path = redPath;
			texture = "red_ghost";
			break;
		}
		case mga::Ghost::Color::YELLOW: {
			path = yellowPath;
			texture = "yellow_ghost";
			break;
		}
		default: {
			path = sgdc::DynamicArray< std::pair< float, float > >();
		}
	}

	mga::Ghost* ghost =
		new mga::Ghost(path);

	ghost->getRenderableSprite()
		->getSprite()
			.setTexture(sgda::TextureManager::get(texture));

	sgds::SceneManager::getSceneGraph()
		.addCollidable(
			ghost->getCollidable());

	sgdr::RenderManager::getRenderer()
			.addRenderableSprite(
				ghost->getRenderableSprite());

	sgds::Scene::getInstance()
		.addTickable(
			ghost->getEventDispatcher());

	return ghost;
}

mgc::GhostController* GhostFactory::createController() {
	mgc::GhostController* ghostController =
		new mgc::GhostController();

	sgds::Scene::getInstance()
		.addTickable(
			ghostController);

	return ghostController;
}

void GhostFactory::destroyActor(mga::Ghost* ghost) {
	sgds::SceneManager::getSceneGraph()
		.removeCollidable(
			ghost->getCollidable());

	sgdr::RenderManager::getRenderer()
			.removeRenderableSprite(
				ghost->getRenderableSprite());

	sgds::Scene::getInstance()
		.removeTickable(
			ghost->getEventDispatcher());
}

void GhostFactory::destroyController(mgc::GhostController* ghostController) {
	sgds::Scene::getInstance()
		.removeTickable(
			ghostController);
}

}
}