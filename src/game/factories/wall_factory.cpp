/*
	Dominik Jedruszczak
*/

/* Includes. */
// Local.
#include "wall_factory.hpp"

namespace StevensDev {
namespace mgf { // My Game Factories.

sgdc::DynamicArray< mga::Wall* > WallFactory::createWalls() {
	// Read from config file.
	// JSON parser broken.
	sgdc::DynamicArray< std::pair< float, float > > positions;
	// Top wall.
	for (unsigned int i = 0; i < 16; i++) {
		positions.append(std::pair< float, float >(i * 64, 0));
	}
	// Bottom wall.
	for (unsigned int i = 0; i < 16; i++) {
		positions.append(std::pair< float, float >(i * 64, 15 * 64));
	}
	// Left wall.
	for (unsigned int i = 1; i < 15; i++) {
		positions.append(std::pair< float, float >(0, i * 64));
	}
	// Right wall.
	for (unsigned int i = 1; i < 15; i++) {
		positions.append(std::pair< float, float >(15 * 64, i * 64));
	}

	sgdc::DynamicArray< mga::Wall* > walls;

	for (unsigned int i = 0; i < positions.getSize(); i++) {
		mga::Wall* wall = 
			new mga::Wall(
				positions.get(i).first,
				positions.get(i).second);

		wall->getRenderableSprite()
				->getSprite()
					.setTexture(sgda::TextureManager::get("blue_box"));

		sgds::SceneManager::getSceneGraph()
			.addCollidable(
				wall->getCollidable());

		sgdr::RenderManager::getRenderer()
				.addRenderableSprite(
					wall->getRenderableSprite());

		sgds::Scene::getInstance()
			.addTickable(
				wall->getEventDispatcher());

		walls.append(wall);
	}

	return walls;
}

}
}