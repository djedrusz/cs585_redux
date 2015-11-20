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
	addedTickables.append(tickable);
}

/* Remove a tickable. */
void Scene::removeTickable(ITickable* tickable) {
	removedTickables.append(tickable);
}

/* Tick the tickables. */
void Scene::tick() {
	/* Add the added tickables. */
	for (unsigned int i = 0; i < addedTickables.getSize(); i++) {
		tickables.append(addedTickables.get(i));
	}
	addedTickables = std::move(sgdc::DynamicArray< ITickable* >());

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

	/* Remove the removed tickables. */
	for (unsigned int i = 0; i < removedTickables.getSize(); i++) {
		for (unsigned int j = 0; j < tickables.getSize(); j++) {
			if (removedTickables.get(i) == tickables.get(j)) {
				tickables.remove(j);
				j--;
			}
		}
	}
	removedTickables = std::move(sgdc::DynamicArray< ITickable* >());
}

/* Set the renderer. */
void Scene::setRenderer(sgdr::Renderer* renderer) {
	this->renderer = renderer;
}

}
}