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

#include "../src/game/actors/pacman.hpp"
#include "../src/game/actors/wall.hpp"
#include "../src/game/controllers/pacman_controller.hpp"
#include "../src/game/factories/ghost_factory.hpp"
#include "../src/game/factories/pacman_factory.hpp"
#include "../src/game/factories/wall_factory.hpp"

/* Definitions. */
// Scene.
#define SCENE_SIZE 1024
#define SCENE_DIVISIONS 10

// Main.
int main(int argc, char** argv) {
	using namespace StevensDev;

	/* Assets. */
	// Textures.
	sgda::TextureManager::add("blue_box", "../textures/blue_box.png");
	//sgda::TextureManager::add("evil_pacman", "../textures/smiley_evil_small.png");
	sgda::TextureManager::add("red_box", "../textures/red_box.png");
	//sgda::TextureManager::add("pacman", "../textures/smiley_small.png");
	sgda::TextureManager::add("yellow_box", "../textures/yellow_box.png");

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

	/* Actors. */
	// Pacman.
	mga::Pacman* pacman = mgf::PacmanFactory::createActor();
	// Ghosts.
	mga::Ghost* blueGhost = mgf::GhostFactory::createActor(mga::Ghost::Color::BLUE);
	mga::Ghost* greenGhost = mgf::GhostFactory::createActor(mga::Ghost::Color::GREEN);
	mga::Ghost* redGhost = mgf::GhostFactory::createActor(mga::Ghost::Color::RED);
	mga::Ghost* yellowGhost = mgf::GhostFactory::createActor(mga::Ghost::Color::YELLOW);
	// Walls.
	sgdc::DynamicArray< mga::Wall* > walls =
		std::move(
			mgf::WallFactory::createWalls());

	/* Controllers. */
	// Pacman.
	mgc::PacmanController* pacmanController = mgf::PacmanFactory::createController();
	pacmanController->possess(pacman);
	// Ghosts.
	mgc::GhostController* blueGhostController = mgf::GhostFactory::createController();
	blueGhostController->possess(blueGhost);
	mgc::GhostController* greenGhostController = mgf::GhostFactory::createController();
	greenGhostController->possess(greenGhost);
	mgc::GhostController* redGhostController = mgf::GhostFactory::createController();
	redGhostController->possess(redGhost);
	mgc::GhostController* yellowGhostController = mgf::GhostFactory::createController();
	yellowGhostController->possess(yellowGhost);

	/* Events. */
	mge::ReverseEvent reverseEvent;

	/* Scene. */
	sgds::Scene::getInstance().addTickable(&sgde::EventBus::getDispatcher());
	sgds::Scene::getInstance().addTickable(&sgdi::Input::getInstance());
	sgds::Scene::getInstance().addTickable(&sgds::SceneManager::getSceneGraph());

	/* Main game loop. */
	while (sgdr::RenderManager::getRenderer().isActive()) {
		sgds::Scene::getInstance().tick();

		if (sgdi::Input::getInstance().wasPressed(sgdi::Input::Type::Q)) {
			sgde::EventBus::getDispatcher().dispatch(&reverseEvent);
		}

		sgdr::RenderManager::getRenderer().draw();
	}

	return 0;
}