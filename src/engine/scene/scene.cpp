/*
	Dominik Jedruszczak

	scene.cpp
	Implementation of the "Scene" singleton.
*/

#include "scene.hpp"

namespace StevensDev {
namespace sgds { // Stevens Game Development Scene.

/* Return the only instance. */
Scene& Scene::getInstance() {
	static Scene instance;

	return instance;
}

/* Add a tickable. */
void Scene::addTickable(ITickable* tickable) {
	tickables.append(tickable);
}

/* Remove a tickable. */
void Scene::removeTickable(ITickable* tickable) {
	for (unsigned int i = 0; i < tickables.getSize(); i++) {
		if (tickables[i] == tickable) {
			tickables.remove(i);
		}
	}
}

/* Tick the tickables. */
void Scene::tick() {
	double secondsElapsed = difftime(previousTime, time(NULL));

	for (unsigned int i = 0; i < tickables.getSize(); i++) {
		tickables[i]->preTick();
	}
	for (unsigned int i = 0; i < tickables.getSize(); i++) {
		tickables[i]->tick(secondsElapsed);
	}
	for (unsigned int i = 0; i < tickables.getSize(); i++) {
		tickables[i]->postTick();
	}

	previousTime = time(NULL);
}

/* Set the renderer. */
void Scene::setRenderer(sgdr::Renderer* renderer) {
	this->renderer = renderer;
}

}
}