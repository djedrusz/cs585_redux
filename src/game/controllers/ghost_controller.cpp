/*
	Dominik Jedruszczak
*/

/* Includes. */
// Local.
#include "ghost_controller.hpp"

namespace StevensDev {
namespace mgc { // My Game Controllers. 

GhostController::GhostController()
:	deathEventCallback(
		std::bind(
			&GhostController::onDeathEvent,
			this,
			std::placeholders::_1)),
	reverseEventCallback(
		std::bind(
			&GhostController::onReverseEvent,
			this,
			std::placeholders::_1)),
	isHunter(true) {
	;
}

GhostController::~GhostController() {
	sgde::EventBus::getDispatcher().removeListener(&reverseEvent, &reverseEventCallback);
}

void GhostController::preTick() {
	;
}

void GhostController::tick(float deltaTime) {
	/* Move. */
	ghost->move();

	/* Resolve collisions. */
	sgdc::DynamicArray< sgds::ICollidable* > collisions =
		std::move(
			sgds::SceneManager::getSceneGraph().getCollisions(
				ghost->getCollidable()));
	for (unsigned int i = 0; i < collisions.getSize(); i++) {
		if (ghost->getCollidable()
				->collides(collisions.get(i)->getBounds())) {
			// Only resolve collisions with ghost.
			// Ghosts' paths do not intersect walls.
			// Ghosts do not collide with each other.
			if (collisions.get(i)->getFlags() == PACMAN_FLAGS
				&& isHunter == true) {
				collisions.get(i)
					->getActor()
						->getEventDispatcher()
							->dispatch(&deathEvent);
			}
		}
	}
}

void GhostController::postTick() {
	;
}

void GhostController::possess(sgds::IActor* actor) {
	ghost = (mga::Ghost*)actor;

	ghost->getEventDispatcher()->addListener(&deathEvent, &deathEventCallback);
	sgde::EventBus::getDispatcher().addListener(&reverseEvent, &reverseEventCallback);
}

void GhostController::onDeathEvent(const sgde::IEvent* event) {
	std::cout << "GHOST DIE" << std::endl;
	//mgf::GhostFactory::destroyActor(ghost);
	//mgf::GhostFactory::destroyController(this);
}

void GhostController::onReverseEvent(const sgde::IEvent* event) {
	isHunter = !isHunter;
}

}
}