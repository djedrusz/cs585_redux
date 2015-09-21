/*
	Dominik Jedruszczak

	test_dynamic_array.cpp
	Tests for the "DynamicArray" class.
*/

#include "../src/engine/memory/counting_allocator.hpp"
#include "../src/engine/containers/dynamic_array.hpp"
#include "../gtest/include/gtest/gtest.h"

#define DYNAMIC_ARRAY_STARTING_CAPACITY 25

/* Globals. */
StevensDev::sgdm::CountingAllocator<int> TEST_DYNAMIC_ARRAY_countingAllocator; // Counting allocator.
StevensDev::sgdc::DynamicArray<int>* TEST_DYNAMIC_ARRAY_dynamicArray = new StevensDev::sgdc::DynamicArray<int>(&TEST_DYNAMIC_ARRAY_countingAllocator, DYNAMIC_ARRAY_STARTING_CAPACITY); // Dynamic array.

/* Test the constuction of a dynamic array. */
TEST(DynamicArray, Constructor) {
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_countingAllocator.getAllocations(), DYNAMIC_ARRAY_STARTING_CAPACITY);
}

/* Test getting the size of a dynamic array. */
TEST(DynamicArray, GetSize) {
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray->getSize(), 0);
}

/* Test prepending into an empty dynamic array. */
TEST(DynamicArray, PrependEmpty) {
	TEST_DYNAMIC_ARRAY_dynamicArray->prepend(2);
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray->getSize(), 1);
}

/* Test prepending into a non-empty dynamic array. */
TEST(DynamicArray, PrependNonEmpty) {
	TEST_DYNAMIC_ARRAY_dynamicArray->prepend(1);
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray->getSize(), 2);
}

/* Test pulling from a dynamic array. */
TEST(DynamicArray, Pull) {
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray->pull(), 1);
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray->getSize(), 1);
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray->pull(), 2);
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray->getSize(), 0);
}

/* Test shrinking a dynamic array. */
TEST(DynamicArray, Shrink) {
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_countingAllocator.getAllocations(), DYNAMIC_ARRAY_STARTING_CAPACITY + (unsigned int)(DYNAMIC_ARRAY_STARTING_CAPACITY * DYNAMIC_ARRAY_SHRINK_RATIO) + DYNAMIC_ARRAY_MINIMUM_CAPACITY);
}

/* Test appending onto an empty dynamic array. */
TEST(DynamicArray, AppendEmpty) {
	TEST_DYNAMIC_ARRAY_dynamicArray->append(1);
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray->getSize(), 1);
}

/* Test appending onto a non-empty dynamic array. */
TEST(DynamicArray, AppendNonEmpty) {
	TEST_DYNAMIC_ARRAY_dynamicArray->append(2);
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray->getSize(), 2);
}

/* Test pushing from a dynamic array. */
TEST(DynamicArray, Push) {
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray->push(), 2);
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray->getSize(), 1);
}

/* Test pushing the last element from a dynamic array. */
TEST(DynamicArray, PushLast) {
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray->push(), 1);
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray->getSize(), 0);
}

/* Test inserting into an empty dynamic array. */
TEST(DynamicArray, InsertEmpty) {
	TEST_DYNAMIC_ARRAY_dynamicArray->insert(0, 2);
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray->getSize(), 1);
}

/* Test inserting into the front of a dynamic array. */
TEST(DynamicArray, InsertFront) {
	TEST_DYNAMIC_ARRAY_dynamicArray->insert(0, 1);
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray->getSize(), 2);
}

/* Test inserting into the back of a dynamic array. */
TEST(DynamicArray, InsertBack) {
	TEST_DYNAMIC_ARRAY_dynamicArray->insert(2, 4);
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray->getSize(), 3);
}

/* Test inserting into the middle of a dynamic array. */
TEST(DynamicArray, InsertMiddle) {
	TEST_DYNAMIC_ARRAY_dynamicArray->insert(2, 3);
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray->getSize(), 4);
}

/* Test removing from the middle of a dynamic array. */
TEST(DynamicArray, RemoveMiddle) {
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray->remove(2), 3);
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray->getSize(), 3);
}

/* Test removing from the back of a dynamic array. */
TEST(DynamicArray, RemoveBack) {
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray->remove(2), 4);
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray->getSize(), 2);
}

/* Test removing from the front of a dynamic array. */
TEST(DynamicArray, RemoveFront) {
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray->remove(0), 1);
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray->getSize(), 1);
}

/* Test removing the last element from a dynamic array. */
TEST(DynamicArray, RemoveLast) {
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray->remove(0), 2);
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray->getSize(), 0);
}

