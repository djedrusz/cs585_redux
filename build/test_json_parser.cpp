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
	sgdm::CountingAllocator< sgdd::JsonValue > countingAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(&countingAllocator, "true");

	EXPECT_EQ(jsonValue->isBool(), true);
	EXPECT_EQ(jsonValue->asBool(), true);

	countingAllocator.deallocate(jsonValue, 1);
	EXPECT_EQ(countingAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing false. */
TEST(JsonParser, False) {
	sgdm::CountingAllocator< sgdd::JsonValue > countingAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(&countingAllocator, "false");

	EXPECT_EQ(jsonValue->isBool(), true);
	EXPECT_EQ(jsonValue->asBool(), false);

	countingAllocator.deallocate(jsonValue, 1);
	EXPECT_EQ(countingAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test boolean whitespaces. */
TEST(JsonParser, BoolWhitespace) {
	sgdm::CountingAllocator< sgdd::JsonValue > countingAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(&countingAllocator, " 	\
		false 	\
		");

	EXPECT_EQ(jsonValue->isBool(), true);
	EXPECT_EQ(jsonValue->asBool(), false);

	countingAllocator.deallocate(jsonValue, 1);
	EXPECT_EQ(countingAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing true error. */
TEST(JsonParser, TrueError) {
	sgdm::CountingAllocator< sgdd::JsonValue > countingAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(&countingAllocator, "tlue");

	EXPECT_EQ(jsonValue->isError(), true);

	countingAllocator.deallocate(jsonValue, 1);
	EXPECT_EQ(countingAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing false error. */
TEST(JsonParser, FalseError) {
	sgdm::CountingAllocator< sgdd::JsonValue > countingAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(&countingAllocator, "falsf");

	EXPECT_EQ(jsonValue->isError(), true);

	countingAllocator.deallocate(jsonValue, 1);
	EXPECT_EQ(countingAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing zero. */
TEST(JsonParser, PositiveZero) {
	sgdm::CountingAllocator< sgdd::JsonValue > countingAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(&countingAllocator, "0");

	EXPECT_EQ(jsonValue->isInt(), true);
	EXPECT_EQ(jsonValue->asInt(), 0);

	countingAllocator.deallocate(jsonValue, 1);
	EXPECT_EQ(countingAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing negative zero. */
TEST(JsonParser, NegativeZero) {
	sgdm::CountingAllocator< sgdd::JsonValue > countingAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(&countingAllocator, "-0");

	EXPECT_EQ(jsonValue->isInt(), true);
	EXPECT_EQ(jsonValue->asInt(), 0);

	countingAllocator.deallocate(jsonValue, 1);
	EXPECT_EQ(countingAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing positive integer. */
TEST(JsonParser, PositiveInteger) {
	sgdm::CountingAllocator< sgdd::JsonValue > countingAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(&countingAllocator, "1234");

	EXPECT_EQ(jsonValue->isInt(), true);
	EXPECT_EQ(jsonValue->asInt(), 1234);

	countingAllocator.deallocate(jsonValue, 1);
	EXPECT_EQ(countingAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing negative integer. */
TEST(JsonParser, NegativeInteger) {
	sgdm::CountingAllocator< sgdd::JsonValue > countingAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(&countingAllocator, "-1234");

	EXPECT_EQ(jsonValue->isInt(), true);
	EXPECT_EQ(jsonValue->asInt(), -1234);

	countingAllocator.deallocate(jsonValue, 1);
	EXPECT_EQ(countingAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing positive double. */
TEST(JsonParser, PositiveDouble) {
	sgdm::CountingAllocator< sgdd::JsonValue > countingAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(&countingAllocator, "1234.1234");

	EXPECT_EQ(jsonValue->isDouble(), true);
	EXPECT_EQ(jsonValue->asDouble(), atof("1234.1234"));

	countingAllocator.deallocate(jsonValue, 1);
	EXPECT_EQ(countingAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing negative double. */
TEST(JsonParser, NegativeDouble) {
	sgdm::CountingAllocator< sgdd::JsonValue > countingAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(&countingAllocator, "-1234.1234");

	EXPECT_EQ(jsonValue->isDouble(), true);
	EXPECT_EQ(jsonValue->asDouble(), atof("-1234.1234"));

	countingAllocator.deallocate(jsonValue, 1);
	EXPECT_EQ(countingAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing positive exponential double. */
TEST(JsonParser, PositiveExponent) {
	sgdm::CountingAllocator< sgdd::JsonValue > countingAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(&countingAllocator, "1234.1234e56");

	EXPECT_EQ(jsonValue->isDouble(), true);
	EXPECT_EQ(jsonValue->asDouble(), atof("1234.1234e56"));

	countingAllocator.deallocate(jsonValue, 1);
	EXPECT_EQ(countingAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing negative exponential double. */
TEST(JsonParser, NegativeExponent) {
	sgdm::CountingAllocator< sgdd::JsonValue > countingAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(&countingAllocator, "1234.1234e-43");

	EXPECT_EQ(jsonValue->isDouble(), true);
	EXPECT_EQ(jsonValue->asDouble(), atof("1234.1234e-43"));

	countingAllocator.deallocate(jsonValue, 1);
	EXPECT_EQ(countingAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test number whitespaces. */
TEST(JsonParser, NumberWhitespaces) {
	sgdm::CountingAllocator< sgdd::JsonValue > countingAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(&countingAllocator, " 	\
		1234.1234e-43 	\
		");

	EXPECT_EQ(jsonValue->isDouble(), true);
	EXPECT_EQ(jsonValue->asDouble(), atof("1234.1234e-43"));

	countingAllocator.deallocate(jsonValue, 1);
	EXPECT_EQ(countingAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing number error invalid exponent format. */
TEST(JsonParser, NumberErrorInvalidExponent) {
	sgdm::CountingAllocator< sgdd::JsonValue > countingAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(&countingAllocator, "123.01ea");

	EXPECT_EQ(jsonValue->isError(), true);

	countingAllocator.deallocate(jsonValue, 1);
	EXPECT_EQ(countingAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing simple string. */
TEST(JsonParser, SimpleString) {
	sgdm::CountingAllocator< sgdd::JsonValue > countingAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(&countingAllocator, "\"string\"");

	EXPECT_EQ(jsonValue->isString(), true);
	EXPECT_EQ(jsonValue->asString().compare("string"), 0);

	countingAllocator.deallocate(jsonValue, 1);
	EXPECT_EQ(countingAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing string with escape characters. */
TEST(JsonParser, EscapeString) {
	sgdm::CountingAllocator< sgdd::JsonValue > countingAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(&countingAllocator, "\"s\\\"s\\\\s\\/s\\bs\\fs\\n\\rs\\ts\\u12344ss\"");

	EXPECT_EQ(jsonValue->isString(), true);
	EXPECT_EQ(jsonValue->asString().compare("s\\\"s\\\\s\\/s\\bs\\fs\\n\\rs\\ts\\u12344ss"), 0);

	countingAllocator.deallocate(jsonValue, 1);
	EXPECT_EQ(countingAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing string with whitespaces. */
TEST(JsonParser, StringWhitespaces) {
	sgdm::CountingAllocator< sgdd::JsonValue > countingAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(&countingAllocator, " 	\
		\"s\\\"s\\\\s\\/s\\bs\\fs\\n\\rs\\ts\\u12344ss\" 	\
		");

	EXPECT_EQ(jsonValue->isString(), true);
	EXPECT_EQ(jsonValue->asString().compare("s\\\"s\\\\s\\/s\\bs\\fs\\n\\rs\\ts\\u12344ss"), 0);

	countingAllocator.deallocate(jsonValue, 1);
	EXPECT_EQ(countingAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing string error invalid special character. */
TEST(JsonParser, StringErrorBadSpecial) {
	sgdm::CountingAllocator< sgdd::JsonValue > countingAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(&countingAllocator, "\"s\\\"s\\\\s\\/s\\zs\\fs\\n\\rs\\ts\\u12344ss\"");

	EXPECT_EQ(jsonValue->isError(), true);

	countingAllocator.deallocate(jsonValue, 1);
	EXPECT_EQ(countingAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing string error invalid hex. */
TEST(JsonParser, StringErrorBadHex) {
	sgdm::CountingAllocator< sgdd::JsonValue > countingAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(&countingAllocator, "\"s\\\"s\\\\s\\/s\\bs\\fs\\n\\rs\\ts\\u123z4ss\"");

	EXPECT_EQ(jsonValue->isError(), true);

	countingAllocator.deallocate(jsonValue, 1);
	EXPECT_EQ(countingAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing empty array. */
TEST(JsonParser, EmptyArray) {
	sgdm::CountingAllocator< std::string > stringAllocator;
	sgdm::CountingAllocator< sgdc::DynamicArray< sgdd::JsonValue > > dynamicArrayAllocator;
	sgdm::CountingAllocator< sgdc::Map< sgdd::JsonValue > > mapAllocator;
	sgdm::CountingAllocator< sgdd::JsonValue > jsonValueAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(
		&stringAllocator,
		&dynamicArrayAllocator,
		nullptr, &mapAllocator,
		&jsonValueAllocator,
		"[]");

	EXPECT_EQ(jsonValue->isArray(), true);
	EXPECT_EQ(jsonValue->asArray().getSize(), 0);

	jsonValueAllocator.deallocate(jsonValue, 1);

	EXPECT_EQ(stringAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(dynamicArrayAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(mapAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(jsonValueAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing array with one value. */
TEST(JsonParser, UnaryArray) {
	sgdm::CountingAllocator< std::string > stringAllocator;
	sgdm::CountingAllocator< sgdc::DynamicArray< sgdd::JsonValue > > dynamicArrayAllocator;
	sgdm::CountingAllocator< sgdc::Map< sgdd::JsonValue > > mapAllocator;
	sgdm::CountingAllocator< sgdd::JsonValue > jsonValueAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(
		&stringAllocator,
		&dynamicArrayAllocator,
		nullptr,
		&mapAllocator,
		&jsonValueAllocator,
		"[\"thirty\"]");

	EXPECT_EQ(jsonValue->isArray(), true);
	EXPECT_EQ(jsonValue->asArray().getSize(), 1);
	EXPECT_EQ(jsonValue->asArray()[0].isString(), true);
	EXPECT_EQ(jsonValue->asArray()[0].asString().compare("thirty"), 0);

	jsonValueAllocator.deallocate(jsonValue, 1);

	EXPECT_EQ(stringAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(dynamicArrayAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(mapAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(jsonValueAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing array with multiple values. */
TEST(JsonParser, MultipleArray) {
	sgdm::CountingAllocator< std::string > stringAllocator;
	sgdm::CountingAllocator< sgdc::DynamicArray< sgdd::JsonValue > > dynamicArrayAllocator;
	sgdm::CountingAllocator< sgdc::Map< sgdd::JsonValue > > mapAllocator;
	sgdm::CountingAllocator< sgdd::JsonValue > jsonValueAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(
		&stringAllocator,
		&dynamicArrayAllocator,
		nullptr,
		&mapAllocator,
		&jsonValueAllocator,
		"[true, false, 17, \"thirty\"]");

	EXPECT_EQ(jsonValue->isArray(), true);
	EXPECT_EQ(jsonValue->asArray().getSize(), 4);
	EXPECT_EQ(jsonValue->asArray()[0].isBool(), true);
	EXPECT_EQ(jsonValue->asArray()[0].asBool(), true);
	EXPECT_EQ(jsonValue->asArray()[1].isBool(), true);
	EXPECT_EQ(jsonValue->asArray()[1].asBool(), false);
	EXPECT_EQ(jsonValue->asArray()[2].isInt(), true);
	EXPECT_EQ(jsonValue->asArray()[2].asInt(), 17);
	EXPECT_EQ(jsonValue->asArray()[3].isString(), true);
	EXPECT_EQ(jsonValue->asArray()[3].asString().compare("thirty"), 0);

	jsonValueAllocator.deallocate(jsonValue, 1);

	EXPECT_EQ(stringAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(dynamicArrayAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(mapAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(jsonValueAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing array with whitespaces. */
TEST(JsonParser, ArrayWhitespaces) {
	sgdm::CountingAllocator< std::string > stringAllocator;
	sgdm::CountingAllocator< sgdc::DynamicArray< sgdd::JsonValue > > dynamicArrayAllocator;
	sgdm::CountingAllocator< sgdc::Map< sgdd::JsonValue > > mapAllocator;
	sgdm::CountingAllocator< sgdd::JsonValue > jsonValueAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(
		&stringAllocator,
		&dynamicArrayAllocator,
		nullptr,
		&mapAllocator,
		&jsonValueAllocator,
		" 	\
		[ 	\
			true 	\
			, 	\
			false 	\
			, 	\
			17 	\
			, 	\
			\"thirty\" 	\
			] 	\
		");

	EXPECT_EQ(jsonValue->isArray(), true);
	EXPECT_EQ(jsonValue->asArray().getSize(), 4);
	EXPECT_EQ(jsonValue->asArray()[0].isBool(), true);
	EXPECT_EQ(jsonValue->asArray()[0].asBool(), true);
	EXPECT_EQ(jsonValue->asArray()[1].isBool(), true);
	EXPECT_EQ(jsonValue->asArray()[1].asBool(), false);
	EXPECT_EQ(jsonValue->asArray()[2].isInt(), true);
	EXPECT_EQ(jsonValue->asArray()[2].asInt(), 17);
	EXPECT_EQ(jsonValue->asArray()[3].isString(), true);
	EXPECT_EQ(jsonValue->asArray()[3].asString().compare("thirty"), 0);

	jsonValueAllocator.deallocate(jsonValue, 1);

	EXPECT_EQ(stringAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(dynamicArrayAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(mapAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(jsonValueAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing array within an array. */
TEST(JsonParser, NestedArrays) {
	sgdm::CountingAllocator< std::string > stringAllocator;
	sgdm::CountingAllocator< sgdc::DynamicArray< sgdd::JsonValue > > dynamicArrayAllocator;
	sgdm::CountingAllocator< sgdc::Map< sgdd::JsonValue > > mapAllocator;
	sgdm::CountingAllocator< sgdd::JsonValue > jsonValueAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(
		&stringAllocator,
		&dynamicArrayAllocator,
		nullptr,
		&mapAllocator,
		&jsonValueAllocator,
		"[[]]");

	EXPECT_EQ(jsonValue->isArray(), true);
	EXPECT_EQ(jsonValue->asArray().getSize(), 1);
	EXPECT_EQ(jsonValue->asArray()[0].isArray(), true);
	EXPECT_EQ(jsonValue->asArray()[0].asArray().getSize(), 0);

	jsonValueAllocator.deallocate(jsonValue, 1);

	EXPECT_EQ(stringAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(dynamicArrayAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(mapAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(jsonValueAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing array with bad entity. */
TEST(JsonParser, ArrayErrorBadEntity) {
	sgdm::CountingAllocator< std::string > stringAllocator;
	sgdm::CountingAllocator< sgdc::DynamicArray< sgdd::JsonValue > > dynamicArrayAllocator;
	sgdm::CountingAllocator< sgdc::Map< sgdd::JsonValue > > mapAllocator;
	sgdm::CountingAllocator< sgdd::JsonValue > jsonValueAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(
		&stringAllocator,
		&dynamicArrayAllocator,
		nullptr,
		&mapAllocator,
		&jsonValueAllocator,
		"[true, falsej, 17, \"thirty\"]");

	EXPECT_EQ(jsonValue->isError(), true);

	jsonValueAllocator.deallocate(jsonValue, 1);

	EXPECT_EQ(stringAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(dynamicArrayAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(mapAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(jsonValueAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing empty object. */
TEST(JsonParser, EmptyObject) {
	sgdm::CountingAllocator< std::string > stringAllocator;
	sgdm::CountingAllocator< sgdc::DynamicArray< sgdd::JsonValue > > dynamicArrayAllocator;
	sgdm::CountingAllocator< sgdc::MapNode< sgdd::JsonValue > > mapNodeAllocator;
	sgdm::CountingAllocator< sgdc::Map< sgdd::JsonValue > > mapAllocator;
	sgdm::CountingAllocator< sgdd::JsonValue > jsonValueAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(
		&stringAllocator,
		&dynamicArrayAllocator,
		&mapNodeAllocator,
		&mapAllocator,
		&jsonValueAllocator,
		"{}");

	EXPECT_EQ(jsonValue->isObject(), true);
	EXPECT_EQ(jsonValue->asObject().getKeys().getSize(), 0);

	jsonValueAllocator.deallocate(jsonValue, 1);

	EXPECT_EQ(stringAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(dynamicArrayAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(mapNodeAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(mapAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(jsonValueAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing object with one pair. */
TEST(JsonParser, UnaryObject) {
	sgdm::CountingAllocator< std::string > stringAllocator;
	sgdm::CountingAllocator< sgdc::DynamicArray< sgdd::JsonValue > > dynamicArrayAllocator;
	sgdm::CountingAllocator< sgdc::MapNode< sgdd::JsonValue > > mapNodeAllocator;
	sgdm::CountingAllocator< sgdc::Map< sgdd::JsonValue > > mapAllocator;
	sgdm::CountingAllocator< sgdd::JsonValue > jsonValueAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(
		&stringAllocator,
		&dynamicArrayAllocator,
		&mapNodeAllocator,
		&mapAllocator,
		&jsonValueAllocator,
		"{\"please\":\"work\"}");
	   /*01-2345678-90-12345-6*/

	EXPECT_EQ(jsonValue->isObject(), true);
	EXPECT_EQ(jsonValue->asObject().has("please"), true);
	EXPECT_EQ(jsonValue->asObject().get("please").isString(), true);
	EXPECT_EQ(jsonValue->asObject().get("please").asString().compare("work"), 0);

	jsonValueAllocator.deallocate(jsonValue, 1);

	EXPECT_EQ(stringAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(dynamicArrayAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(mapNodeAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(mapAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(jsonValueAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing object with multiple pairs. */
TEST(JsonParser, MultipleObject) {
	sgdm::CountingAllocator< std::string > stringAllocator;
	sgdm::CountingAllocator< sgdc::DynamicArray< sgdd::JsonValue > > dynamicArrayAllocator;
	sgdm::CountingAllocator< sgdc::MapNode< sgdd::JsonValue > > mapNodeAllocator;
	sgdm::CountingAllocator< sgdc::Map< sgdd::JsonValue > > mapAllocator;
	sgdm::CountingAllocator< sgdd::JsonValue > jsonValueAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(
		&stringAllocator,
		&dynamicArrayAllocator,
		&mapNodeAllocator,
		&mapAllocator,
		&jsonValueAllocator,
		"{\"a\":\"yes\",\"b\":true,\"c\":2,\"d\":3.12}");
	   /*01-23-45-6789-01-23-4567890-12-3456-78-90123*/
	   /*0             1           2             3   */

	EXPECT_EQ(jsonValue->isObject(), true);
	EXPECT_EQ(jsonValue->asObject().getKeys().getSize(), 4);
	EXPECT_EQ(jsonValue->asObject().has("a"), true);
	EXPECT_EQ(jsonValue->asObject().get("a").isString(), true);
	EXPECT_EQ(jsonValue->asObject().get("a").asString().compare("yes"), 0);
	EXPECT_EQ(jsonValue->asObject().has("b"), true);
	EXPECT_EQ(jsonValue->asObject().get("b").isBool(), true);
	EXPECT_EQ(jsonValue->asObject().get("b").asBool(), true);
	EXPECT_EQ(jsonValue->asObject().has("c"), true);
	EXPECT_EQ(jsonValue->asObject().get("c").isInt(), true);
	EXPECT_EQ(jsonValue->asObject().get("c").asInt(), 2);
	EXPECT_EQ(jsonValue->asObject().has("d"), true);
	EXPECT_EQ(jsonValue->asObject().get("d").isDouble(), true);
	EXPECT_EQ(jsonValue->asObject().get("d").asDouble(), 3.12);

	jsonValueAllocator.deallocate(jsonValue, 1);

	EXPECT_EQ(stringAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(dynamicArrayAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(mapNodeAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(mapAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(jsonValueAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing object within an object. */
TEST(JsonParser, NestedObject) {
	sgdm::CountingAllocator< std::string > stringAllocator;
	sgdm::CountingAllocator< sgdc::DynamicArray< sgdd::JsonValue > > dynamicArrayAllocator;
	sgdm::CountingAllocator< sgdc::MapNode< sgdd::JsonValue > > mapNodeAllocator;
	sgdm::CountingAllocator< sgdc::Map< sgdd::JsonValue > > mapAllocator;
	sgdm::CountingAllocator< sgdd::JsonValue > jsonValueAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(
		&stringAllocator,
		&dynamicArrayAllocator,
		&mapNodeAllocator,
		&mapAllocator,
		&jsonValueAllocator,
		"{\"a\":{\"b\":\"huzzah\"}}");
	   /*01-23-45-6789-01-23-4567890-12-3456-78-90123*/
	   /*0             1           2             3   */

	EXPECT_EQ(jsonValue->isObject(), true);
	EXPECT_EQ(jsonValue->asObject().getKeys().getSize(), 1);
	EXPECT_EQ(jsonValue->asObject().has("a"), true);
	EXPECT_EQ(jsonValue->asObject().get("a").isObject(), true);
	EXPECT_EQ(jsonValue->asObject().get("a").asObject().getKeys().getSize(), 1);
	EXPECT_EQ(jsonValue->asObject().get("a").asObject().has("b"), true);
	EXPECT_EQ(jsonValue->asObject().get("a").asObject().get("b").isString(), true);
	EXPECT_EQ(jsonValue->asObject().get("a").asObject().get("b").asString().compare("huzzah"), 0);


	jsonValueAllocator.deallocate(jsonValue, 1);

	EXPECT_EQ(stringAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(dynamicArrayAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(mapNodeAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(mapAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(jsonValueAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing object with whitespaces. */
TEST(JsonParser, ObjectWhitespaces) {
	sgdm::CountingAllocator< std::string > stringAllocator;
	sgdm::CountingAllocator< sgdc::DynamicArray< sgdd::JsonValue > > dynamicArrayAllocator;
	sgdm::CountingAllocator< sgdc::MapNode< sgdd::JsonValue > > mapNodeAllocator;
	sgdm::CountingAllocator< sgdc::Map< sgdd::JsonValue > > mapAllocator;
	sgdm::CountingAllocator< sgdd::JsonValue > jsonValueAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(
		&stringAllocator,
		&dynamicArrayAllocator,
		&mapNodeAllocator,
		&mapAllocator,
		&jsonValueAllocator,
		" 	\
		{ 	\
			\"a\" 	\
			: 	\
			\"yes\" 	\
			, 	\
			\"b\" 	\
			: 	\
			true, 	\
			\"c\" 	\
			: 	\
			2 	\
			, 	\
			\"d\" 	\
			: 	\
			3.12 	\
			} 	\
			");
	   /*01-23-45-6789-01-23-4567890-12-3456-78-90123*/
	   /*0             1           2             3   */

	EXPECT_EQ(jsonValue->isObject(), true);
	EXPECT_EQ(jsonValue->asObject().getKeys().getSize(), 4);
	EXPECT_EQ(jsonValue->asObject().has("a"), true);
	EXPECT_EQ(jsonValue->asObject().get("a").isString(), true);
	EXPECT_EQ(jsonValue->asObject().get("a").asString().compare("yes"), 0);
	EXPECT_EQ(jsonValue->asObject().has("b"), true);
	EXPECT_EQ(jsonValue->asObject().get("b").isBool(), true);
	EXPECT_EQ(jsonValue->asObject().get("b").asBool(), true);
	EXPECT_EQ(jsonValue->asObject().has("c"), true);
	EXPECT_EQ(jsonValue->asObject().get("c").isInt(), true);
	EXPECT_EQ(jsonValue->asObject().get("c").asInt(), 2);
	EXPECT_EQ(jsonValue->asObject().has("d"), true);
	EXPECT_EQ(jsonValue->asObject().get("d").isDouble(), true);
	EXPECT_EQ(jsonValue->asObject().get("d").asDouble(), 3.12);

	jsonValueAllocator.deallocate(jsonValue, 1);

	EXPECT_EQ(stringAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(dynamicArrayAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(mapNodeAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(mapAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(jsonValueAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing object invalid entity. */
TEST(JsonParser, ObjectErrorBadEntity) {
	sgdm::CountingAllocator< std::string > stringAllocator;
	sgdm::CountingAllocator< sgdc::DynamicArray< sgdd::JsonValue > > dynamicArrayAllocator;
	sgdm::CountingAllocator< sgdc::MapNode< sgdd::JsonValue > > mapNodeAllocator;
	sgdm::CountingAllocator< sgdc::Map< sgdd::JsonValue > > mapAllocator;
	sgdm::CountingAllocator< sgdd::JsonValue > jsonValueAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(
		&stringAllocator,
		&dynamicArrayAllocator,
		&mapNodeAllocator,
		&mapAllocator,
		&jsonValueAllocator,
		"{\"a\":\"yes\",\"b\":trsue,\"c\":2,\"d\":3.12}");
	   /*01-23-45-6789-01-23-4567890-12-3456-78-90123*/
	   /*0             1           2             3   */

	EXPECT_EQ(jsonValue->isError(), true);

	jsonValueAllocator.deallocate(jsonValue, 1);

	EXPECT_EQ(stringAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(dynamicArrayAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(mapNodeAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(mapAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(jsonValueAllocator.getTotalOutstandingAllocations(), 0);
}

/* Test parsing object no colon. */
TEST(JsonParser, ObjectErrorNoColon) {
	sgdm::CountingAllocator< std::string > stringAllocator;
	sgdm::CountingAllocator< sgdc::DynamicArray< sgdd::JsonValue > > dynamicArrayAllocator;
	sgdm::CountingAllocator< sgdc::MapNode< sgdd::JsonValue > > mapNodeAllocator;
	sgdm::CountingAllocator< sgdc::Map< sgdd::JsonValue > > mapAllocator;
	sgdm::CountingAllocator< sgdd::JsonValue > jsonValueAllocator;
	sgdd::JsonValue* jsonValue = sgdd::JsonParser::parse(
		&stringAllocator,
		&dynamicArrayAllocator,
		&mapNodeAllocator,
		&mapAllocator,
		&jsonValueAllocator,
		"{\"a\"\"yes\",\"b\":trsue,\"c\":2,\"d\":3.12}");
	   /*01-23-45-6789-01-23-4567890-12-3456-78-90123*/
	   /*0             1           2             3   */

	EXPECT_EQ(jsonValue->isError(), true);

	jsonValueAllocator.deallocate(jsonValue, 1);

	EXPECT_EQ(stringAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(dynamicArrayAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(mapNodeAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(mapAllocator.getTotalOutstandingAllocations(), 0);
	EXPECT_EQ(jsonValueAllocator.getTotalOutstandingAllocations(), 0);
}