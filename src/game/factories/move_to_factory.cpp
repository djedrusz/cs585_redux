/*
	Dominik Jedruszczak
*/

#include "move_to_factory.hpp"

namespace StevensDev {
namespace mgf { // My Game Factories.

mgc::MoveToController* MoveToFactory::createController() {
	mgc::MoveToController* moveToController = new mgc::MoveToController();
	std::cout << "A1" << std::endl;
	//moveToController->possess(createActor());
	std::cout << "A2" << std::endl;
	sgds::Scene::getInstance()
		.addTickable(
			moveToController);
	std::cout << "A3" << std::endl;
}

mga::MoveToBox* MoveToFactory::createActor() {
	mga::MoveToBox* moveToBox = new mga::MoveToBox();

	std::cout << "B1" << std::endl;
	moveToBox
		->getRenderableSprite()
			->getSprite()
				.setTexture(sgda::TextureManager::get("blue_box"));

	std::cout << "B2" << std::endl;
	sgdr::RenderManager::getRenderer()
		.addRenderableSprite(
			moveToBox
				->getRenderableSprite());

	std::cout << "B3" << std::endl;
	sgds::Scene::getInstance()
		.addTickable(
			moveToBox
				->getEventDispatcher());

	std::cout << "B4" << std::endl;
	sgds::SceneManager::getSceneGraph()
		.addCollidable(
			moveToBox
				->getCollidable());

	std::cout << "B5" << std::endl;
}

}
}