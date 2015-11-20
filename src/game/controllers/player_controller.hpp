/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_PLAYER_CONTROLLER
#define INCLUDED_PLAYER_CONTROLLER

#include "../../engine/events/collision_event.hpp"
#include "../../engine/input/input.hpp"
#include "../../engine/scene/icontroller.hpp"
#include "../../engine/scene/scene_manager.hpp"

#include "../actors/player_controlled_box.hpp"

#define PLAYER_CONTROLLER_MOVEMENT_SPEED 0.5

namespace StevensDev {
namespace mgc { // My Game Controllers.

/*
	Move an actor inside the bounds of the screen using the "WASD" keys.
*/
class PlayerController : public sgds::IController {
	private:
		/* Data member(s). */
		mga::PlayerControlledBox* playerControlledBox;
	public:
		/* Constructor(s). */
		PlayerController();
		/* Inherited function(s). */
		// Controller.
		virtual void possess(sgds::IActor* actor);
		// Tickable.
		virtual void preTick();
		virtual void tick(float deltaTime);
		virtual void postTick();
};

}
}

#endif