/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_GHOST_CONTROLLER
#define INCLUDED_GHOST_CONTROLLER

/* Includes. */
// Local.
#include "../../engine/events/event_bus.hpp"
#include "../../engine/input/input.hpp"
#include "../../engine/scene/icontroller.hpp"
#include "../../engine/scene/scene_manager.hpp"
#include "../actors/ghost.hpp"
#include "../events/death_event.hpp"
#include "../events/reverse_event.hpp"
//#include "../factories/ghost_factory.hpp"

namespace StevensDev {
namespace mgc { // My Game Controllers.

/* 
	Move the ghost along its path.
	In eating mode, end game on collision with pacman.
*/
class GhostController : public sgds::IController {
	private:
		/* Data members. */
		mga::Ghost* ghost;
		mge::DeathEvent deathEvent;
		std::function< void (const sgde::IEvent*) > deathEventCallback;
		mge::ReverseEvent reverseEvent;
		std::function< void (const sgde::IEvent*) > reverseEventCallback;
		bool isHunter;
	public:
		/* Constructors. */
		GhostController();
		/* Destructors. */
		~GhostController();
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