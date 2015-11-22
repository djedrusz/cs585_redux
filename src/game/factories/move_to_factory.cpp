/*
	Dominik Jedruszczak
*/

#include "move_to_factory.hpp"

namespace StevensDev {
namespace mgf { // My Game Factories.

mgc::MoveToController* MoveToFactory::createController() {
	mgc::MoveToController* moveToController 
		= new mgc::MoveToController();

	sgds::Scene::getInstance()
		.addTickable(
			moveToController);

	return moveToController;
}

mga::MoveToBox* MoveToFactory::createActor() {
	mga::MoveToBox* moveToBox = new mga::MoveToBox();

	moveToBox
		->getRenderableSprite()
			->getSprite()
				.setTexture(sgda::TextureManager::get("blue_box"));

	sgds::SceneManager::getSceneGraph()
		.addCollidable(
			moveToBox
				->getCollidable());

	sgdr::RenderManager::getRenderer()
			.addRenderableSprite(
				moveToBox
					->getRenderableSprite());

	sgds::Scene::getInstance()
		.addTickable(
			moveToBox
				->getEventDispatcher());

	return moveToBox;
}

}
}