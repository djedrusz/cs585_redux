/*
	Dominik Jedruszczak

	test_scene_graph_visual.cpp
	Visual tests for the "NxNSceneGraph" class.
*/

#include "../src/engine/scene/nxn_scene_graph.hpp"

using namespace StevensDev;

class SimpleCollidable : public sgds::ICollidable {
	private:
		sgds::RectangleBounds& bounds;
	public:
		SimpleCollidable(sgds::RectangleBounds rectangleBounds) : bounds(rectangleBounds) { ; };
		const sgds::RectangleBounds& getBounds() const { return bounds; };
		unsigned short getFlags() const { return 0; };
		bool canCollide(const unsigned short flags) const { return false; };
		bool collides(const sgds::RectangleBounds& rectangleBounds) const { return false; };
};

int main(int arc, char** argv) {
	sgds::NxNSceneGraph scene(6.0f, 8);

	scene.print();

	SimpleCollidable collidable(sgds::RectangleBounds(1, 1, 1.75, 2.5));

	std::cout << std::endl;
	scene.addCollidable(&collidable);
	scene.preTick();
	scene.print();

	std::cout << std::endl;
	scene.removeCollidable(&collidable);
	scene.postTick();
	scene.print();

	return 0;
}