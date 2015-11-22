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

#include "../src/game/factories/move_to_factory.hpp"
#include "../src/game/factories/player_controlled_factory.hpp"

#define NUM_BOXES 1000


int main(int argc, char** argv) {
	using namespace StevensDev;

	/* Scene Manager. */
	sgds::SceneManager::setSceneGraph(1024, 10);

	/* Assets. */
	// Textures.
	sgda::TextureManager::add("red_box", "../textures/red_box.png");
	sgda::TextureManager::add("blue_box", "../textures/blue_box.png");

	/* Actors. */
	// Player box.
	mga::PlayerControlledBox* playerControlledBox = mgf::PlayerControlledFactory::createActor();
	// Move to boxes.
	mga::MoveToBox* moveToBoxes[NUM_BOXES];
	for (unsigned int i = 0; i < NUM_BOXES; i++) {
		moveToBoxes[i] = mgf::MoveToFactory::createActor();
	}

	/* Controllers. */
	// Player controller.
	mgc::PlayerController* playerController = mgf::PlayerControlledFactory::createController();
	playerController->possess(playerControlledBox);
	// Move to controllers.
	mgc::MoveToController* moveToControllers[NUM_BOXES];
	for (unsigned int i = 0; i < NUM_BOXES; i++) {
		moveToControllers[i] = mgf::MoveToFactory::createController();
		moveToControllers[i]->possess(moveToBoxes[i]);
	}

	/* Renderer. */
	sgdr::RenderManager::getRenderer()
		.setupWindow(
			sgds::SceneManager::getSceneGraph().getLength(),
			sgds::SceneManager::getSceneGraph().getLength());

	/* Scene. */
	sgds::Scene::getInstance().addTickable(&sgdi::Input::getInstance());
	sgds::Scene::getInstance().addTickable(&sgds::SceneManager::getSceneGraph());

	/* Main game loop. */
	while (sgdr::RenderManager::getRenderer().isActive()) {
		sgds::Scene::getInstance().tick();

		sgdr::RenderManager::getRenderer().draw();
	}

	return 0;
}