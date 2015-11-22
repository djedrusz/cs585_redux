/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_PLAYER_CONTROLLED_FACTORY
#define INCLUDED_PLAYER_CONTROLLED_FACTORY

#include "../../engine/assets/texture_manager.hpp"
#include "../../engine/rendering/render_manager.hpp"
#include "../../engine/scene/scene.hpp"
#include "../../engine/scene/scene_manager.hpp"

#include "../controllers/player_controller.hpp"

namespace StevensDev {
namespace mgf { // My Game Factories.

/* 
	A singleton factory which creates a PlayerController with a
	possessed PlayerControlledBox.
*/
class PlayerControlledFactory {
	private:
		/* Constructor(s). */
		PlayerControlledFactory() {};
		PlayerControlledFactory(const PlayerControlledFactory& moveToFactory) = delete;
		/* Operator(s). */
		PlayerControlledFactory& operator = 
			(const PlayerControlledFactory& moveToFactory) = delete;
	public:
		/* Function(s). */
		static mgc::PlayerController* createController();
		static mga::PlayerControlledBox* createActor();
};

}
}

#endif