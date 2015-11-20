/*
	Dominik Jedruszczak

	nxn_scene_graph.cpp
	Implementation of the "NxNSceneGraph" class.
*/

#include "nxn_scene_graph.hpp"

namespace StevensDev {
namespace sgds { // Stevens Game Development Scene.

void NxNSceneGraph::createGraph() {
	graph = new sgdc::DynamicArray< ICollidable* >*[divisions];
	for (unsigned int i = 0; i < divisions; i++) {
		graph[i] = new sgdc::DynamicArray< ICollidable* >[divisions];
	}
}

void NxNSceneGraph::destroyGraph() {
	for (unsigned int i = 0; i < divisions; i++) {
		delete[] graph[i];
	}
	delete[] graph;
}

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

	int left, top, right, bottom;

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
	if (right >= divisions) {
		right = divisions - 1;
	}
	if (bottom >= divisions) {
		bottom = divisions - 1;
	}

	for (int x = left; x <= right; x++) {
		for (int y = top; y <= bottom; y++) {
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

	int left, top, right, bottom;

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
	if (right >= divisions) {
		right = divisions - 1;
	}
	if (bottom >= divisions) {
		bottom = divisions - 1;
	}

	for (int x = left; x <= right; x++) {
		for (int y = top; y <= bottom; y++) {
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
	assert(length > 0);
	assert(divisions > 0);
	
	createGraph();
}

NxNSceneGraph::~NxNSceneGraph() {
	destroyGraph();
}

const float NxNSceneGraph::getLength() const {
	return length;
}

void NxNSceneGraph::preTick() {
	/* Update the positions of the current collidables. */
	destroyGraph();
	createGraph();
	for (unsigned int i = 0; i < collidables.getSize(); i++) {
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
	/*
		 (x1, y1)______
				|      |
				|      |
				|______|
						(x2, y2)
	*/
	float unitLength = length / divisions;

	float x1, y1, x2, y2;

	x1 = x;
	y1 = y;
	x2 = x1 + width;
	y2 = y1 + height;

	int left, top, right, bottom;

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
	if (right >= divisions) {
		right = divisions - 1;
	}
	if (bottom >= divisions) {
		bottom = divisions - 1;
	}

	sgdc::DynamicArray< ICollidable* > collisions;
	bool has = false;
	for (int x = left; x <= right; x++) {
		for (int y = top; y <= bottom; y++) {
			for (unsigned int i = 0; i < graph[x][y].getSize(); i++) {
				for (unsigned int j = 0; j < collisions.getSize(); j++) {
						if (collisions.get(j) == graph[x][y].get(i)) {
							has = true;
							break;
						}
					}
					if (has == false) {
						collisions.append(graph[x][y].get(i));
					}
					has = false;
			}
		}
	}

	return collisions;
}

sgdc::DynamicArray< ICollidable* > NxNSceneGraph::getCollisions(
	float x, float y, float width, float height,
	unsigned short flags) {
	/*
		 (x1, y1)______
				|      |
				|      |
				|______|
						(x2, y2)
	*/
	float unitLength = length / divisions;

	float x1, y1, x2, y2;

	x1 = x;
	y1 = y;
	x2 = x1 + width;
	y2 = y1 + height;

	int left, top, right, bottom;

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
	if (right >= divisions) {
		right = divisions - 1;
	}
	if (bottom >= divisions) {
		bottom = divisions - 1;
	}

	sgdc::DynamicArray< ICollidable* > collisions;
	bool has = false;
	for (int x = left; x <= right; x++) {
		for (int y = top; y <= bottom; y++) {
			for (unsigned int i = 0; i < graph[x][y].getSize(); i++) {
				if (graph[x][y].get(i)->getFlags() == flags) {
					for (unsigned int j = 0; j < collisions.getSize(); j++) {
						if (collisions.get(j) == graph[x][y].get(i)) {
							has = true;
							break;
						}
					}
					if (has == false) {
						collisions.append(graph[x][y].get(i));
					}
					has = false;
				}
			}
		}
	}

	return collisions;
}

sgdc::DynamicArray< ICollidable* > NxNSceneGraph::getCollisions(
	const RectangleBounds& rectangleBounds) {
	/*
		 (x1, y1)______
				|      |
				|      |
				|______|
						(x2, y2)
	*/
	float unitLength = length / divisions;

	float x1, y1, x2, y2;

	x1 = rectangleBounds.getX();
	y1 = rectangleBounds.getY();
	x2 = x1 + rectangleBounds.getWidth();
	y2 = y1 + rectangleBounds.getHeight();

	int left, top, right, bottom;

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
	if (right >= divisions) {
		right = divisions - 1;
	}
	if (bottom >= divisions) {
		bottom = divisions - 1;
	}

	sgdc::DynamicArray< ICollidable* > collisions;
	bool has = false;
	for (int x = left; x <= right; x++) {
		for (int y = top; y <= bottom; y++) {
			for (unsigned int i = 0; i < graph[x][y].getSize(); i++) {
				for (unsigned int j = 0; j < collisions.getSize(); j++) {
						if (collisions.get(j) == graph[x][y].get(i)) {
							has = true;
							break;
						}
					}
					if (has == false) {
						collisions.append(graph[x][y].get(i));
					}
					has = false;
			}
		}
	}

	return collisions;
}

sgdc::DynamicArray< ICollidable* > NxNSceneGraph::getCollisions(
	const RectangleBounds& rectangleBounds,
	unsigned short flags) {
	/*
		 (x1, y1)______
				|      |
				|      |
				|______|
						(x2, y2)
	*/
	float unitLength = length / divisions;

	float x1, y1, x2, y2;

	x1 = rectangleBounds.getX();
	y1 = rectangleBounds.getY();
	x2 = x1 + rectangleBounds.getWidth();
	y2 = y1 + rectangleBounds.getHeight();

	int left, top, right, bottom;

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
	if (right >= divisions) {
		right = divisions - 1;
	}
	if (bottom >= divisions) {
		bottom = divisions - 1;
	}

	sgdc::DynamicArray< ICollidable* > collisions;
	bool has = false;
	for (int x = left; x <= right; x++) {
		for (int y = top; y <= bottom; y++) {
			for (unsigned int i = 0; i < graph[x][y].getSize(); i++) {
				if (graph[x][y].get(i)->getFlags() == flags) {
					for (unsigned int j = 0; j < collisions.getSize(); j++) {
						if (collisions.get(j) == graph[x][y].get(i)) {
							has = true;
							break;
						}
					}
					if (has == false) {
						collisions.append(graph[x][y].get(i));
					}
					has = false;;
				}
			}
		}
	}

	return collisions;
}

sgdc::DynamicArray< ICollidable* > NxNSceneGraph::getCollisions(
	const ICollidable* collidable) {
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

	int left, top, right, bottom;

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
	if (right >= divisions) {
		right = divisions - 1;
	}
	if (bottom >= divisions) {
		bottom = divisions - 1;
	}

	sgdc::DynamicArray< ICollidable* > collisions;
	bool has = false;
	for (int x = left; x <= right; x++) {
		for (int y = top; y <= bottom; y++) {
			for (unsigned int i = 0; i < graph[x][y].getSize(); i++) {
				if (collidable->canCollide(graph[x][y].get(i)->getFlags()) &&
					graph[x][y].get(i) != collidable) {
					for (unsigned int j = 0; j < collisions.getSize(); j++) {
						if (collisions.get(j) == graph[x][y].get(i)) {
							has = true;
							break;
						}
					}
					if (has == false) {
						collisions.append(graph[x][y].get(i));
					}
					has = false;
				}
			}
		}
	}

	return collisions;
}

#ifdef NXN_SCENE_GRAPH_TESTING
/* REMOVE AFTER TESTING. */
void NxNSceneGraph::print() {
	for (unsigned int y = 0; y < divisions; y++) {
		for (unsigned int x = 0; x < divisions; x++) {
			std::cout << graph[x][y].getSize() << " ";
		}
		std::cout << std::endl;
	}
}
#endif

}
}