/*
	Dominik Jedruszczak

	test_default_allocator.cpp
	Tests for the "DefaultAllocator" class.
*/

#include "../gtest/include/gtest/gtest.h"
#include "../src/engine/memory/default_allocator.hpp"

/* Test allocation of a default allocator. */
TEST(DefaultAllocator, Allocation) {
	StevensDev::sgdm DefaultAllocator<int> defaultAllocator;
	int* memoryBlock = defaultAllocator.allocate(10);
	EXPECT_EQ(memoryBlock, !NULL);
	defaultAllocator.deallocate(memoryBlock, 10);
}