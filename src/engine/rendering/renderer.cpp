/*
	Dominik Jedruszczak

	renderer.cpp
	Implementation of the "Renderer" class.
*/

#include "renderer.hpp"

namespace StevensDev {
namespace sgdr { // Stevens Game Development Rendering.

/* Default constructor. */
Renderer::Renderer() {
	;
}

/* Copy constructor. */
Renderer::Renderer(const Renderer& renderer)
:	renderableSprites(renderer.renderableSprites) {
	;
}

/* Move constructor. */
Renderer::Renderer(Renderer&& renderer)
:	renderableSprites(std::move(renderer.renderableSprites)) {
	;
}

/* Copy assignment operator. */
Renderer& Renderer::operator = (const Renderer& renderer) {
	renderableSprites = renderer.renderableSprites;
}

/* Move assignment operator. */
Renderer& Renderer::operator = (Renderer&& renderer) {
	renderableSprites = std::move(renderer.renderableSprites);
}

/* Set up the window. */
void Renderer::setupWindow(unsigned int width, unsigned int height) {
	window.create(sf::VideoMode(width, height), "SGDRenderer");
}

/* Return whether or not the window is active. */
bool Renderer::isActive() {
	sf::Event event;
	window.pollEvent(event);
	return (event.type != sf::Event::Closed);
}

/* Add a renderable sprite. */
void Renderer::addRenderableSprite(RenderableSprite* renderableSprite) {
	renderableSprites.append(renderableSprite);
}

/* Remove a renderable sprite. */
void Renderer::removeRenderableSprite(RenderableSprite* renderableSprite) {
	for (unsigned int i = 0; i < renderableSprites.getSize(); i++) {
		if (renderableSprites[i] == renderableSprite) {
			renderableSprites.remove(i);
		}
	}
}

/* Draw the renderable sprites. */
void Renderer::draw() {
	window.clear();
	for (unsigned int i = 0; i < renderableSprites.getSize(); i++) {
		window.draw(renderableSprites[i]->getSprite());
	}
	window.display();
}

}
}