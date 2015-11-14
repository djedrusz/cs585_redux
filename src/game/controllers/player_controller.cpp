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