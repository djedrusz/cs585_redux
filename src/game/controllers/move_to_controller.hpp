/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_MOVE_TO_CONTROLLER
#define INCLUDED_MOVE_TO_CONTROLLER

#include "../../engine/events/collision_event.hpp"
#include "../../engine/scene/icontroller.hpp"

namespace StevensDev {
namespace mgc { // My Game Controllers.

/* 
	Moves a sprite in a random direction until intersection with:
	1.) Wall.
	2.) Another sprite.
	Then selects another random direction to move in.
*/
class MoveToController : public sgds::IController {
	private:
		/* Data member(s). */
		sgds::IActor* actor;
	public:
		/* Constructor(s). */
		MoveToController();
		/* Function(s). */
		void onCollisionEvent(const sgde::IEvent* event);
		/* Inherited function(s). */
		// IController.
		virtual void possess(sgds::IActor* actor);
		// Tickable.
		virtual void preTick();
		virtual void tick(float deltaTime);
		virtual void postTick();
};

}
}

#endif