/*
	Dominik Jedruszczak
*/

#include "player_controller.hpp"

namespace StevensDev {
namespace mgc { // My Game Controllers.

PlayerController::PlayerController() {
	;
}

void PlayerController::possess(sgds::IActor* actor) {
	playerControlledBox = (mga::PlayerControlledBox*)actor;
	playerControlledBox->move(100, 100);
}

void PlayerController::preTick() {
	;
}

void PlayerController::tick(float deltaTime) {
	/* Check for collisions. */
	sgdc::DynamicArray< sgds::ICollidable* > collisions =
		std::move(
			sgds::SceneManager::getSceneGraph().getCollisions(
				playerControlledBox->getCollidable()));
	for (unsigned int i = 0; i < collisions.getSize(); i++) {
		std::cout << "Y" << std::endl;
		if (playerControlledBox
				->getCollidable()
					->collides(collisions.get(i)->getBounds())) {
			std::cout << "X" << std::endl;
		}
	}

	/* Move the actor's sprite. */
	if (sgdi::Input::getInstance().isDown(sgdi::Input::Type::A)) {
		playerControlledBox->move(
			-PLAYER_CONTROLLER_MOVEMENT_SPEED,
			0.0f);
	}
	if (sgdi::Input::getInstance().isDown(sgdi::Input::Type::D)) {
		playerControlledBox->move(
			PLAYER_CONTROLLER_MOVEMENT_SPEED,
			0.0f);
	}
	if (sgdi::Input::getInstance().isDown(sgdi::Input::Type::W)) {
		playerControlledBox->move(
			0.0f,
			-PLAYER_CONTROLLER_MOVEMENT_SPEED);
	}
	if (sgdi::Input::getInstance().isDown(sgdi::Input::Type::S)) {
		playerControlledBox->move(
			0.0f,
			PLAYER_CONTROLLER_MOVEMENT_SPEED);
	}
}

void PlayerController::postTick() {
	;
}

}
}