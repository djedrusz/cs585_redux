/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_IRENDERABLE
#define INCLUDED_IRENDERABLE

namespace StevensDev {
namespace sgdr { // Stevens Game Development Rendering.

/* An abstract renderable object. */
class IRenderable {
	public:
		/* Function(s). */
		virtual void render() = 0;
};

}
}

#endif