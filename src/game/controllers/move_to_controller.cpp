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
	/* Avoidance. */
	float otherX = ((sgde::CollisionEvent*)event)->getX();
	float otherY = ((sgde::CollisionEvent*)event)->getY();

	float myX = moveToBox->getRenderableSprite()->getPositionX() + 32;
	float myY = moveToBox->getRenderableSprite()->getPositionY() + 32;

	vectorX = myX - otherX;
	vectorY = myY - otherY;

	vectorX = vectorX / 10;
	vectorY = vectorY / 10;
}

void MoveToController::possess(sgds::IActor* actor) {
	moveToBox = (mga::MoveToBox*)actor;

	moveToBox->move(
		rand() % (int)sgds::SceneManager::getSceneGraph().getLength(),
		rand() % (int)sgds::SceneManager::getSceneGraph().getLength());

	// I kind of messed up here with the mapped dispatcher: addListener should take 
	// a string type, not the actual event. I'm getting around this by creating an
	// instance of the event.
	moveToBox->getEventDispatcher()->addListener(&collisionEvent, &collisionCallback);
}

void MoveToController::preTick() {

}

void MoveToController::tick(float deltaTime) {
	moveToBox->move(vectorX, vectorY);

	/* Check collision with outside bounds. */
	if (moveToBox
			->getRenderableSprite()
				->getPositionX()
		+ 64
		>
		sgds::SceneManager::getSceneGraph().getLength()) {
		if (vectorX > 0) {
			vectorX = -vectorX;
		}
	}
	else if (moveToBox
			->getRenderableSprite()
				->getPositionX()
		<
		0) {
		if (vectorX < 0) {
			vectorX = -vectorX;
		}
	}
	if (moveToBox
			->getRenderableSprite()
				->getPositionY()
		+ 64
		>
		sgds::SceneManager::getSceneGraph().getLength()) {
		if (vectorY > 0) {
			vectorY = -vectorY;
		}
	}
	else if (moveToBox
			->getRenderableSprite()
				->getPositionY()
		<
		0) {
		if (vectorY < 0) {
			vectorY = -vectorY;
		}
	}
}

void MoveToController::postTick() {

}


}
}