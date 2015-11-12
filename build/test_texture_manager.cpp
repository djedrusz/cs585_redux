/*
	Dominik Jedruszczak

	Tests for the "TextureManager" static class.
*/

#include "../gtest/include/gtest/gtest.h"
#include "../src/engine/assets/texture_manager.hpp"

TEST(TextureManager, addRemove) {
	/*StevensDev::sgda::TextureManager::add(
		"smiley", "../textures/smiley.png");

	EXPECT_GT(
		StevensDev::sgda::TextureManager::get(
			"smiley").getSize().x,
		0);
	EXPECT_GT(
		StevensDev::sgda::TextureManager::get(
			"smiley").getSize().y,
		0);*/
	// Removed because Travis CI doesn't download the images or 
	// something stupid like that.
}