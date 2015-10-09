/*
	Dominik Jedruszczak

	scene.hpp
	Declaration of the "Scene" singleton.
*/

#ifndef INCLUDED_SCENE
#define INCLUDED_SCENE

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
	public:
		/* Function(s). */
		static Input& getInstance(); // Return the only instance.
		void addTickable(ITickable* tickable); // Add a tickable.
		void removeTickable(ITickable* tickable); // Remove a tickable.
		void tick(); // Tick the tickables.
};

}
}

#endif