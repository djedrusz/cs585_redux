/*
	Dominik Jedruszczak

	test_renderer.cpp
	Visual tests for the "Renderer" class.
*/

#include "../src/engine/rendering/renderer.hpp"
#include "../src/engine/input/input.hpp"
#include "../src/engine/scene/scene.hpp"
#include <iostream>

int main() {
	using namespace StevensDev;

	/* Rendering. */
	sgdr::Renderer renderer;
	renderer.addTexture("smiley", "../textures/smiley_small.png");

	sgdr::RenderableSprite renderableSprite;
	renderableSprite.getSprite().setTexture(renderer.getTexture("smiley"));

	renderer.addRenderableSprite(&renderableSprite);

	renderer.setupWindow(256, 256);

	/* Scene. */
	sgds::Scene::getInstance().addTickable(&sgdi::Input::getInstance());
	
	while (renderer.isActive()) {
		sgds::Scene::getInstance().tick();

		if (sgdi::Input::getInstance().isDown(sgdi::Input::Type::A)) {
			renderableSprite.move(-0.05, 0);
		}
		if (sgdi::Input::getInstance().isDown(sgdi::Input::Type::D)) {
			renderableSprite.move(0.05, 0);
		}
		if (sgdi::Input::getInstance().isDown(sgdi::Input::Type::S)) {
			renderableSprite.move(0, 0.05);
		}
		if (sgdi::Input::getInstance().isDown(sgdi::Input::Type::W)) {
			renderableSprite.move(0, -0.05);
		}

		renderer.draw();
	}

	return 0;
}