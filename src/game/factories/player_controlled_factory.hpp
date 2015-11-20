/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_PLAYER_CONTROLLED_FACTORY
#define INCLUDED_PLAYER_CONTROLLED_FACTORY

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
		const mgc::PlayerController* createController();
		const mga::PlayerControlledBox* createActor();
};

}
}

#endif