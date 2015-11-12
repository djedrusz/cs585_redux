/*
	Dominik Jedruszczak

	test_renderer.cpp
	Visual tests for the "Renderer" class.
*/

#include "../src/engine/rendering/renderer.hpp"
#include "../src/engine/input/input.hpp"
#include "../src/engine/scene/scene.hpp"
#include "../src/engine/assets/texture_manager.hpp"
#include <iostream>

int main() {
	using namespace StevensDev;

	/* Textures. */
	sgda::TextureManager::add("smiley", "../textures/smiley_small.png");

	/* Rendering. */
	sgdr::Renderer renderer;

	sgdr::RenderableSprite renderableSprite;
	renderableSprite.getSprite().setTexture(sgda::TextureManager::get("smiley"));

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