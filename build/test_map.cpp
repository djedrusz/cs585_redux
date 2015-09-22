/*
	Dominik Jedruszczak

	test_map.cpp
	Tests for the "Map" class.
*/

#include "../gtest/include/gtest/gtest.h"
#include "../src/engine/memory/counting_allocator.hpp"
#include "../src/engine/containers/map.hpp"

/* Globals. */
StevensDev::sgdm::CountingAllocator< StevensDev::sgdc::MapNode< int > >* TEST_MAP_countingMapAllocator = new StevensDev::sgdm::CountingAllocator< StevensDev::sgdc::MapNode< int > >();
StevensDev::sgdm::CountingAllocator< std::string >* TEST_MAP_countingKeysAllocator = new StevensDev::sgdm::CountingAllocator< std::string >();
StevensDev::sgdm::CountingAllocator< int >* TEST_MAP_countingValuesAllocator = new StevensDev::sgdm::CountingAllocator< int >();
StevensDev::sgdc::Map< int >* TEST_MAP_map = new StevensDev::sgdc::Map< int >(TEST_MAP_countingMapAllocator, TEST_MAP_countingKeysAllocator, TEST_MAP_countingValuesAllocator);

/* Test the construction of a map. */
TEST(Map, Construction) {
	EXPECT_EQ(TEST_MAP_countingKeysAllocator->getAllocations(), DYNAMIC_ARRAY_DEFAULT_CAPACITY);

	EXPECT_EQ(TEST_MAP_countingValuesAllocator->getAllocations(), DYNAMIC_ARRAY_DEFAULT_CAPACITY);

	EXPECT_EQ(TEST_MAP_countingMapAllocator->getAllocations(), 1);
}

/* Test getting the keys of a map. */
TEST(Map, GetKeys) {
	EXPECT_EQ(TEST_MAP_map->getKeys().getSize(), 0);
}

/* Test getting the values of a map. */
TEST(Map, GetValues) {
	EXPECT_EQ(TEST_MAP_map->getValues().getSize(), 0);
}

/* Test puting a node to the root of a map. */
TEST(Map, PutRoot) {
	TEST_MAP_map->put("a", 1);

	EXPECT_EQ(TEST_MAP_countingMapAllocator->getAllocations(), 2);

	EXPECT_EQ(TEST_MAP_map->getKeys().getSize(), 1);
	EXPECT_EQ(TEST_MAP_map->getKeys()[0], "a");

	EXPECT_EQ(TEST_MAP_map->getValues().getSize(), 1);
	EXPECT_EQ(TEST_MAP_map->getValues()[0], 1);
}

/* Test puting a node to another node. */
TEST(Map, PutSubNode) {
	TEST_MAP_map->put("aa", 2);

	EXPECT_EQ(TEST_MAP_countingMapAllocator->getAllocations(), 3);

	EXPECT_EQ(TEST_MAP_map->getKeys().getSize(), 2);
	EXPECT_EQ(TEST_MAP_map->getKeys()[1], "aa");

	EXPECT_EQ(TEST_MAP_map->getValues().getSize(), 2);
	EXPECT_EQ(TEST_MAP_map->getValues()[1], 2);
}

/* Test puting a node through a node which does not exist. */
TEST(Map, PutIndirect) {
	TEST_MAP_map->put("bbbb", 3);

	EXPECT_EQ(TEST_MAP_countingMapAllocator->getAllocations(), 7);

	EXPECT_EQ(TEST_MAP_map->getKeys().getSize(), 3);
	EXPECT_EQ(TEST_MAP_map->getKeys()[2], "bbbb");

	EXPECT_EQ(TEST_MAP_map->getValues().getSize(), 3);
	EXPECT_EQ(TEST_MAP_map->getValues()[2], 3);
}

/* Test checking if a map has a value when there exists a node with a value. */
TEST(Map, HasValue) {
	EXPECT_TRUE(TEST_MAP_map->has("a"));
	EXPECT_TRUE(TEST_MAP_map->has("aa"));
	EXPECT_TRUE(TEST_MAP_map->has("bbbb"));
}

/* Test checking if a map has a value when there exists a node without a value. */
TEST(Map, HasNoValue) {
	EXPECT_FALSE(TEST_MAP_map->has("b"));
	EXPECT_FALSE(TEST_MAP_map->has("bb"));
	EXPECT_FALSE(TEST_MAP_map->has("bbb"));
}

/* Test checking if a map has a value when there doesn't exist a node. */
TEST(Map, HasDoesntExist) {
	EXPECT_FALSE(TEST_MAP_map->has("c"));
	EXPECT_FALSE(TEST_MAP_map->has("cde"));
}

/* Test removing a value from a map. */
TEST(Map, Remove) {
	TEST_MAP_map->remove("aa");
	
	EXPECT_FALSE(TEST_MAP_map->has("aa"));

	EXPECT_EQ(TEST_MAP_map->getKeys().getSize(), 2);
	EXPECT_EQ(TEST_MAP_map->getKeys()[0], "a");
	EXPECT_EQ(TEST_MAP_map->getKeys()[1], "bbbb");

	EXPECT_EQ(TEST_MAP_map->getValues().getSize(), 2);
	EXPECT_EQ(TEST_MAP_map->getValues()[0], 1);
	EXPECT_EQ(TEST_MAP_map->getValues()[1], 3);
}

