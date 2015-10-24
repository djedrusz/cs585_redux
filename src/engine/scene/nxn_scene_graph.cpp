/*
	Dominik Jedruszczak

	nxn_scene_graph.cpp
	Implementation of the "NxNSceneGraph" class.
*/

#include "nxn_scene_graph.hpp"

namespace StevensDev {
namespace sgds { // Stevens Game Development Scene.

void NxNSceneGraph::addCollidableToGraph(ICollidable* collidable) {
	/*
		 (x1, y1)______
				|      |
				|      |
				|______|
						(x2, y2)
	*/
	float unitLength = length / divisions;

	float x1, y1, x2, y2;

	x1 = collidable->getBounds().getX();
	y1 = collidable->getBounds().getY();
	x2 = x1 + collidable->getBounds().getWidth();
	y2 = y1 + collidable->getBounds().getHeight();

	unsigned int left, top, right, bottom;

	left = x1 / unitLength;
	top = y1 / unitLength;
	right = x2 / unitLength;
	bottom = y2 / unitLength;

	if (left < 0) {
		left = 0;
	}
	if (top < 0) {
		top = 0;
	}
	if (right > length - unitLength) {
		right = length - unitLength;
	}
	if (top > length - unitLength) {
		top = length - unitLength;
	}

	std::cout << left << " " << top << " " << right << " " << bottom << std::endl;

	for (unsigned int x = left; x <= right; x++) {
		for (unsigned int y = top; y <= bottom; y++) {
			graph[x][y].append(collidable);
		}
	}

}

void NxNSceneGraph::removeCollidableFromGraph(ICollidable* collidable) {
	/*
		 (x1, y1)______
				|      |
				|      |
				|______|
						(x2, y2)
	*/
	float unitLength = length / divisions;

	float x1, y1, x2, y2;

	x1 = collidable->getBounds().getX();
	y1 = collidable->getBounds().getY();
	x2 = x1 + collidable->getBounds().getWidth();
	y2 = y1 + collidable->getBounds().getHeight();

	unsigned int left, top, right, bottom;

	left = x1 / unitLength;
	top = y1 / unitLength;
	right = x2 / unitLength;
	bottom = y2 / unitLength;

	if (left < 0) {
		left = 0;
	}
	if (top < 0) {
		top = 0;
	}
	if (right > length - unitLength) {
		right = length - unitLength;
	}
	if (top > length - unitLength) {
		top = length - unitLength;
	}

	for (unsigned int x = left; x <= right; x++) {
		for (unsigned int y = top; y <= bottom; y++) {
			for (unsigned int i = 0; i < graph[x][y].getSize(); i++) {
				if (graph[x][y].get(i) == collidable) {
					graph[x][y].remove(i--);
				}
			}
		}
	}
}

NxNSceneGraph::NxNSceneGraph(float length, unsigned int divisions)
:	length(length),
	divisions(divisions) {
	/* Create the graph. */
	graph = new sgdc::DynamicArray< ICollidable* >*[divisions];
	for (unsigned int i = 0; i < divisions; i++) {
		graph[i] = new sgdc::DynamicArray< ICollidable* >[divisions];
	}
}

NxNSceneGraph::~NxNSceneGraph() {
	/* Destroy the graph. */
	for (unsigned int i = 0; i < divisions; i++) {
		delete[] graph[i];
	}
	delete[] graph;
}

void NxNSceneGraph::preTick() {
	/* Update the positions of the current collidables. */
	for (unsigned int i = 0; i < collidables.getSize(); i++) {
		removeCollidableFromGraph(collidables.get(i));
		addCollidableToGraph(collidables.get(i));
	}

	/* Add the new collidables. */
	for (unsigned int i = 0; i < addedCollidables.getSize(); i++) {
		collidables.append(addedCollidables.get(i));
		addCollidableToGraph(addedCollidables.get(i));
	}
	addedCollidables = std::move(sgdc::DynamicArray< ICollidable* >());
}

void NxNSceneGraph::tick(float deltaTime) {
	;
}

void NxNSceneGraph::postTick() {
	/* Remove the removed collidables. */
	for (unsigned int i = 0; i < removedCollidables.getSize(); i++) {
		for (unsigned int j = 0; j < collidables.getSize(); j++) {
			if (removedCollidables.get(i) == collidables.get(j)) {
				removeCollidableFromGraph(removedCollidables.get(i));
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

/* REMOVE AFTER TESTING. */
void NxNSceneGraph::print() {
	for (unsigned int y = 0; y < divisions; y++) {
		for (unsigned int x = 0; x < divisions; x++) {
			std::cout << graph[x][y].getSize() << " ";
		}
		std::cout << std::endl;
	}
}

}
}