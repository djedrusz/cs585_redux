/*
	Dominik Jedruszczak

	test_json_parser.cpp
	Tests for the "JsonParser" class.
*/

#include "../gtest/include/gtest/gtest.h"
#include "../src/engine/memory/counting_allocator.hpp"
#include "../src/engine/data/json_parser.hpp"

using namespace StevensDev;

/* Test parsing true. */
TEST(JsonParser, True) {
	sgdm::CountingAllocator< sgdd::JsonEntity > countingAllocator;
	sgdd::JsonEntity* jsonEntity = sgdd::JsonParser::parse(&countingAllocator, "true");

	EXPECT_EQ(jsonEntity->isBool(), true);
	EXPECT_EQ(jsonEntity->asBool(), true);

	countingAllocator.deallocate(jsonEntity, 1);
	EXPECT_EQ(countingAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing false. */
TEST(JsonParser, False) {
	sgdm::CountingAllocator< sgdd::JsonEntity > countingAllocator;
	sgdd::JsonEntity* jsonEntity = sgdd::JsonParser::parse(&countingAllocator, "false");

	EXPECT_EQ(jsonEntity->isBool(), true);
	EXPECT_EQ(jsonEntity->asBool(), false);

	countingAllocator.deallocate(jsonEntity, 1);
	EXPECT_EQ(countingAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing zero. */
TEST(JsonParser, PositiveZero) {
	sgdm::CountingAllocator< sgdd::JsonEntity > countingAllocator;
	sgdd::JsonEntity* jsonEntity = sgdd::JsonParser::parse(&countingAllocator, "0");

	EXPECT_EQ(jsonEntity->isInt(), true);
	EXPECT_EQ(jsonEntity->asInt(), 0);

	countingAllocator.deallocate(jsonEntity, 1);
	EXPECT_EQ(countingAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing negative zero. */
TEST(JsonParser, NegativeZero) {
	sgdm::CountingAllocator< sgdd::JsonEntity > countingAllocator;
	sgdd::JsonEntity* jsonEntity = sgdd::JsonParser::parse(&countingAllocator, "-0");

	EXPECT_EQ(jsonEntity->isInt(), true);
	EXPECT_EQ(jsonEntity->asInt(), 0);

	countingAllocator.deallocate(jsonEntity, 1);
	EXPECT_EQ(countingAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing positive integer. */
TEST(JsonParser, PositiveInteger) {
	sgdm::CountingAllocator< sgdd::JsonEntity > countingAllocator;
	sgdd::JsonEntity* jsonEntity = sgdd::JsonParser::parse(&countingAllocator, "1234");

	EXPECT_EQ(jsonEntity->isInt(), true);
	EXPECT_EQ(jsonEntity->asInt(), 1234);

	countingAllocator.deallocate(jsonEntity, 1);
	EXPECT_EQ(countingAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing negative integer. */
TEST(JsonParser, NegativeInteger) {
	sgdm::CountingAllocator< sgdd::JsonEntity > countingAllocator;
	sgdd::JsonEntity* jsonEntity = sgdd::JsonParser::parse(&countingAllocator, "-1234");

	EXPECT_EQ(jsonEntity->isInt(), true);
	EXPECT_EQ(jsonEntity->asInt(), -1234);

	countingAllocator.deallocate(jsonEntity, 1);
	EXPECT_EQ(countingAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing positive double. */
TEST(JsonParser, PositiveDouble) {
	sgdm::CountingAllocator< sgdd::JsonEntity > countingAllocator;
	sgdd::JsonEntity* jsonEntity = sgdd::JsonParser::parse(&countingAllocator, "1234.1234");

	EXPECT_EQ(jsonEntity->isDouble(), true);
	EXPECT_EQ(jsonEntity->asDouble(), atof("1234.1234"));

	countingAllocator.deallocate(jsonEntity, 1);
	EXPECT_EQ(countingAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing negative double. */
TEST(JsonParser, NegativeDouble) {
	sgdm::CountingAllocator< sgdd::JsonEntity > countingAllocator;
	sgdd::JsonEntity* jsonEntity = sgdd::JsonParser::parse(&countingAllocator, "-1234.1234");

	EXPECT_EQ(jsonEntity->isDouble(), true);
	EXPECT_EQ(jsonEntity->asDouble(), atof("-1234.1234"));

	countingAllocator.deallocate(jsonEntity, 1);
	EXPECT_EQ(countingAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing positive exponential double. */
TEST(JsonParser, PositiveExponent) {
	sgdm::CountingAllocator< sgdd::JsonEntity > countingAllocator;
	sgdd::JsonEntity* jsonEntity = sgdd::JsonParser::parse(&countingAllocator, "1234.1234e56");

	EXPECT_EQ(jsonEntity->isDouble(), true);
	EXPECT_EQ(jsonEntity->asDouble(), atof("1234.1234e56"));

	countingAllocator.deallocate(jsonEntity, 1);
	EXPECT_EQ(countingAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing negative exponential double. */
TEST(JsonParser, NegativeExponent) {
	sgdm::CountingAllocator< sgdd::JsonEntity > countingAllocator;
	sgdd::JsonEntity* jsonEntity = sgdd::JsonParser::parse(&countingAllocator, "1234.1234e-43");

	EXPECT_EQ(jsonEntity->isDouble(), true);
	EXPECT_EQ(jsonEntity->asDouble(), atof("1234.1234e-43"));

	countingAllocator.deallocate(jsonEntity, 1);
	EXPECT_EQ(countingAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing simple string. */
TEST(JsonParser, SimpleString) {
	sgdm::CountingAllocator< sgdd::JsonEntity > countingAllocator;
	sgdd::JsonEntity* jsonEntity = sgdd::JsonParser::parse(&countingAllocator, "\"string\"");

	EXPECT_EQ(jsonEntity->isString(), true);
	EXPECT_EQ(jsonEntity->asString().compare("string"), 0);

	countingAllocator.deallocate(jsonEntity, 1);
	EXPECT_EQ(countingAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing string with escape characters. */
TEST(JsonParser, EscapeString) {
	sgdm::CountingAllocator< sgdd::JsonEntity > countingAllocator;
	sgdd::JsonEntity* jsonEntity = sgdd::JsonParser::parse(&countingAllocator, "\"s\\\"s\\\\s\\/s\\bs\\fs\\n\\rs\\ts\\u12344ss\"");

	EXPECT_EQ(jsonEntity->isString(), true);
	EXPECT_EQ(jsonEntity->asString().compare("s\\\"s\\\\s\\/s\\bs\\fs\\n\\rs\\ts\\u12344ss"), 0);

	countingAllocator.deallocate(jsonEntity, 1);
	EXPECT_EQ(countingAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing empty array. */
TEST(JsonParser, EmptyArray) {
	sgdm::CountingAllocator< std::string > stringAllocator;
	sgdm::CountingAllocator< sgdc::DynamicArray< sgdd::JsonEntity > > dynamicArrayAllocator;
	sgdm::CountingAllocator< sgdc::Map< sgdd::JsonEntity > > mapAllocator;
	sgdm::CountingAllocator< sgdd::JsonEntity > jsonEntityAllocator;
	sgdd::JsonEntity* jsonEntity = sgdd::JsonParser::parse(&stringAllocator, &dynamicArrayAllocator, nullptr, &mapAllocator, &jsonEntityAllocator, "[]");

	EXPECT_EQ(jsonEntity->isArray(), true);
	EXPECT_EQ(jsonEntity->asArray().getSize(), 0);

	jsonEntityAllocator.deallocate(jsonEntity, 1);

	EXPECT_EQ(stringAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(dynamicArrayAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(mapAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(jsonEntityAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing array with one value. */
TEST(JsonParser, UnaryArray) {
	sgdm::CountingAllocator< std::string > stringAllocator;
	sgdm::CountingAllocator< sgdc::DynamicArray< sgdd::JsonEntity > > dynamicArrayAllocator;
	sgdm::CountingAllocator< sgdc::Map< sgdd::JsonEntity > > mapAllocator;
	sgdm::CountingAllocator< sgdd::JsonEntity > jsonEntityAllocator;
	sgdd::JsonEntity* jsonEntity = sgdd::JsonParser::parse(&stringAllocator, &dynamicArrayAllocator, nullptr, &mapAllocator, &jsonEntityAllocator, "[\"thirty\"]");

	EXPECT_EQ(jsonEntity->isArray(), true);
	EXPECT_EQ(jsonEntity->asArray().getSize(), 1);
	EXPECT_EQ(jsonEntity->asArray()[0].isString(), true);
	std::cout << jsonEntity->asArray()[0].asString() << std::endl;
	EXPECT_EQ(jsonEntity->asArray()[0].asString().compare("thirty"), 0);

	jsonEntityAllocator.deallocate(jsonEntity, 1);

	EXPECT_EQ(stringAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(dynamicArrayAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(mapAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(jsonEntityAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing array with multiple values. */
TEST(JsonParser, MultipleArray) {
	sgdm::CountingAllocator< std::string > stringAllocator;
	sgdm::CountingAllocator< sgdc::DynamicArray< sgdd::JsonEntity > > dynamicArrayAllocator;
	sgdm::CountingAllocator< sgdc::Map< sgdd::JsonEntity > > mapAllocator;
	sgdm::CountingAllocator< sgdd::JsonEntity > jsonEntityAllocator;
	sgdd::JsonEntity* jsonEntity = sgdd::JsonParser::parse(&stringAllocator, &dynamicArrayAllocator, nullptr, &mapAllocator, &jsonEntityAllocator, "[true, false, 17, \"thirty\"]");

	EXPECT_EQ(jsonEntity->isArray(), true);
	EXPECT_EQ(jsonEntity->asArray().getSize(), 4);
	EXPECT_EQ(jsonEntity->asArray()[0].isBool(), true);
	EXPECT_EQ(jsonEntity->asArray()[0].asBool(), true);
	EXPECT_EQ(jsonEntity->asArray()[1].isBool(), true);
	EXPECT_EQ(jsonEntity->asArray()[1].asBool(), false);
	EXPECT_EQ(jsonEntity->asArray()[2].isInt(), true);
	EXPECT_EQ(jsonEntity->asArray()[2].asInt(), 17);
	EXPECT_EQ(jsonEntity->asArray()[3].isString(), true);
	EXPECT_EQ(jsonEntity->asArray()[3].asString().compare("thirty"), 0);

	jsonEntityAllocator.deallocate(jsonEntity, 1);

	EXPECT_EQ(stringAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(dynamicArrayAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(mapAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(jsonEntityAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing array within an array. */
TEST(JsonParser, NestedArrays) {
	sgdm::CountingAllocator< std::string > stringAllocator;
	sgdm::CountingAllocator< sgdc::DynamicArray< sgdd::JsonEntity > > dynamicArrayAllocator;
	sgdm::CountingAllocator< sgdc::Map< sgdd::JsonEntity > > mapAllocator;
	sgdm::CountingAllocator< sgdd::JsonEntity > jsonEntityAllocator;
	sgdd::JsonEntity* jsonEntity = sgdd::JsonParser::parse(&stringAllocator, &dynamicArrayAllocator, nullptr, &mapAllocator, &jsonEntityAllocator, "[[]]");

	EXPECT_EQ(jsonEntity->isArray(), true);
	EXPECT_EQ(jsonEntity->asArray().getSize(), 1);
	EXPECT_EQ(jsonEntity->asArray()[0].isArray(), true);
	EXPECT_EQ(jsonEntity->asArray()[0].asArray().getSize(), 0);

	jsonEntityAllocator.deallocate(jsonEntity, 1);

	EXPECT_EQ(stringAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(dynamicArrayAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(mapAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(jsonEntityAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing empty object. */
TEST(JsonParser, EmptyObject) {
	sgdm::CountingAllocator< std::string > stringAllocator;
	sgdm::CountingAllocator< sgdc::DynamicArray< sgdd::JsonEntity > > dynamicArrayAllocator;
	sgdm::CountingAllocator< sgdc::MapNode< sgdd::JsonEntity > > mapNodeAllocator;
	sgdm::CountingAllocator< sgdc::Map< sgdd::JsonEntity > > mapAllocator;
	sgdm::CountingAllocator< sgdd::JsonEntity > jsonEntityAllocator;
	sgdd::JsonEntity* jsonEntity = sgdd::JsonParser::parse(&stringAllocator, &dynamicArrayAllocator, &mapNodeAllocator, &mapAllocator, &jsonEntityAllocator, "{}");

	jsonEntityAllocator.deallocate(jsonEntity, 1);

	EXPECT_EQ(stringAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(dynamicArrayAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(mapNodeAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(mapAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(jsonEntityAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing object with one pair. */
TEST(JsonParser, UnaryObject) {
	sgdm::CountingAllocator< std::string > stringAllocator;
	sgdm::CountingAllocator< sgdc::DynamicArray< sgdd::JsonEntity > > dynamicArrayAllocator;
	sgdm::CountingAllocator< sgdc::MapNode< sgdd::JsonEntity > > mapNodeAllocator;
	sgdm::CountingAllocator< sgdc::Map< sgdd::JsonEntity > > mapAllocator;
	sgdm::CountingAllocator< sgdd::JsonEntity > jsonEntityAllocator;
	sgdd::JsonEntity* jsonEntity = sgdd::JsonParser::parse(&stringAllocator, &dynamicArrayAllocator, &mapNodeAllocator, &mapAllocator, &jsonEntityAllocator, "{\"please\":\"work\"}");

	jsonEntityAllocator.deallocate(jsonEntity, 1);

	EXPECT_EQ(stringAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(dynamicArrayAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(mapNodeAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(mapAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(jsonEntityAllocator.getTotalOutstandingAllocations(), 0);
}

/*TEST(JsonParser, General) {
	std::cout << "Wert" << std::endl;
	sgdd::JsonEntity* jsonEntity;

	std::cout << jsonEntity->getType() << std::endl;
	jsonEntity = sgdd::JsonParser::parse(" 	\
		\"string\"");


	jsonEntity = sgdd::JsonParser::parse("-1234.567e-89");
	double halp = jsonEntity->asDouble();
	double halp2 = atof("-1234.567e-89");
	std::cout << halp << std::endl;
	std::cout << halp2 << std::endl;
	std::cout << jsonEntity->getType() << std::endl;
	EXPECT_EQ(1, 1);
}*/