/* Test getting a value from a map. */
TEST(Map, Get) {
	EXPECT_EQ(TEST_MAP_map->get("a"), 1);
	EXPECT_EQ(TEST_MAP_map->get("bbbb"), 3);
}

/* Test the subscript get. */
TEST(Map, SubscriptGet) {
	std::cout << &(*TEST_MAP_map)["a"] << " = " << &TEST_MAP_map->get("a") << std::endl;
	EXPECT_EQ((*TEST_MAP_map)["a"], 1);//TEST_MAP_map->get("a"));
	//EXPECT_EQ((*TEST_MAP_map)["bbbb"], 3);//TEST_MAP_map->get("bbbb"));
}

/* Test the subscript set. */
TEST(Map, SubscriptSet) {
	(*TEST_MAP_map)["a"] = 3;
	EXPECT_EQ(TEST_MAP_map->get("a"), 3);
}

/* Test the copy constructor of a map. */
TEST(Map, CopyConstructor) {
	StevensDev::sgdc::Map< int > map2(*TEST_MAP_map);
	EXPECT_EQ(TEST_MAP_countingMapAllocator->getAllocations(), 14);
	EXPECT_EQ(TEST_MAP_countingKeysAllocator->getAllocations(), 3 * DYNAMIC_ARRAY_DEFAULT_CAPACITY);
	EXPECT_EQ(TEST_MAP_countingValuesAllocator->getAllocations(), 3 * DYNAMIC_ARRAY_DEFAULT_CAPACITY);
	EXPECT_EQ(map2.get("a"), TEST_MAP_map->get("a"));
	EXPECT_EQ(map2.get("bbbb"), TEST_MAP_map->get("bbbb"));

	map2.put("a", 4);
	EXPECT_EQ(map2.get("a"), 4);
	EXPECT_NE(map2.get("a"), TEST_MAP_map->get("a"));
	EXPECT_EQ(map2.get("bbbb"), TEST_MAP_map->get("bbbb"));
}

/* Test the copy assignment operator of a map. */
TEST(Map, CopyAssignment) {
	StevensDev::sgdc::Map< int > map2;
	map2 = *TEST_MAP_map;
	EXPECT_EQ(TEST_MAP_countingMapAllocator->getAllocations(), 21);
	EXPECT_EQ(TEST_MAP_countingKeysAllocator->getAllocations(), 4 * DYNAMIC_ARRAY_DEFAULT_CAPACITY);
	EXPECT_EQ(TEST_MAP_countingValuesAllocator->getAllocations(), 4 * DYNAMIC_ARRAY_DEFAULT_CAPACITY);
	EXPECT_EQ(map2.get("a"), TEST_MAP_map->get("a"));
	EXPECT_EQ(map2.get("bbbb"), TEST_MAP_map->get("bbbb"));

	map2.put("a", 4);
	EXPECT_EQ(map2.get("a"), 4);
	EXPECT_NE(map2.get("a"), TEST_MAP_map->get("a"));
	EXPECT_EQ(map2.get("bbbb"), TEST_MAP_map->get("bbbb"));
}

/* Test the move constructor of a map. */
TEST(Map, MoveConstructor) {
	StevensDev::sgdc::Map< int > map2(*TEST_MAP_map);
	unsigned int prevMapAllocations = TEST_MAP_countingMapAllocator->getAllocations();
	unsigned int prevMapDeallocations = TEST_MAP_countingMapAllocator->getDeallocations();
	StevensDev::sgdc::Map< int > map3(std::move(map2));
	EXPECT_EQ(TEST_MAP_countingMapAllocator->getAllocations(), prevMapAllocations);
	EXPECT_EQ(TEST_MAP_countingMapAllocator->getDeallocations(), prevMapDeallocations);
}

/* Test the move assignment operator of a map. */
TEST(Map, MoveAssignment) {
	StevensDev::sgdc::Map< int > map2;
	unsigned int prevMapAllocations = TEST_MAP_countingMapAllocator->getAllocations();
	unsigned int prevMapDeallocations = TEST_MAP_countingMapAllocator->getDeallocations();
	StevensDev::sgdc::Map< int > map3 = std::move(map2);
	EXPECT_EQ(TEST_MAP_countingMapAllocator->getAllocations(), prevMapAllocations);
	EXPECT_EQ(TEST_MAP_countingMapAllocator->getDeallocations(), prevMapDeallocations);
}

/* Test oustanding allocations. */
TEST(Map, CleanUp) {
	delete TEST_MAP_map;
	EXPECT_EQ(TEST_MAP_countingMapAllocator->getOutstandingAllocations(), 0);
	EXPECT_EQ(TEST_MAP_countingKeysAllocator->getOutstandingAllocations(), 0);
	EXPECT_EQ(TEST_MAP_countingValuesAllocator->getOutstandingAllocations(), 0);
}