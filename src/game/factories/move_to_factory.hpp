/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_MOVE_TO_FACTORY
#define INCLUDED_MOVE_TO_FACTORY

#include <iostream> // Remove after testing.

#include "../../engine/assets/texture_manager.hpp"
#include "../../engine/rendering/render_manager.hpp"
#include "../../engine/scene/scene.hpp"
#include "../../engine/scene/scene_manager.hpp"

#include "../controllers/move_to_controller.hpp"

namespace StevensDev {
namespace mgf { // My Game Factories.

/* 
	A singleton factory which creates a MoveToController with a
	possessed MoveToBox.
*/
class MoveToFactory {
	private:
		/* Constructor(s). */
		MoveToFactory() {};
		MoveToFactory(const MoveToFactory& moveToFactory) = delete;
		/* Operator(s). */
		MoveToFactory& operator = 
			(const MoveToFactory& moveToFactory) = delete;
	public:
		/* Function(s). */
		static mgc::MoveToController* createController();
		static mga::MoveToBox* createActor();
};

}
}

#endif