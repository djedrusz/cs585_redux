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
#include "../src/engine/events/ievent.hpp"
#include "../src/engine/events/event_bus.hpp"
#include "../src/engine/assets/texture_manager.hpp"

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
		/* Function(s). */
		void onMoveEvent(const sgde::IEvent* event) {
			actor->getRenderableSprite()
				->setPosition(127, 127);
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
		virtual sgde::MappedEventDispatcher* getEventDispatcher() {
			return NULL;
		}
};

class MoveEvent : public sgde::IEvent {
	private:
		/* Data member(s). */
		const std::string type = "move";
	public:
		/* Constructor(s). */
		MoveEvent() {};
		/* Inherited function(s). */
		// IEvent.
		virtual const std::string& getType() const {
			return type;
		}
};

int main(int argc, char** argv) {
	/* Textures. */
	sgda::TextureManager::add("smiley", "../textures/smiley_small.png");

	/* Renderer. */
	sgdr::Renderer renderer;
	renderer.setupWindow(256, 256);

	/* Actors. */
	BrownianActor brownianActor;
	brownianActor.getRenderableSprite()
		->getSprite()
		.setTexture(sgda::TextureManager::get("smiley"));

	/* Controllers. */
	BrownianController brownianController;
	brownianController.possess(&brownianActor);

	/* Renderables. */
	renderer.addRenderableSprite(brownianActor.getRenderableSprite());

	/* Events. */
	MoveEvent moveEvent;
	/* Callbacks. */
	std::function< void(const sgde::IEvent*) > moveEventCallback =
		std::bind(&BrownianController::onMoveEvent, &brownianController, std::placeholders::_1);
	sgde::EventBus::getDispatcher().addListener(&moveEvent, &moveEventCallback);

	/* Scene. */
	// Input.
	sgds::Scene::getInstance().addTickable(&sgdi::Input::getInstance());
	// Controllers.
	sgds::Scene::getInstance().addTickable(&brownianController);
	// Event bus.
	sgds::Scene::getInstance().addTickable(&sgde::EventBus::getDispatcher());

	while (renderer.isActive()) {
		sgds::Scene::getInstance().tick();

		if (sgdi::Input::getInstance().wasPressed(sgdi::Input::Type::A)) {
			sgde::EventBus::getDispatcher().dispatch(&moveEvent);
		}

		renderer.draw();
	}

	
	return 0;
}