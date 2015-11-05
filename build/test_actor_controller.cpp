/*
	Dominik Jedruszczak

	Tests for the actor/controller model.
*/

#include <iostream>
	
#include "../src/engine/rendering/renderer.hpp"
#include "../src/engine/scene/scene.hpp"
#include "../src/engine/input/input.hpp"
#include "../src/engine/scene/iactor.hpp"
#include "../src/engine/scene/icontroller.hpp"

using namespace StevensDev;

class BrownianController : public sgds::IController {
	private:
		/* Data member(s). */
		sgds::IActor* actor;
	public:
		/* Constructor(s). */
		BrownianController() {}
		/* Inherited function(s). */
		// ITickable.
		virtual void preTick() {}
		virtual void tick(float deltaTime) {
			actor->getRenderableSprite()
				->move(-5.0 * deltaTime, -5.0 * deltaTime);
		}
		virtual void postTick() {}
		// IController.
		virtual void possess(sgds::IActor* actor) {
			this->actor = actor;
		}
};

class BrownianActor : public sgds::IActor {
	private:
		sgdr::RenderableSprite renderableSprite;
	public:
		/* Constructor(s). */
		BrownianActor() {}
		/* Inherited function(s). */
		// IActor.
		virtual sgdr::RenderableSprite* getRenderableSprite() {
			return &renderableSprite;
		}
		virtual sgds::ICollidable* getCollidable() {
			return NULL;
		}
};

int main(int argc, char** argv) {
	/* Renderer. */
	sgdr::Renderer renderer;
	renderer.addTexture("smiley", "../textures/smiley_small.png");
	renderer.setupWindow(256, 256);

	/* Actors. */
	BrownianActor brownianActor;
	brownianActor.getRenderableSprite()
		->getSprite()
		.setTexture(renderer.getTexture("smiley"));

	/* Controllers. */
	BrownianController brownianController;
	brownianController.possess(&brownianActor);

	/* Renderables. */
	renderer.addRenderableSprite(brownianActor.getRenderableSprite());

	/* Scene. */
	// Input.
	sgds::Scene::getInstance().addTickable(&sgdi::Input::getInstance());
	// Controllers.
	sgds::Scene::getInstance().addTickable(&brownianController);

	while (renderer.isActive()) {
		sgds::Scene::getInstance().tick();

		std::cout << "Tick" << std::endl;

		renderer.draw();
	}

	
	return 0;
}