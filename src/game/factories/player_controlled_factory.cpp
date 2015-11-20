/*
	Dominik Jedruszczak
*/

#include "player_controlled_factory.hpp"

namespace StevensDev {
namespace mgf { // My Game Factories.

const mgc::PlayerController* PlayerControlledFactory::createController() {
	return new mgc::PlayerController();
}

const mga::PlayerControlledBox* PlayerControlledFactory::createActor() {
	return new mga::PlayerControlledBox();
}

}
}