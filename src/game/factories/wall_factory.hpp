/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_WALL_FACTORY
#define INCLUDED_WALL_FACTORY

/* Includes. */
// System.
#include <utility>
// Local.
#include "../../engine/assets/texture_manager.hpp"
#include "../../engine/rendering/render_manager.hpp"
#include "../../engine/scene/scene.hpp"
#include "../../engine/scene/scene_manager.hpp"
#include "../../game/actors/wall.hpp"

namespace StevensDev {
namespace mgf { // My Game Factories.

/* A singleton factory which creates Walls. */
class WallFactory {
	private:
		/* Constructor(s). */
		WallFactory() {};
		WallFactory(const WallFactory& wallFactory) = delete;
		/* Operator(s). */
		WallFactory& operator =
			(const WallFactory& wallFactory) = delete;
	public:
		/* Function(s). */
		static sgdc::DynamicArray< mga::Wall* > createWalls();
};

}
}

#endif