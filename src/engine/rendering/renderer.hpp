/*
	Dominik Jedruszczak

	renderer.hpp
	Declaration of the "Renderer" class.
*/

#ifndef INCLUDED_RENDERER
#define INCLUDED_RENDERER

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include "renderable_sprite.hpp"
#include "../containers/map.hpp"
#include "../containers/dynamic_array.hpp"

namespace StevensDev {
namespace sgdr { // Stevens Game Development Rendering.

/* A renderer. */
class Renderer {
	private:
		/* Data member(s). */
		sf::RenderWindow window; // Window.
		sgdc::DynamicArray< RenderableSprite* > renderableSprites; // List of renderable sprites.
	public:
		/* Constructor(s). */
		Renderer(); // Default constructor.
		Renderer(const Renderer& renderer); // Copy constructor.
		Renderer(Renderer&& renderer); // Move constructor.
		/* Operator(s). */
		Renderer& operator = (const Renderer& renderer); // Copy assignment operator.
		Renderer& operator = (Renderer&& renderer); // Move assignment operator.
		/* Function(s). */
		void setupWindow(unsigned int width, unsigned int height); // Set up the SFML window.
		bool isActive(); // Return whether or not the window is active.
		void addRenderableSprite(RenderableSprite* renderableSprite); // Add a renderable sprite.
		void removeRenderableSprite(RenderableSprite* renderableSprite); // Remove a renderable sprite.
		void draw(); // Render the renderable sprites.
};

}
}

#endif