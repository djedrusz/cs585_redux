/*
	Dominik Jedruszczak

	Assignment 9 (Final)
*/

/* Includes. */
// Local.
#include "../src/engine/assets/texture_manager.hpp"
#include "../src/engine/rendering/renderer.hpp"
#include "../src/engine/rendering/render_manager.hpp"
#include "../src/engine/scene/scene_manager.hpp"
#include "../src/engine/scene/scene.hpp"

#include "../src/game/actors/wall.hpp"
#include "../src/game/factories/wall_factory.hpp"
#include "../src/game/levels/pacman_level.hpp"
#include "../src/game/misc/blackboard.hpp"

/* Definitions. */
// Scene.
#define SCENE_SIZE 1024
#define SCENE_DIVISIONS 10
#define REVERSE_LOOP_TIME 40
#define REVERSE_DISPATCH_TIME 30

// Main.
int main(int argc, char** argv) {
	using namespace StevensDev;

	/* Assets. */
	// Textures.
	sgda::TextureManager::add("blue_box", "../textures/blue_box.png");

	sgda::TextureManager::add("pacman", "../textures/pacman_48.png");
	sgda::TextureManager::add("evil_pacman", "../textures/pacman_evil_48.png");

	sgda::TextureManager::add("blue_ghost", "../textures/blue_ghost_64.png");
	sgda::TextureManager::add("green_ghost", "../textures/green_ghost_64.png");
	sgda::TextureManager::add("red_ghost", "../textures/red_ghost_64.png");
	sgda::TextureManager::add("yellow_ghost", "../textures/yellow_ghost_64.png");

	/* Scene manager. */
	sgds::SceneManager::setSceneGraph(SCENE_SIZE, SCENE_DIVISIONS);

	/* Renderer. */
	sgdr::RenderManager::getRenderer()
		.setupWindow(
			sgds::SceneManager::getSceneGraph()
				.getLength(),
			sgds::SceneManager::getSceneGraph()
				.getLength());

	/* Level. */
	mgl::PacmanLevel::init();

	/* Events. */
	mge::ReverseEvent reverseEvent;
	mge::DeathEvent deathEvent(0);
	std::function< void (const sgde::IEvent*) > deathEventCallback =
		std::bind(&mgm::Blackboard::onDeathEvent, std::placeholders::_1);
	sgde::EventBus::getDispatcher().addListener(&deathEvent, &deathEventCallback);
	mge::ResetEvent resetEvent;
	std::function< void (const sgde::IEvent*) > resetEventCallback =
		std::bind(&mgm::Blackboard::onResetEvent, std::placeholders::_1);
	sgde::EventBus::getDispatcher().addListener(&resetEvent, &resetEventCallback);

	/* Scene. */
	sgds::Scene::getInstance().addTickable(&sgde::EventBus::getDispatcher());
	sgds::Scene::getInstance().addTickable(&sgdi::Input::getInstance());
	sgds::Scene::getInstance().addTickable(&sgds::SceneManager::getSceneGraph());

	time_t start = time(NULL);
	time_t end;
	bool dispatched = false;
	/* Main game loop. */
	while (sgdr::RenderManager::getRenderer().isActive()) {
		sgds::Scene::getInstance().tick();

		/* Trigger reverse. */
		end = time(NULL);
		time_t elapsed = difftime(end, start);
		if (elapsed == REVERSE_DISPATCH_TIME && dispatched == false) {
			sgde::EventBus::getDispatcher().dispatch(&reverseEvent);
			dispatched = true;
		}
		if (elapsed > REVERSE_LOOP_TIME) {
			sgde::EventBus::getDispatcher().dispatch(&reverseEvent);
			start = time(NULL);
			dispatched = false;
		}

		if (sgdi::Input::getInstance().wasPressed(sgdi::Input::Type::Q)) {
			sgde::EventBus::getDispatcher().dispatch(&reverseEvent);
		}
		if (sgdi::Input::getInstance().wasPressed(sgdi::Input::Type::R)) {
			mgl::PacmanLevel::reset();
		}

		if (mgm::Blackboard::getGhostCount() == 0 || mgm::Blackboard::getPacmanCount() == 0) {
			mgl::PacmanLevel::reset();
		}

		sgdr::RenderManager::getRenderer().draw();
	}

	return 0;
}