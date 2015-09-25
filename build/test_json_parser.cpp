/*
	Dominik Jedruszczak

	test_json_parser.cpp
	Tests for the "JsonParser" class.
*/

#include "../gtest/include/gtest/gtest.h"
#include "../src/engine/data/json_parser.hpp"

using namespace StevensDev;

TEST(JsonParser, General) {
	std::cout << "Wert" << std::endl;
	sgdd::JsonEntity* jsonEntity = sgdd::JsonParser::parse(" 	\
		\"string\"");
	if (jsonEntity != NULL) {
		std::cout << jsonEntity->getType() << std::endl;
	}
	EXPECT_EQ(1, 1);
}