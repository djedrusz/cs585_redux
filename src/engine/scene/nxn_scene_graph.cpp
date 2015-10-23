/*
	Dominik Jedruszczak

	nxn_scene_graph.cpp
	Implementation of the "NxNSceneGraph" class.
*/

#include "nxn_scene_graph.hpp"

namespace StevensDev {
namespace sgds { // Stevens Game Development Scene.

NxNSceneGraph::NxNSceneGraph(float length, unsigned int divisions)
:	length(length),
	divisions(divisions) {
	;
}

void NxNSceneGraph::preTick() {
	for (unsigned int i = 0; i < addedCollidables.getSize(); i++) {
		collidables.append(addedCollidables.get(i));
	}
	addedCollidables = std::move(sgdc::DynamicArray< ICollidable* >());
}

void NxNSceneGraph::tick(float deltaTime) {
	;
}

void NxNSceneGraph::postTick() {
	for (unsigned int i = 0; i < removedCollidables.getSize(); i++) {
		for (unsigned int j = 0; j < collidables.getSize(); j++) {
			if (removedCollidables.get(i) == collidables.get(j)) {
				collidables.remove(j);
			}
		}
	}
	removedCollidables = std::move(sgdc::DynamicArray< ICollidable* >());
}

void NxNSceneGraph::addCollidable(ICollidable* collidable) {
	addedCollidables.append(collidable);
}

void NxNSceneGraph::removeCollidable(ICollidable* collidable) {
	removedCollidables.append(collidable);
}

sgdc::DynamicArray< ICollidable* > NxNSceneGraph::getCollisions(
	float x, float y, float width, float height) {
	
}

sgdc::DynamicArray< ICollidable* > NxNSceneGraph::getCollisions(
	float x, float y, float width, float height,
	unsigned short flags) {

}

sgdc::DynamicArray< ICollidable* > NxNSceneGraph::getCollisions(
	const RectangleBounds& rectangleBounds) {
	return sgdc::DynamicArray< ICollidable* >();
}

sgdc::DynamicArray< ICollidable* > NxNSceneGraph::getCollisions(
	const RectangleBounds& rectangleBounds,
	unsigned short flags) {

}

sgdc::DynamicArray< ICollidable* > NxNSceneGraph::getCollisions(
	const ICollidable* collidable) {

}

}
}