/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_GHOST_FACTORY
#define INCLUDED_GHOST_FACTORY

/* Includes. */
// Local.
#include "../../engine/assets/texture_manager.hpp"
#include "../../engine/rendering/render_manager.hpp"
#include "../../engine/scene/scene.hpp"
#include "../../engine/scene/scene_manager.hpp"
#include "../../game/actors/ghost.hpp"
#include "../../game/controllers/ghost_controller.hpp"

namespace StevensDev {
namespace mgf {

/* A singleton factory which creates Ghosts and their controllers. */
class GhostFactory {
	private:
		/* Data members. */
		static sgdc::DynamicArray< std::pair< float, float > > redPath;
		/* Constructor(s). */
		GhostFactory() {};
		GhostFactory(const GhostFactory& ghostFactory) = delete;
		/* Operator(s). */
		GhostFactory& operator =
			(const GhostFactory& ghostFactory) = delete;
	public:
		/* Function(s). */
		static mga::Ghost* createActor(mga::Ghost::Color color);
		static mgc::GhostController* createController();
};

}
}

#endif