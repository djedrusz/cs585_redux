/*
	Dominik Jedruszczak

	scene.hpp
	Declaration of the "Scene" singleton.
*/

#ifndef INCLUDED_SCENE
#define INCLUDED_SCENE

#include <ctime>
#include "itickable.hpp"
#include "../containers/dynamic_array.hpp"
#include "../rendering/renderer.hpp"

namespace StevensDev {
namespace sgds { // Stevens Game Development Scene.

/* Scene singleton. */
class Scene {
	private:
		/* Constructor(s). */
		Scene() {}; // Default constructor.
		Scene(const Scene& scene) = delete; // Copy constructor.
		/* Operator(s). */
		Scene& operator = (const Scene& scene) = delete; // Copy assignment operator.
		/* Data member(s). */
		time_t previousTime = time(NULL); // The previous time.
		sgdc::DynamicArray< ITickable* > tickables; // The tickables.
		sgdr::Renderer* renderer; // The renderer.
	public:
		/* Function(s). */
		static Scene& getInstance(); // Return the only instance.
		void addTickable(ITickable* tickable); // Add a tickable.
		void removeTickable(ITickable* tickable); // Remove a tickable.
		void tick(); // Tick the tickables.
		void setRenderer(sgdr::Renderer* renderer); // Set the renderer.
};

}
}

#endif