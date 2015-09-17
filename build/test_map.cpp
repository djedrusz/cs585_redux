/*
	Dominik Jedruszczak

	test_map.cpp
	Tests for the "Map" class.
*/

#include "../gtest/include/gtest/gtest.h"
#include "../src/engine/containers/map.hpp"

TEST(Map, General) {
	StevensDev::sgdc::Map<int>* map = new StevensDev::sgdc::Map<int>();
	map->add("a", 0);
	map->add("aa", 3);
	map->add("ab", 4);
	map->add("ac", 5);
	map->add("b", 1);
	map->add("ba", 6);
	map->add("bb", 7);
	map->add("bc", 8);
	map->add("c", 2);
	map->add("ca", 9);
	map->add("cb", 10);
	map->add("cc", 11);
	map->print();
	delete map;
}