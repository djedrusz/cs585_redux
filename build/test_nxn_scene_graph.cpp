/*
	Dominik Jedruszczak

	test_nxn_scene_graph.cpp
	Tests for the "NxNSceneGraph" class.
*/

#include "../gtest/include/gtest/gtest.h"
#include "../src/engine/scene/nxn_scene_graph.hpp"

class SimpleCollidable : public StevensDev::sgds::ICollidable {
	private:
		unsigned short flags;
		StevensDev::sgds::RectangleBounds& bounds;
	public:
		SimpleCollidable(StevensDev::sgds::RectangleBounds rectangleBounds, unsigned short flags) : bounds(rectangleBounds), flags(flags) { ; };
		StevensDev::sgds::RectangleBounds& getBoundss() { return bounds; };
		const StevensDev::sgds::RectangleBounds& getBounds() const { return bounds; };
		unsigned short getFlags() const { return flags; };
		bool canCollide(const unsigned short flags) const { return false; };
		bool collides(const StevensDev::sgds::RectangleBounds& rectangleBounds) const { return false; };
};

/* Test float collision. */
TEST(NxNSceneGraph, FloatCollision) {
	StevensDev::sgds::NxNSceneGraph scene(6.0f, 8);
	SimpleCollidable topLeft(StevensDev::sgds::RectangleBounds(-1, -1, 2, 2), 1);
	SimpleCollidable topRight(StevensDev::sgds::RectangleBounds(5, -1, 2, 2), 1);
	SimpleCollidable bottomLeft(StevensDev::sgds::RectangleBounds(-1, 5, 2, 2), 1);
	SimpleCollidable bottomRight(StevensDev::sgds::RectangleBounds(5, 5, 2, 2), 1);
	SimpleCollidable middle(StevensDev::sgds::RectangleBounds(2.5, 2.5, 1, 1), 1);

	scene.addCollidable(&topLeft);
	scene.addCollidable(&topRight);
	scene.addCollidable(&bottomLeft);
	scene.addCollidable(&bottomRight);
	scene.addCollidable(&middle);
	scene.preTick();
	scene.tick(0);
	scene.postTick();

	StevensDev::sgdc::DynamicArray< StevensDev::sgds::ICollidable* > collisions =
		scene.getCollisions(-1, -1, 8, 8);
	for (unsigned int i = 0; i < collisions.getSize(); i++) {
		assert(
			collisions.get(i) == &topLeft ||
			collisions.get(i) == &topRight ||
			collisions.get(i) == &bottomLeft ||
			collisions.get(i) == &bottomRight ||
			collisions.get(i) == &middle);
	}
	
	EXPECT_EQ(collisions.getSize(), 5);
}

/* Test float & flag collision. */
TEST(NxNSceneGraph, FloatFlagCollision) {
	StevensDev::sgds::NxNSceneGraph scene(6.0f, 8);
	SimpleCollidable topLeft(StevensDev::sgds::RectangleBounds(-1, -1, 2, 2), 1);
	SimpleCollidable topRight(StevensDev::sgds::RectangleBounds(5, -1, 2, 2), 1);
	SimpleCollidable bottomLeft(StevensDev::sgds::RectangleBounds(-1, 5, 2, 2), 1);
	SimpleCollidable bottomRight(StevensDev::sgds::RectangleBounds(5, 5, 2, 2), 1);
	SimpleCollidable middle(StevensDev::sgds::RectangleBounds(2.5, 2.5, 1, 1), 1);

	scene.addCollidable(&topLeft);
	scene.addCollidable(&topRight);
	scene.addCollidable(&bottomLeft);
	scene.addCollidable(&bottomRight);
	scene.addCollidable(&middle);
	scene.preTick();
	scene.tick(0);
	scene.postTick();

	StevensDev::sgdc::DynamicArray< StevensDev::sgds::ICollidable* > collisions =
		scene.getCollisions(-1, -1, 8, 8, 0);
	for (unsigned int i = 0; i < collisions.getSize(); i++) {
		assert(
			collisions.get(i) == &topLeft ||
			collisions.get(i) == &topRight ||
			collisions.get(i) == &bottomLeft ||
			collisions.get(i) == &bottomRight ||
			collisions.get(i) == &middle);
	}
	EXPECT_EQ(collisions.getSize(), 0);

	collisions =
		scene.getCollisions(-1, -1, 8, 8, 1);
	for (unsigned int i = 0; i < collisions.getSize(); i++) {
		assert(
			collisions.get(i) == &topLeft ||
			collisions.get(i) == &topRight ||
			collisions.get(i) == &bottomLeft ||
			collisions.get(i) == &bottomRight ||
			collisions.get(i) == &middle);
	}
	EXPECT_EQ(collisions.getSize(), 5);
}

