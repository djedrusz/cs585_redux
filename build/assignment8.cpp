/*
	Dominik Jedruszczak

	Assignment 8 game.
*/

#include <unistd.h>

#include "../src/engine/assets/texture_manager.hpp"

#include "../src/engine/rendering/renderer.hpp"

#include "../src/engine/scene/scene_manager.hpp"
#include "../src/engine/scene/scene.hpp"

#include "../src/game/actors/move_to_box.hpp"
#include "../src/game/actors/player_controlled_box.hpp"

#include "../src/game/controllers/move_to_controller.hpp"
#include "../src/game/controllers/player_controller.hpp"


int main(int argc, char** argv) {
	using namespace StevensDev;

	std::cout << sizeof(int) << std::endl;
	std::cout << sizeof(sgds::RectangleBounds) << std::endl;
	std::cout << sizeof(mgcl::CollidableBox) << std::endl;

	/* Assets. */
	// Textures.
	sgda::TextureManager::add("red_box", "../textures/red_box.png");
	sgda::TextureManager::add("blue_box", "../textures/blue_box.png");

	/* Actors. */
	// Player box.
	mga::PlayerControlledBox playerControlledBox;
	playerControlledBox
		.getRenderableSprite()
			->getSprite()
				.setTexture(sgda::TextureManager::get("red_box"));
	// Move-to box.
	mga::MoveToBox moveToBox;
	moveToBox
		.getRenderableSprite()
			->getSprite()
				.setTexture(sgda::TextureManager::get("blue_box"));

	/* Controllers. */
	// Player controller.
	mgc::PlayerController playerController;
	playerController.possess(&playerControlledBox);
	// Move to controller.
	mgc::MoveToController moveToController;
	moveToController.possess(&moveToBox);

	/* Renderer. */
	sgdr::Renderer renderer;
	renderer.setupWindow(256, 256);
	renderer.addRenderableSprite(moveToBox.getRenderableSprite());
	renderer.addRenderableSprite(playerControlledBox.getRenderableSprite());

	/* Scene manager/graph. */
	sgds::SceneManager::setSceneGraph(256, 10);
	sgds::NxNSceneGraph& sceneGraph = sgds::SceneManager::getSceneGraph();
	sceneGraph.addCollidable(moveToBox.getCollidable());
	sceneGraph.addCollidable(playerControlledBox.getCollidable());

	/* Scene. */
	sgds::Scene::getInstance().addTickable(&sgdi::Input::getInstance());
	sgds::Scene::getInstance().addTickable(moveToBox.getEventDispatcher());
	sgds::Scene::getInstance().addTickable(&playerController);
	sgds::Scene::getInstance().addTickable(&moveToController);
	sgds::Scene::getInstance().addTickable(&sceneGraph);

	/* Main game loop. */
	while (renderer.isActive()) {
		sgds::Scene::getInstance().tick();

		renderer.draw();
	}

	return 0;
}