/*
	Dominik Jedruszczak
*/

#include "scene_manager.hpp"

namespace StevensDev {
namespace sgds { // Stevens Game Development Scene.

/* Initialize static data member(s). */
NxNSceneGraph SceneManager::sceneGraph(1, 1);

void SceneManager::setSceneGraph(float length, int divisions) {
	new (&sceneGraph) NxNSceneGraph(length, divisions);
}

NxNSceneGraph& SceneManager::getSceneGraph() {
	return sceneGraph;
}

}
}