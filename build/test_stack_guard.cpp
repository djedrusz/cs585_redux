/*
	Dominik Jedruszczak

	test_stack_guard.cpp
	Tests for the "StackGuard" class.
*/

#include "../gtest/include/gtest/gtest.h"
#include "../src/engine/memory/counting_allocator.hpp"
#include "../src/engine/memory/stack_guard.hpp"
#include "../src/engine/containers/dynamic_array.hpp"

using namespace StevensDev;

/* Globals. */
sgdm::CountingAllocator< sgdc::DynamicArray< int > >* TEST_STACK_GUARD_countingAllocator = new sgdm::CountingAllocator< sgdc::DynamicArray< int > >();

/* Test the constructor of a stack guard. */
TEST(StackGuard, Constructor) {
	sgdc::DynamicArray< int >* dynamicArray = TEST_STACK_GUARD_countingAllocator->allocate(1);
	TEST_STACK_GUARD_countingAllocator->construct(dynamicArray, sgdc::DynamicArray< int >());
	sgdm::StackGuard< sgdc::DynamicArray< int > > stackGuard(TEST_STACK_GUARD_countingAllocator, dynamicArray);

	EXPECT_EQ(TEST_STACK_GUARD_countingAllocator->getAllocations(), 1);
	EXPECT_EQ(stackGuard.getGuarded(), dynamicArray);
}

/* Test the destructor of a stack guard. */
TEST(StackGuard, Destructor) {
	EXPECT_EQ(TEST_STACK_GUARD_countingAllocator->getDeallocations(), 1);
}

/* Test the move constructor of a stack guard. */
TEST(StackGuard, MoveConstructor) {
	sgdc::DynamicArray< int >* dynamicArray = TEST_STACK_GUARD_countingAllocator->allocate(1);
	TEST_STACK_GUARD_countingAllocator->construct(dynamicArray, sgdc::DynamicArray< int >());
	sgdm::StackGuard< sgdc::DynamicArray< int > >* stackGuard = new sgdm::StackGuard< sgdc::DynamicArray< int > >(TEST_STACK_GUARD_countingAllocator, dynamicArray);
	sgdm::StackGuard< sgdc::DynamicArray< int > >* stackGuard2 = new sgdm::StackGuard< sgdc::DynamicArray< int > >(std::move(*stackGuard));

	EXPECT_EQ(TEST_STACK_GUARD_countingAllocator->getAllocations(), 2);
	EXPECT_EQ(stackGuard2->getGuarded(), dynamicArray);

	delete stackGuard2;

	EXPECT_EQ(TEST_STACK_GUARD_countingAllocator->getDeallocations(), 2);
}

/* Test the move assignment operator of a stack guard. */
TEST(StackGuard, MoveAssignment) {
	sgdc::DynamicArray< int >* dynamicArray = TEST_STACK_GUARD_countingAllocator->allocate(1);
	TEST_STACK_GUARD_countingAllocator->construct(dynamicArray, sgdc::DynamicArray< int >());
	sgdm::StackGuard< sgdc::DynamicArray< int > >* stackGuard = new sgdm::StackGuard< sgdc::DynamicArray< int > >(TEST_STACK_GUARD_countingAllocator, dynamicArray);
	sgdm::StackGuard< sgdc::DynamicArray< int > >* stackGuard2 = new sgdm::StackGuard< sgdc::DynamicArray< int > >(NULL);
	stackGuard2 = std::move(stackGuard);

	EXPECT_EQ(TEST_STACK_GUARD_countingAllocator->getAllocations(), 3);
	EXPECT_EQ(stackGuard2->getGuarded(), dynamicArray);

	delete stackGuard2;

	EXPECT_EQ(TEST_STACK_GUARD_countingAllocator->getDeallocations(), 3);
}