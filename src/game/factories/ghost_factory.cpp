/*
	Dominik Jedruszczak
*/

/* Includes. */
// Local.
#include "ghost_factory.hpp"

namespace StevensDev {
namespace mgf { // My Game Factories.

/* Initialize static data members. */
// Path 1.
sgdc::DynamicArray< std::pair< float, float > > GhostFactory::redPath;

mga::Ghost* GhostFactory::createActor(mga::Ghost::Color color) {
	// For now, create paths because JSON parser is broken :(
	GhostFactory::redPath.append(std::pair< float, float >(256, 256));
	GhostFactory::redPath.append(std::pair< float, float >(512, 256));
	GhostFactory::redPath.append(std::pair< float, float >(512, 512));
	GhostFactory::redPath.append(std::pair< float, float >(256, 512));

	/* Color switch. */
	// In here we would parse the path from config file.
	sgdc::DynamicArray< std::pair< float, float > > path;
	switch (color) {
		case mga::Ghost::Color::RED: {
			path = redPath;
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
			.setTexture(sgda::TextureManager::get("yellow_box"));

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

}
}