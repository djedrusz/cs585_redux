/*
	Dominik Jedruszczak
*/

#include "player_controlled_factory.hpp"

namespace StevensDev {
namespace mgf { // My Game Factories.

mgc::PlayerController* PlayerControlledFactory::createController() {
	mgc::PlayerController* playerController 
		= new mgc::PlayerController();

	sgds::Scene::getInstance()
		.addTickable(
			playerController);

	return playerController;
}

mga::PlayerControlledBox* PlayerControlledFactory::createActor() {
	mga::PlayerControlledBox* playerControlledBox = new mga::PlayerControlledBox();

	playerControlledBox
		->getRenderableSprite()
			->getSprite()
				.setTexture(sgda::TextureManager::get("red_box"));

	sgds::SceneManager::getSceneGraph()
		.addCollidable(
			playerControlledBox
				->getCollidable());

	sgdr::RenderManager::getRenderer()
			.addRenderableSprite(
				playerControlledBox
					->getRenderableSprite());

	sgds::Scene::getInstance()
		.addTickable(
			playerControlledBox
				->getEventDispatcher());

	return playerControlledBox;
}

}
}