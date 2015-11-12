/*
	Dominik Jedruszczak

	Tests for the "SmartMap" class.
*/

#include "../gtest/include/gtest/gtest.h"
#include "../src/engine/containers/smart_map.hpp"

using namespace StevensDev::sgdc;

TEST(SmartMap, PutRootGet) {
	SmartMap< int > smartMap;

	smartMap.put("a", 1);

	EXPECT_EQ(smartMap.get("a"), 1);
}

TEST(SmartMap, PutRootIndirect) {
	SmartMap< int > smartMap;

	smartMap.put("ab", 2);

	EXPECT_EQ(smartMap.get("ab"), 2);
}

TEST(SmartMap, PutExistingNodeDirect) {
	SmartMap< int > smartMap;

	smartMap.put("a", 1);
	smartMap.put("ab", 2);

	EXPECT_EQ(smartMap.get("ab"), 2);
}

TEST(SmartMap, PutExistingNodeIndirect) {
	SmartMap< int > smartMap;

	smartMap.put("a", 1);
	smartMap.put("abb", 2);

	EXPECT_EQ(smartMap.get("abb"), 2);
}