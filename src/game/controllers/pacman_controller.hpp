/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_PACMAN_CONTROLLER
#define INCLUDED_PACMAN_CONTROLLER

/* Includes. */
// Local.
#include "../../engine/assets/texture_manager.hpp"
#include "../../engine/events/event_bus.hpp"
#include "../../engine/input/input.hpp"
#include "../../engine/scene/icontroller.hpp"
#include "../../engine/scene/scene_manager.hpp"
#include "../actors/pacman.hpp"
#include "../events/death_event.hpp"
#include "../events/reverse_event.hpp"

#define PACMAN_MOVEMENT_SPEED 5

namespace StevensDev {
namespace mgc { // My Game Controllers.

/* 
	Move Pacman according to keyboard input.
	In eating mode, remove ghosts from scene on collision.
*/
class PacmanController : public sgds::IController {
	private:
		/* Data members. */
		mga::Pacman* pacman;
		mge::DeathEvent deathEvent;
		std::function< void (const sgde::IEvent*) > deathEventCallback;
		mge::ReverseEvent reverseEvent;
		std::function< void (const sgde::IEvent*) > reverseEventCallback;
		bool isHunter;
	public:
		/* Constructors. */
		PacmanController();
		/* Inherited functions. */
		// Controller.
		virtual void preTick();
		virtual void tick(float deltaTime);
		virtual void postTick();
		virtual void possess(sgds::IActor* actor);
		/* Functions. */
		void onDeathEvent(const sgde::IEvent* event);
		void onReverseEvent(const sgde::IEvent* event);
};

}
}

#endif