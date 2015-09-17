/*
	Dominik Jedruszczak

	test_map.cpp
	Tests for the "Map" class.
*/

#include "../gtest/include/gtest/gtest.h"
#include "../src/engine/memory/counting_allocator.hpp"
#include "../src/engine/containers/map.hpp"

TEST(Map, General) {
	StevensDev::sgdm::CountingAllocator< StevensDev::sgdc::MapNode< int > >* countingAllocator = new StevensDev::sgdm::CountingAllocator< StevensDev::sgdc::MapNode< int > >();
	StevensDev::sgdc::Map<int>* map = new StevensDev::sgdc::Map<int>(countingAllocator);
	//map->add("a", 0);
	map->add("aa", 3);
	map->add("ab", 4);
	map->add("ac", 5);
	//map->add("b", 1);
	map->add("ba", 6);
	map->add("bb", 7);
	map->add("bc", 8);
	//map->add("c", 2);
	map->add("ca", 9);
	map->add("cb", 10);
	map->add("cc", 11);
	map->print();
	printf("%d", map->has("a"));
	printf("%d", map->has("aa"));
	printf("%d", map->has("ab"));
	printf("%d", map->has("ac"));
	printf("%d", map->has("b"));
	printf("%d", map->has("ba"));
	printf("%d", map->has("bb"));
	printf("%d", map->has("bc"));
	printf("%d", map->has("c"));
	printf("%d", map->has("ca"));
	printf("%d", map->has("cb"));
	printf("%d", map->has("cc"));
	printf("\n");
	printf("%d", map->has("e"));
	printf("\n");
	//const StevensDev::sgdc::DynamicArray< std::string > keys = map->getKeys();
	const StevensDev::sgdc::DynamicArray< int > values = map->getValues();
	for (unsigned int i = 0; i < values.getSize(); i++) {
		printf("%i", values[i]);
		//printf("%s = %i\n", keys[i].c_str(), values[i]);
	}
	printf("\n");
	delete map;
	printf("Total allocations = %u\n", countingAllocator->getTotalAllocations());
	printf("Total Outstanding allocations = %u\n", countingAllocator->getTotalOutstandingAllocations());
}