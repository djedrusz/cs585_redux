/*
	Dominik Jedruszczak
*/

/* Includes. */
// Local.
#include "pacman_controller.hpp"

namespace StevensDev {
namespace mgc { // My Game Controllers. 

PacmanController::PacmanController()
:	deathEventCallback(
		std::bind(
			&PacmanController::onDeathEvent,
			this,
			std::placeholders::_1)),
	reverseEventCallback(
		std::bind(
			&PacmanController::onReverseEvent,
			this,
			std::placeholders::_1)),
	isHunter(false) {
	;
}

void PacmanController::preTick() {
	;
}

void PacmanController::tick(float deltaTime) {
	/* Move. */
	if (sgdi::Input::getInstance().isDown(sgdi::Input::Type::A)) {
		pacman->move(
			-PACMAN_MOVEMENT_SPEED,
			0.0f);
	}
	if (sgdi::Input::getInstance().isDown(sgdi::Input::Type::D)) {
		pacman->move(
			PACMAN_MOVEMENT_SPEED,
			0.0f);
	}
	if (sgdi::Input::getInstance().isDown(sgdi::Input::Type::W)) {
		pacman->move(
			0.0f,
			-PACMAN_MOVEMENT_SPEED);
	}
	if (sgdi::Input::getInstance().isDown(sgdi::Input::Type::S)) {
		pacman->move(
			0.0f,
			PACMAN_MOVEMENT_SPEED);
	}

	/* Resolve collisions. */
	sgds::RectangleBounds pacmanBounds = 
		pacman->getCollidable()->getBounds();
	sgdc::DynamicArray< sgds::ICollidable* > collisions =
		std::move(
			sgds::SceneManager::getSceneGraph().getCollisions(
				pacman->getCollidable()));
	for (unsigned int i = 0; i < collisions.getSize(); i++) {
		if (pacman->getCollidable()
				->collides(collisions.get(i)->getBounds())) {
			// Resolve wall collisions here without events.
			// It would be wasteful for each wall to check for
			// a collision with pacman.
			if (collisions.get(i)->getFlags() == WALL_FLAGS) {
				sgds::RectangleBounds wallBounds = 
					collisions.get(i)->getBounds();
				float distanceX, distanceY;
				// X.
				if (pacmanBounds.getX() < wallBounds.getX()) {
					distanceX = 
						wallBounds.getX()
						- pacmanBounds.getX()
						- pacmanBounds.getWidth();
				}
				else {
					distanceX = 
						wallBounds.getX() 
						+ wallBounds.getWidth() 
						- pacmanBounds.getX();
				}
				// Y.
				if (pacmanBounds.getY() < wallBounds.getY()) {
					distanceY = 
						wallBounds.getY()
						- pacmanBounds.getY()
						- pacmanBounds.getHeight();
				}
				else {
					distanceY = 
						wallBounds.getY() 
						+ wallBounds.getHeight() 
						- pacmanBounds.getY();
				}
				/* Move in the direction with the smaller magnitude. */
				if (((distanceX > 0)?distanceX:-distanceX) 
					< ((distanceY > 0)?distanceY:-distanceY)) {
					pacman->move(distanceX, 0);
				}
				else {
					pacman->move(0, distanceY);
				}
			}
			else if (collisions.get(i)->getFlags() == GHOST_FLAGS
				&& isHunter == true) {
				collisions.get(i)
					->getActor()
						->getEventDispatcher()
							->dispatch(&deathEvent);
			}
		}
	}
}

void PacmanController::postTick() {
	;
}

void PacmanController::possess(sgds::IActor* actor) {
	pacman = (mga::Pacman*)actor;

	pacman->getEventDispatcher()->addListener(&deathEvent, &deathEventCallback);
	sgde::EventBus::getDispatcher().addListener(&reverseEvent, &reverseEventCallback);
}

void PacmanController::onDeathEvent(const sgde::IEvent* event) {
	std::cout << "PACMAN DIE" << std::endl;
}

void PacmanController::onReverseEvent(const sgde::IEvent* event) {
	if (isHunter == false) {
		pacman->getRenderableSprite()
			->getSprite()
				.setTexture(sgda::TextureManager::get("evil_pacman"));
	}
	else {
		pacman->getRenderableSprite()
			->getSprite()
				.setTexture(sgda::TextureManager::get("pacman"));
	}
	isHunter = !isHunter;
}

}
}