/* Test rectangle bounds collision. */
TEST(NxNSceneGraph, RectangleBoundsCollision) {
	StevensDev::sgds::NxNSceneGraph scene(6.0f, 8);
	SimpleCollidable topLeft(StevensDev::sgds::RectangleBounds(-1, -1, 2, 2), 1);
	SimpleCollidable topRight(StevensDev::sgds::RectangleBounds(5, -1, 2, 2), 1);
	SimpleCollidable bottomLeft(StevensDev::sgds::RectangleBounds(-1, 5, 2, 2), 1);
	SimpleCollidable bottomRight(StevensDev::sgds::RectangleBounds(5, 5, 2, 2), 1);
	SimpleCollidable middle(StevensDev::sgds::RectangleBounds(2.5, 2.5, 1, 1), 1);

	scene.addCollidable(&topLeft);
	scene.addCollidable(&topRight);
	scene.addCollidable(&bottomLeft);
	scene.addCollidable(&bottomRight);
	scene.addCollidable(&middle);
	scene.preTick();
	scene.tick(0);
	scene.postTick();

	StevensDev::sgdc::DynamicArray< StevensDev::sgds::ICollidable* > collisions =
		scene.getCollisions(StevensDev::sgds::RectangleBounds(-1, -1, 8, 8));
	for (unsigned int i = 0; i < collisions.getSize(); i++) {
		assert(
			collisions.get(i) == &topLeft ||
			collisions.get(i) == &topRight ||
			collisions.get(i) == &bottomLeft ||
			collisions.get(i) == &bottomRight ||
			collisions.get(i) == &middle);
	}
	
	EXPECT_EQ(collisions.getSize(), 5);
}

/* Test rectangle bounds & flag collision. */
TEST(NxNSceneGraph, RectangleBoundsFlagCollision) {
	StevensDev::sgds::NxNSceneGraph scene(6.0f, 8);
	SimpleCollidable topLeft(StevensDev::sgds::RectangleBounds(-1, -1, 2, 2), 1);
	SimpleCollidable topRight(StevensDev::sgds::RectangleBounds(5, -1, 2, 2), 1);
	SimpleCollidable bottomLeft(StevensDev::sgds::RectangleBounds(-1, 5, 2, 2), 1);
	SimpleCollidable bottomRight(StevensDev::sgds::RectangleBounds(5, 5, 2, 2), 1);
	SimpleCollidable middle(StevensDev::sgds::RectangleBounds(2.5, 2.5, 1, 1), 1);

	scene.addCollidable(&topLeft);
	scene.addCollidable(&topRight);
	scene.addCollidable(&bottomLeft);
	scene.addCollidable(&bottomRight);
	scene.addCollidable(&middle);
	scene.preTick();
	scene.tick(0);
	scene.postTick();

	StevensDev::sgdc::DynamicArray< StevensDev::sgds::ICollidable* > collisions =
		scene.getCollisions(StevensDev::sgds::RectangleBounds(-1, -1, 8, 8), 0);
	for (unsigned int i = 0; i < collisions.getSize(); i++) {
		assert(
			collisions.get(i) == &topLeft ||
			collisions.get(i) == &topRight ||
			collisions.get(i) == &bottomLeft ||
			collisions.get(i) == &bottomRight ||
			collisions.get(i) == &middle);
	}
	EXPECT_EQ(collisions.getSize(), 0);

	collisions =
		scene.getCollisions(StevensDev::sgds::RectangleBounds(-1, -1, 8, 8), 1);
	for (unsigned int i = 0; i < collisions.getSize(); i++) {
		assert(
			collisions.get(i) == &topLeft ||
			collisions.get(i) == &topRight ||
			collisions.get(i) == &bottomLeft ||
			collisions.get(i) == &bottomRight ||
			collisions.get(i) == &middle);
	}
	EXPECT_EQ(collisions.getSize(), 5);
}

/* Test collider collision. */
TEST(NxNSceneGraph, ColliderCollision) {
	StevensDev::sgds::NxNSceneGraph scene(6.0f, 8);
	SimpleCollidable topLeft(StevensDev::sgds::RectangleBounds(-1, -1, 2, 2), 1);
	SimpleCollidable topRight(StevensDev::sgds::RectangleBounds(5, -1, 2, 2), 1);
	SimpleCollidable bottomLeft(StevensDev::sgds::RectangleBounds(-1, 5, 2, 2), 1);
	SimpleCollidable bottomRight(StevensDev::sgds::RectangleBounds(5, 5, 2, 2), 1);
	SimpleCollidable middle(StevensDev::sgds::RectangleBounds(2.5, 2.5, 1, 1), 1);
	SimpleCollidable over(StevensDev::sgds::RectangleBounds(-1, -1, 8, 8), 0);
	SimpleCollidable over2(StevensDev::sgds::RectangleBounds(-1, -1, 8, 8), 1);

	scene.addCollidable(&topLeft);
	scene.addCollidable(&topRight);
	scene.addCollidable(&bottomLeft);
	scene.addCollidable(&bottomRight);
	scene.addCollidable(&middle);
	scene.preTick();
	scene.tick(0);
	scene.postTick();

	StevensDev::sgdc::DynamicArray< StevensDev::sgds::ICollidable* > collisions =
		scene.getCollisions(&over);
	for (unsigned int i = 0; i < collisions.getSize(); i++) {
		assert(
			collisions.get(i) == &topLeft ||
			collisions.get(i) == &topRight ||
			collisions.get(i) == &bottomLeft ||
			collisions.get(i) == &bottomRight ||
			collisions.get(i) == &middle);
	}
	EXPECT_EQ(collisions.getSize(), 0);

	collisions =
		scene.getCollisions(&over2);
	for (unsigned int i = 0; i < collisions.getSize(); i++) {
		assert(
			collisions.get(i) == &topLeft ||
			collisions.get(i) == &topRight ||
			collisions.get(i) == &bottomLeft ||
			collisions.get(i) == &bottomRight ||
			collisions.get(i) == &middle);
	}
	EXPECT_EQ(collisions.getSize(), 5);
}