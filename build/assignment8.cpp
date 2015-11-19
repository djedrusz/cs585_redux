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
	sgds::Scene::getInstance().addTickable(&playerController);
	sgds::Scene::getInstance().addTickable(&sceneGraph);

	/* Main game loop. */
	while (renderer.isActive()) {
		sgds::Scene::getInstance().tick();

		/*sgdc::DynamicArray< sgds::ICollidable* > playerControlledBoxCollisions =
			std::move(
				sceneGraph
					.getCollisions(
						playerControlledBox
							.getCollidable()));
		if (playerControlledBoxCollisions.getSize() > 0) {
			if (playerControlledBox
					.getCollidable()
						->collides(
							playerControlledBoxCollisions[0]
								->getBounds())) {
				std::cout << "X" << std::endl;
			}
		}*/

		renderer.draw();
	}

	return 0;
}