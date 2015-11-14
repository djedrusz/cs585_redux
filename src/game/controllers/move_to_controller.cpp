/*
	Dominik Jedruszczak
*/

#include "move_to_controller.hpp"

namespace StevensDev {
namespace mgc { // My Game Controllers.

MoveToController::MoveToController() {
	;
}

void MoveToController::possess(sgds::IActor* actor) {
	this->actor = actor;
}

void MoveToController::preTick() {

}

void MoveToController::tick(float deltaTime) {

}

void MoveToController::postTick() {

}


}
}