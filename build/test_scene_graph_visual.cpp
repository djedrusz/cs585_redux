/*
	Dominik Jedruszczak

	test_scene_graph_visual.cpp
	Visual tests for the "NxNSceneGraph" class.
*/

#include "../src/engine/scene/nxn_scene_graph.hpp"

using namespace StevensDev;

class SimpleCollidable : public StevensDev::sgds::ICollidable {
	private:
		unsigned short flags;
		StevensDev::sgds::RectangleBounds& bounds;
	public:
		SimpleCollidable(StevensDev::sgds::RectangleBounds rectangleBounds, unsigned short flags) : bounds(rectangleBounds), flags(flags) { ; };
		const std::string& getActorKey() { return ""; }
		StevensDev::sgds::RectangleBounds& getBoundss() { return bounds; };
		const StevensDev::sgds::RectangleBounds& getBounds() const { return bounds; };
		unsigned short getFlags() const { return flags; };
		bool canCollide(const unsigned short flags) const { return flags == this->flags; };
		bool collides(const StevensDev::sgds::RectangleBounds& rectangleBounds) const { return false; };
};

int main(int arc, char** argv) {
	sgds::NxNSceneGraph scene(6.0f, 8);
	SimpleCollidable topLeft(sgds::RectangleBounds(-1, -1, 2, 2), 1);
	SimpleCollidable topRight(sgds::RectangleBounds(5, -1, 2, 2), 1);
	SimpleCollidable bottomLeft(sgds::RectangleBounds(-1, 5, 2, 2), 1);
	SimpleCollidable bottomRight(sgds::RectangleBounds(5, 5, 2, 2), 1);
	SimpleCollidable middle(sgds::RectangleBounds(2.5, 2.5, 1, 1), 1);
	SimpleCollidable over(sgds::RectangleBounds(-1, -1, 8, 8), 1);

	scene.addCollidable(&topLeft);
	scene.addCollidable(&topRight);
	scene.addCollidable(&bottomLeft);
	scene.addCollidable(&bottomRight);
	scene.addCollidable(&middle);
	scene.preTick();
	scene.tick(0);
	scene.postTick();
	scene.print();
	std::cout << std::endl;

	middle.getBoundss().setPosition(3.25, 3.25);
	scene.preTick();
	scene.tick(0);
	scene.postTick();
	scene.print();
	std::cout << std::endl;

	middle.getBoundss().setPosition(2.5, 2.5);
	middle.getBoundss().setDimensions(1.75, 1.75);
	scene.preTick();
	scene.tick(0);
	scene.postTick();
	scene.print();
	std::cout << std::endl;

	sgdc::DynamicArray< sgds::ICollidable* > collisions =
		scene.getCollisions(&over);
	std::cout << collisions.getSize() << " collisions." << std::endl;
	for (unsigned int i = 0; i < collisions.getSize(); i++) {
		assert(
			collisions.get(i) == &topLeft ||
			collisions.get(i) == &topRight ||
			collisions.get(i) == &bottomLeft ||
			collisions.get(i) == &bottomRight ||
			collisions.get(i) == &middle);
	}
	std::cout << std::endl;

	collisions =
		scene.getCollisions(sgds::RectangleBounds(-1, -1, 8, 8));
	std::cout << collisions.getSize() << " collisions." << std::endl;
	for (unsigned int i = 0; i < collisions.getSize(); i++) {
		assert(
			collisions.get(i) == &topLeft ||
			collisions.get(i) == &topRight ||
			collisions.get(i) == &bottomLeft ||
			collisions.get(i) == &bottomRight ||
			collisions.get(i) == &middle);
	}
	std::cout << std::endl;

	collisions =
		scene.getCollisions(-1, -1, 8, 8);
	std::cout << collisions.getSize() << " collisions." << std::endl;
	for (unsigned int i = 0; i < collisions.getSize(); i++) {
		assert(
			collisions.get(i) == &topLeft ||
			collisions.get(i) == &topRight ||
			collisions.get(i) == &bottomLeft ||
			collisions.get(i) == &bottomRight ||
			collisions.get(i) == &middle);
	}
	std::cout << std::endl;

	scene.removeCollidable(&topLeft);
	scene.removeCollidable(&topRight);
	scene.removeCollidable(&bottomLeft);
	scene.removeCollidable(&bottomRight);
	scene.removeCollidable(&middle);;
	scene.preTick();
	scene.tick(0);
	scene.postTick();
	scene.print();
	std::cout << std::endl;

	return 0;
}