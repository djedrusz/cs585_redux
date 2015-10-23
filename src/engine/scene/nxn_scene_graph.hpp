/*
	Dominik Jedruszczak

	nxn_scene_graph.hpp
	Declaration of the "NxNSceneGraph" class.
*/

#ifndef INCLUDED_NXN_SCENE_GRAPH
#define INCLUDED_NXN_SCENE_GRAPH

#include "itickable.hpp"
#include "../containers/dynamic_array.hpp"
#include "icollidable.hpp"

namespace StevensDev {
namespace sgds { // Stevens Game Development Scene.

/* A square scene graph. */
class NxNSceneGraph : public ITickable {
	private:
		/* Constructor(s). */
		NxNSceneGraph();
		/* Data member(s). */
		const float length;
		const unsigned int divisions;
		sgdc::DynamicArray< ICollidable* > addedCollidables; // Collidables to be added.
		sgdc::DynamicArray< ICollidable* > removedCollidables; // Collidables to be removed.
		sgdc::DynamicArray< ICollidable* > collidables;
	public:
		/* Constructor(s). */
		NxNSceneGraph(float length, unsigned int divisions);
		NxNSceneGraph(const NxNSceneGraph& nxNSceneGraph);
		NxNSceneGraph(NxNSceneGraph&& nxNSceneGraph);
		/* Function(s). */
		void preTick();
		void tick(float deltaTime);
		void postTick();
		void addCollidable(ICollidable* collidable);
		void removeCollidable(ICollidable* collidable);
		sgdc::DynamicArray< ICollidable* > getCollisions(
			float x, float y, float width, float height);
		sgdc::DynamicArray< ICollidable* > getCollisions(
			float x, float y, float width, float height,
			unsigned short flags);
		sgdc::DynamicArray< ICollidable* > getCollisions(
			const RectangleBounds& rectangleBounds);
		sgdc::DynamicArray< ICollidable* > getCollisions(
			const RectangleBounds& rectangleBounds,
			unsigned short flags);
		sgdc::DynamicArray< ICollidable* > getCollisions(
			const ICollidable* collidable); // Does not return self.
};

}
}

#endif