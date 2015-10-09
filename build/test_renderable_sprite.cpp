/*
	Dominik Jedruszczak

	test_renderable_sprite.cpp
	Tests for the "RenderableSprite" class.
*/

#include "../gtest/include/gtest/gtest.h"
#include "../src/engine/rendering/renderable_sprite.hpp"

/* Test the construction of a renderable sprite. */
TEST(RenderableSprite, Construction) {
	StevensDev::sgdr::RenderableSprite sprite(3.0f, 4.0f);

	EXPECT_EQ(sprite.getPositionX(), 3.0f);
	EXPECT_EQ(sprite.getPositionY(), 4.0f);
}