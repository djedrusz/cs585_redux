/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_RENDER_MANAGER
#define INCLUDED_RENDER_MANAGER

#include "renderer.hpp"

namespace StevensDev {
namespace sgdr { // Stevens Game Development Rendering.

/* A static renderer. */
class RenderManager {
	private:
		/* Constructor(s). */
		RenderManager() {};
		RenderManager(const RenderManager& renderManager) = delete;
		/* Operator(s). */
		RenderManager& operator = (const RenderManager& renderManager) = delete;
	public:
		/* Function(s). */
		static Renderer& getRenderer();
};

}
}

#endif