/*
	Dominik Jedruszczak

	tests.cpp
	Run all tests.
*/

#include "../gtest/include/gtest/gtest.h"

/* Run all tests. */
int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}