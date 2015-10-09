/*
	Dominik Jedruszczak

	test_renderable_sprite.cpp
	Tests for the "RenderableSprite" class.
*/

#include "../gtest/include/gtest/gtest.h"
#include "../src/engine/rendering/renderable_sprite.hpp"

/* Test the construction of a renderable sprite. */
TEST(RenderableSprite, Constructor) {
	StevensDev::sgdr::RenderableSprite sprite(3.0f, 4.0f);

	EXPECT_EQ(sprite.getPositionX(), 3.0f);
	EXPECT_EQ(sprite.getPositionY(), 4.0f);
}

/* Test the copy constructor of a renderable sprite. */
TEST(RenderableSprite, CopyConstructor) {
	StevensDev::sgdr::RenderableSprite sprite(3.0f, 4.0f);
	StevensDev::sgdr::RenderableSprite sprite2(sprite);

	EXPECT_EQ(sprite2.getPositionX(), 3.0f);
	EXPECT_EQ(sprite2.getPositionY(), 4.0f);
}

/* Test the move constructor of a renderable sprite. */
TEST(RenderableSprite, MoveConstructor) {
	StevensDev::sgdr::RenderableSprite sprite(3.0f, 4.0f);
	StevensDev::sgdr::RenderableSprite sprite2(std::move(sprite));

	EXPECT_EQ(sprite2.getPositionX(), 3.0f);
	EXPECT_EQ(sprite2.getPositionY(), 4.0f);
}

/* Test the copy assignment operator of a renderable sprite. */
TEST(RenderableSprite, CopyAssignmentOperator) {
	StevensDev::sgdr::RenderableSprite sprite(3.0f, 4.0f);
	StevensDev::sgdr::RenderableSprite sprite2 = sprite;

	EXPECT_EQ(sprite2.getPositionX(), 3.0f);
	EXPECT_EQ(sprite2.getPositionY(), 4.0f);
}

/* Test the move assignment operator of a renderable sprite. */
TEST(RenderableSprite, MoveAssignmentOperator) {
	StevensDev::sgdr::RenderableSprite sprite(3.0f, 4.0f);
	StevensDev::sgdr::RenderableSprite sprite2 = std::move(sprite);

	EXPECT_EQ(sprite2.getPositionX(), 3.0f);
	EXPECT_EQ(sprite2.getPositionY(), 4.0f);
}

/* Test setting the x-position of a renderable sprite. */
TEST(RenderableSprite, SetPositionX) {
	StevensDev::sgdr::RenderableSprite sprite(3.0f, 4.0f);
	sprite.setPositionX(5.0f);

	EXPECT_EQ(sprite.getPositionX(), 5.0f);
	EXPECT_EQ(sprite.getPositionY(), 4.0f);
}

/* Test setting the y-position of a renderable sprite. */
TEST(RenderableSprite, SetPositionY) {
	StevensDev::sgdr::RenderableSprite sprite(3.0f, 4.0f);
	sprite.setPositionY(5.0f);

	EXPECT_EQ(sprite.getPositionX(), 3.0f);
	EXPECT_EQ(sprite.getPositionY(), 5.0f);
}

/* Test setting the position of a renderable sprite. */
TEST(RenderableSprite, SetPosition) {
	StevensDev::sgdr::RenderableSprite sprite(3.0f, 4.0f);
	sprite.setPosition(1.0f, 2.0f);

	EXPECT_EQ(sprite.getPositionX(), 1.0f);
	EXPECT_EQ(sprite.getPositionY(), 2.0f);
}

/* Test moving a renderable sprite. */
TEST(RenderableSprite, Move) {
	StevensDev::sgdr::RenderableSprite sprite(3.0f, 4.0f);
	sprite.move(5.0f, 6.0f);

	EXPECT_EQ(sprite.getPositionX(), 8.0f);
	EXPECT_EQ(sprite.getPositionY(), 10.0f);
}