/*
	Dominik Jedruszczak
*/

#include "render_manager.hpp"

namespace StevensDev {
namespace sgdr { // Stevens Game Development Rendering.

Renderer& RenderManager::getRenderer() {
	static Renderer renderer;

	return renderer;
}

}
}