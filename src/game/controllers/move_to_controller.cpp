/*
	Dominik Jedruszczak
*/

#include "move_to_controller.hpp"

namespace StevensDev {
namespace mgc { // My Game Controllers.

MoveToController::MoveToController()
:	collisionEvent(0, 0),
	collisionCallback(
		std::bind(
			&MoveToController::onCollisionEvent, 
			this, 
			std::placeholders::_1)) {
	;
}

void MoveToController::onCollisionEvent(const sgde::IEvent* event) {
	std::cout << "COLLISION!" << std::endl;
}

void MoveToController::possess(sgds::IActor* actor) {
	this->actor = actor;

	// I kind of messed up here with the mapped dispatcher: addListener should take 
	// a string type, not the actual event. I'm getting around this by creating an
	// instance of the event.
	actor->getEventDispatcher()->addListener(&collisionEvent, &collisionCallback);
}

void MoveToController::preTick() {

}

void MoveToController::tick(float deltaTime) {

}

void MoveToController::postTick() {

}


}
}