/*
	Dominik Jedruszczak

	test_rectangle_bounds.cpp
	Tests for the "RectangleBounds" class.
*/

#include "../gtest/include/gtest/gtest.h"
#include "../src/engine/scene/rectangle_bounds.hpp"

/* Test the default constructor and getters of a rectangle bounds. */
TEST(RectangleBounds, DefaultConstructorAndGetters) {
	StevensDev::sgds::RectangleBounds rectangleBounds(-1, -1, 5, 5);

	EXPECT_EQ(rectangleBounds.getX(), -1);
	EXPECT_EQ(rectangleBounds.getY(), -1);
	EXPECT_EQ(rectangleBounds.getWidth(), 5);
	EXPECT_EQ(rectangleBounds.getHeight(), 5);
}

/* Test the setters of a rectangle bounds. */
TEST(RectangleBounds, Setters) {
	StevensDev::sgds::RectangleBounds rectangleBounds(-2, -2, 6, 6);

	rectangleBounds.setX(-1);
	rectangleBounds.setY(-1);
	rectangleBounds.setWidth(5);
	rectangleBounds.setHeight(5);

	EXPECT_EQ(rectangleBounds.getX(), -1);
	EXPECT_EQ(rectangleBounds.getY(), -1);
	EXPECT_EQ(rectangleBounds.getWidth(), 5);
	EXPECT_EQ(rectangleBounds.getHeight(), 5);
}

/* Test setting the position of a rectangle bounds. */
TEST(RectangleBounds, SetPosition) {
	StevensDev::sgds::RectangleBounds rectangleBounds(-2, -2, 6, 6);

	rectangleBounds.setPosition(-1, -1);

	EXPECT_EQ(rectangleBounds.getX(), -1);
	EXPECT_EQ(rectangleBounds.getY(), -1);
}

/* Test setting the dimensions of a rectangle bounds. */
TEST(RectangleBounds, SetDimensions) {
	StevensDev::sgds::RectangleBounds rectangleBounds(-2, -2, 6, 6);

	rectangleBounds.setDimensions(5, 5);

	EXPECT_EQ(rectangleBounds.getWidth(), 5);
	EXPECT_EQ(rectangleBounds.getHeight(), 5);
}

/* Test top left no collision check of a rectangle bounds. */
TEST(RectangleBounds, TopLeftNoCollision) {
	StevensDev::sgds::RectangleBounds a(1, 1, 1, 1);
	StevensDev::sgds::RectangleBounds b(0, 0, 1, 1);

	EXPECT_FALSE(a.collides(b));
}

/* Test top middle no collision check of a rectangle bounds. */
TEST(RectangleBounds, TopMiddleNoCollision) {
	StevensDev::sgds::RectangleBounds a(1, 1, 1, 1);
	StevensDev::sgds::RectangleBounds b(1, 0, 1, 1);

	EXPECT_FALSE(a.collides(b));
}

/* Test top right no collision check of a rectangle bounds. */
TEST(RectangleBounds, TopRightNoCollision) {
	StevensDev::sgds::RectangleBounds a(1, 1, 1, 1);
	StevensDev::sgds::RectangleBounds b(2, 0, 1, 1);

	EXPECT_FALSE(a.collides(b));
}

/* Test right middle no collision check of a rectangle bounds. */
TEST(RectangleBounds, RightMiddleNoCollision) {
	StevensDev::sgds::RectangleBounds a(1, 1, 1, 1);
	StevensDev::sgds::RectangleBounds b(2, 1, 1, 1);

	EXPECT_FALSE(a.collides(b));
}

/* Test bottom right no collision check of a rectangle bounds. */
TEST(RectangleBounds, BottomRightNoCollision) {
	StevensDev::sgds::RectangleBounds a(1, 1, 1, 1);
	StevensDev::sgds::RectangleBounds b(2, 2, 1, 1);

	EXPECT_FALSE(a.collides(b));
}

