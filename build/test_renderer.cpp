/*
	Dominik Jedruszczak

	test_renderer.cpp
	Tests for the "Renderer" class.
*/

#include "../src/engine/rendering/renderer.hpp"

int main() {
	using namespace StevensDev;

	sgdr::RenderableSprite renderableSprite;
	const sf::Sprite& spriteRef = renderableSprite.getSprite();
	sgdr::Renderer renderer;
	renderer.setupWindow(800, 800);
	renderer.addTexture("smiley", "../textures/smiley.jpg");
	renderer.addRenderableSprite(&renderableSprite);

	while (renderer.isActive()) {
		renderer.draw();
	}

	return 0;
}