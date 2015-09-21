/*
	Dominik Jedruszczak

	test_counting_allocator.cpp
	Tests for the "CountingAllocator" class.
*/

#include "../gtest/include/gtest/gtest.h"
#include "../src/engine/memory/counting_allocator.hpp"

/* Globals. */
/* Counting allocators. */
StevensDev::sgdm::CountingAllocator<int> TEST_COUNTING_ALLOCATOR_countingAllocator;
StevensDev::sgdm::CountingAllocator<int> TEST_COUNTING_ALLOCATOR_countingAllocator2;

/* Memory blocks. */
int* TEST_COUNTING_ALLOCATOR_memoryBlock;
int* TEST_COUNTING_ALLOCATOR_memoryBlock2;

/* Test the constructor of a counting allocator. */
TEST(CountingAllocator, Constructor) {
	EXPECT_EQ(TEST_COUNTING_ALLOCATOR_countingAllocator.getAllocations(), 0);
	EXPECT_EQ(TEST_COUNTING_ALLOCATOR_countingAllocator.getDeallocations(), 0);
	EXPECT_EQ(TEST_COUNTING_ALLOCATOR_countingAllocator.getOutstandingAllocations(), 0);

	EXPECT_EQ(TEST_COUNTING_ALLOCATOR_countingAllocator2.getAllocations(), 0);
	EXPECT_EQ(TEST_COUNTING_ALLOCATOR_countingAllocator2.getDeallocations(), 0);
	EXPECT_EQ(TEST_COUNTING_ALLOCATOR_countingAllocator2.getOutstandingAllocations(), 0);
}

/* Test the allocation of a counting allocator. */
TEST(CountingAllocator, Allocate) {
	TEST_COUNTING_ALLOCATOR_memoryBlock = TEST_COUNTING_ALLOCATOR_countingAllocator.allocate(10);
	TEST_COUNTING_ALLOCATOR_memoryBlock2 = TEST_COUNTING_ALLOCATOR_countingAllocator2.allocate(15);

	EXPECT_EQ(TEST_COUNTING_ALLOCATOR_countingAllocator.getAllocations(), 10);
	EXPECT_EQ(TEST_COUNTING_ALLOCATOR_countingAllocator.getOutstandingAllocations(), 10);

	EXPECT_EQ(TEST_COUNTING_ALLOCATOR_countingAllocator2.getAllocations(), 15);
	EXPECT_EQ(TEST_COUNTING_ALLOCATOR_countingAllocator2.getOutstandingAllocations(), 15);
}

/* Test the copy constructor of a counting allocator. */
TEST(CountingAllocator, CopyConstructor) {
	StevensDev::sgdm::CountingAllocator<int> TEST_COUNTING_ALLOCATOR_countingAllocator3(TEST_COUNTING_ALLOCATOR_countingAllocator);

	EXPECT_EQ(TEST_COUNTING_ALLOCATOR_countingAllocator3.getAllocations(), 10);
	EXPECT_EQ(TEST_COUNTING_ALLOCATOR_countingAllocator3.getDeallocations(), 0);
}

/* Test the move constructor of a counting allocator. */
TEST(CountingAllocator, MoveConstructor) {
	StevensDev::sgdm::CountingAllocator<int> TEST_COUNTING_ALLOCATOR_countingAllocator3(TEST_COUNTING_ALLOCATOR_countingAllocator2);

	EXPECT_EQ(TEST_COUNTING_ALLOCATOR_countingAllocator3.getAllocations(), 15);
	EXPECT_EQ(TEST_COUNTING_ALLOCATOR_countingAllocator3.getDeallocations(), 0);
}

/* Test the deallocation of a counting allocator. */
TEST(CountingAllocator, Deallocate) {
	TEST_COUNTING_ALLOCATOR_countingAllocator.deallocate(TEST_COUNTING_ALLOCATOR_memoryBlock, 10);
	TEST_COUNTING_ALLOCATOR_countingAllocator2.deallocate(TEST_COUNTING_ALLOCATOR_memoryBlock2, 15);

	EXPECT_EQ(TEST_COUNTING_ALLOCATOR_countingAllocator.getDeallocations(), 10);
	EXPECT_EQ(TEST_COUNTING_ALLOCATOR_countingAllocator.getOutstandingAllocations(), 0);

	EXPECT_EQ(TEST_COUNTING_ALLOCATOR_countingAllocator2.getDeallocations(), 15);
	EXPECT_EQ(TEST_COUNTING_ALLOCATOR_countingAllocator2.getOutstandingAllocations(), 0);
}