/* Test setting an element of a dynamic array. */
TEST(DynamicArray, Set) {
	TEST_DYNAMIC_ARRAY_dynamicArray->prepend(1);
	TEST_DYNAMIC_ARRAY_dynamicArray->prepend(0);
	TEST_DYNAMIC_ARRAY_dynamicArray->set(1, 2);
	TEST_DYNAMIC_ARRAY_dynamicArray->set(0, 1);
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray->pull(), 1);
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray->pull(), 2);
}

/* Test getting the elements of a dynamic array. */
TEST(DynamicArray, Get) {
	TEST_DYNAMIC_ARRAY_dynamicArray->prepend(1);
	TEST_DYNAMIC_ARRAY_dynamicArray->prepend(0);
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray->get(0), 0);
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray->get(1), 1);
}

/* Test the copy assignment operator of a dynamic array. */
TEST(DynamicArray, CopyAssignmentOperator) {
	StevensDev::sgdc::DynamicArray<int> TEST_DYNAMIC_ARRAY_dynamicArray2;
	unsigned int currentAllocations = TEST_DYNAMIC_ARRAY_countingAllocator.getAllocations();
	TEST_DYNAMIC_ARRAY_dynamicArray2 = *TEST_DYNAMIC_ARRAY_dynamicArray;
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_countingAllocator.getAllocations(), currentAllocations + 10);
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray2.getSize(), 2);
	for (unsigned int i = 0; i < TEST_DYNAMIC_ARRAY_dynamicArray->getSize(); i++) {
		EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray->get(i), TEST_DYNAMIC_ARRAY_dynamicArray2.get(i));
	}
}

/* Test the growth of a dynamic array. */
TEST(DynamicArray, Grow) {
	StevensDev::sgdc::DynamicArray<int> TEST_DYNAMIC_ARRAY_dynamicArray2(&TEST_DYNAMIC_ARRAY_countingAllocator, DYNAMIC_ARRAY_STARTING_CAPACITY);
	unsigned int currentAllocations = TEST_DYNAMIC_ARRAY_countingAllocator.getAllocations();

	for (unsigned int i = 0; i < DYNAMIC_ARRAY_STARTING_CAPACITY + 1; i++) {
		TEST_DYNAMIC_ARRAY_dynamicArray2.append(42);
	}

	EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray2.getSize(), 26);
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_countingAllocator.getAllocations(), (unsigned int)(currentAllocations + DYNAMIC_ARRAY_STARTING_CAPACITY * DYNAMIC_ARRAY_GROW_RATIO));
}

/* Test the get subcript operator of a dynamic array. */
TEST(DynamicArray, SubscriptGet) {
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_dynamicArray->getSize(), 2);
	for (unsigned int i = 0; i < TEST_DYNAMIC_ARRAY_dynamicArray->getSize(); i++) {
		EXPECT_EQ((*TEST_DYNAMIC_ARRAY_dynamicArray)[0], TEST_DYNAMIC_ARRAY_dynamicArray->get(0));
	}
}

/* Test the set subscript operator of a dynamic array. */
TEST(DynamicArray, SubscriptSet) {
	StevensDev::sgdc::DynamicArray<int> tester;
	tester.append(2);
	tester[2] = 5;
	EXPECT_EQ(tester[2], 5);
}

/* Test the move constructor of a dynamic array. */
TEST(DynamicArray, MoveConstructor) {
	StevensDev::sgdc::DynamicArray< int > dynamicArray2;
	dynamicArray2.append(2);
	dynamicArray2.append(3);
	StevensDev::sgdc::DynamicArray< int >* dynamicArray3 = new StevensDev::sgdc::DynamicArray< int >(std::move(dynamicArray2));
	EXPECT_EQ(dynamicArray3->get(0), 2);
	EXPECT_EQ(dynamicArray3->get(1), 3);
}

/* Test the move assignment operator of a dynamic array. */
TEST(DynamicArray, MoveAssignmentOperator) {
	StevensDev::sgdc::DynamicArray< int > dynamicArray2;
	dynamicArray2.append(2);
	dynamicArray2.append(3);
	StevensDev::sgdc::DynamicArray< int > dynamicArray3;
	dynamicArray3 = std::move(dynamicArray2);
	EXPECT_EQ(dynamicArray3.get(0), 2);
	EXPECT_EQ(dynamicArray3.get(1), 3);
}

/* Test destructor. */
TEST(DynamicArray, Destructor) {
	delete TEST_DYNAMIC_ARRAY_dynamicArray;
	EXPECT_EQ(TEST_DYNAMIC_ARRAY_countingAllocator.getOutstandingAllocations(), 0);
}