/* Test bottom middle no collision check of a rectangle bounds. */
TEST(RectangleBounds, BottomMiddleNoCollision) {
	StevensDev::sgds::RectangleBounds a(1, 1, 1, 1);
	StevensDev::sgds::RectangleBounds b(1, 2, 1, 1);

	EXPECT_FALSE(a.collides(b));
}

/* Test bottom left no collision check of a rectangle bounds. */
TEST(RectangleBounds, BottomLeftNoCollision) {
	StevensDev::sgds::RectangleBounds a(1, 1, 1, 1);
	StevensDev::sgds::RectangleBounds b(0, 2, 1, 1);

	EXPECT_FALSE(a.collides(b));
}

/* Test left middle no collision check of a rectangle bounds. */
TEST(RectangleBounds, LeftMiddleNoCollision) {
	StevensDev::sgds::RectangleBounds a(1, 1, 1, 1);
	StevensDev::sgds::RectangleBounds b(0, 1, 1, 1);

	EXPECT_FALSE(a.collides(b));
}

/* Test top left collision check of a rectangle bounds. */
TEST(RectangleBounds, TopLeftCollision) {
	StevensDev::sgds::RectangleBounds a(1, 1, 1, 1);
	StevensDev::sgds::RectangleBounds b(.75, .75, .5, .5);

	EXPECT_TRUE(a.collides(b));
}

/* Test top middle collision check of a rectangle bounds. */
TEST(RectangleBounds, TopMiddleCollision) {
	StevensDev::sgds::RectangleBounds a(1, 1, 1, 1);
	StevensDev::sgds::RectangleBounds b(1.25, .75, .5, .5);

	EXPECT_TRUE(a.collides(b));
}

/* Test top right collision check of a rectangle bounds. */
TEST(RectangleBounds, TopRightCollision) {
	StevensDev::sgds::RectangleBounds a(1, 1, 1, 1);
	StevensDev::sgds::RectangleBounds b(1.75, .75, .5, .5);

	EXPECT_TRUE(a.collides(b));
}

/* Test right middle collision check of a rectangle bounds. */
TEST(RectangleBounds, RightMiddleCollision) {
	StevensDev::sgds::RectangleBounds a(1, 1, 1, 1);
	StevensDev::sgds::RectangleBounds b(1.75, 1.25, .5, .5);

	EXPECT_TRUE(a.collides(b));
}

/* Test bottom right collision check of a rectangle bounds. */
TEST(RectangleBounds, BottomRightCollision) {
	StevensDev::sgds::RectangleBounds a(1, 1, 1, 1);
	StevensDev::sgds::RectangleBounds b(1.75, 1.75, .5, .5);

	EXPECT_TRUE(a.collides(b));
}

/* Test bottom middle collision check of a rectangle bounds. */
TEST(RectangleBounds, BottomMiddleCollision) {
	StevensDev::sgds::RectangleBounds a(1, 1, 1, 1);
	StevensDev::sgds::RectangleBounds b(1.25, 1.75, .5, .5);

	EXPECT_TRUE(a.collides(b));
}

/* Test bottom left collision check of a rectangle bounds. */
TEST(RectangleBounds, BottomLeftCollision) {
	StevensDev::sgds::RectangleBounds a(1, 1, 1, 1);
	StevensDev::sgds::RectangleBounds b(.75, 1.75, .5, .5);

	EXPECT_TRUE(a.collides(b));
}

/* Test left middle collision check of a rectangle bounds. */
TEST(RectangleBounds, LeftMiddleCollision) {
	StevensDev::sgds::RectangleBounds a(1, 1, 1, 1);
	StevensDev::sgds::RectangleBounds b(.75, 1.25, .5, .5);

	EXPECT_TRUE(a.collides(b));
}

/* Test exact collision check of a rectangle bounds. */
TEST(RectangleBounds, ExactCollision) {
	StevensDev::sgds::RectangleBounds a(1, 1, 1, 1);
	StevensDev::sgds::RectangleBounds b(1, 1, 1, 1);

	EXPECT_TRUE(a.collides(b));
}