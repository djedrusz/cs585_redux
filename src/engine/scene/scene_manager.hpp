/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_SCENE_MANAGER
#define INCLUDED_SCENE_MANAGER

#include "nxn_scene_graph.hpp"

namespace StevensDev {
namespace sgds { // Stevens Game Development Scene.

/* A static scene graph. */
class SceneManager {
	private:
		/* Constructor(s). */
		SceneManager() {};
		SceneManager(const SceneManager& sceneManager) = delete;
		/* Operator(s). */
		SceneManager& operator = (const SceneManager& sceneManager) = delete;
		/* Data member(s). */
		static NxNSceneGraph sceneGraph;
	public:
		/* Function(s). */
		static void setSceneGraph(float length, int divisions);
		static NxNSceneGraph& getSceneGraph();
};

}
}

#endif