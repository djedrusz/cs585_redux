/*
	Dominik Jedruszczak

	test_default_allocator.cpp
	Tests for the "DefaultAllocator" class.
*/

#include "../gtest/include/gtest/gtest.h"
#include "../src/engine/memory/default_allocator.hpp"
#include <vector>

template< typename T >
class TEST_DEFAULT_ALLOCATOR_A {
	public:
		T a;
		T b;
		T c;
		TEST_DEFAULT_ALLOCATOR_A() { a = 1, b = 2; c = 3;};
		TEST_DEFAULT_ALLOCATOR_A(T _a, T _b, T _c) { a = _a; b = _b; c = _c;};
		TEST_DEFAULT_ALLOCATOR_A(const TEST_DEFAULT_ALLOCATOR_A< T >& other) { a = other.a; b = other.b; c = other.c; };
		TEST_DEFAULT_ALLOCATOR_A(TEST_DEFAULT_ALLOCATOR_A< T >&& other) { a = other.a; b = other.b; c = other.c;};
};

/* Test allocation of a default allocator. */
TEST(DefaultAllocator, Allocation) {
	StevensDev::sgdm::DefaultAllocator<int> defaultAllocator;
	int* memoryBlock = defaultAllocator.allocate(10);
	EXPECT_TRUE(memoryBlock != NULL);
	defaultAllocator.deallocate(memoryBlock, 10);
}

/* Test in-place copy construction of a default allocator. */
TEST(DefaultAllocator, CopyContruction) {
	StevensDev::sgdm::DefaultAllocator< TEST_DEFAULT_ALLOCATOR_A< int > > defaultAllocator;
	TEST_DEFAULT_ALLOCATOR_A< int >* as = defaultAllocator.allocate(3);

	defaultAllocator.construct(&as[0], TEST_DEFAULT_ALLOCATOR_A< int >());
	EXPECT_EQ(as[0].a, 1);
	EXPECT_EQ(as[0].b, 2);
	EXPECT_EQ(as[0].c, 3);

	defaultAllocator.construct(&as[1], TEST_DEFAULT_ALLOCATOR_A< int >(2, 3, 4));
	EXPECT_EQ(as[1].a, 2);
	EXPECT_EQ(as[1].b, 3);
	EXPECT_EQ(as[1].c, 4);

	defaultAllocator.construct(&as[2], TEST_DEFAULT_ALLOCATOR_A< int >(as[1]));
	EXPECT_EQ(as[2].a, 2);
	EXPECT_EQ(as[2].b, 3);
	EXPECT_EQ(as[2].c, 4);

	defaultAllocator.deallocate(as, 3);
}

/* Test in-place move construction of a default allocator. */
TEST(DefaultAllocator, MoveConstruction) {
	StevensDev::sgdm::DefaultAllocator< TEST_DEFAULT_ALLOCATOR_A< int > > defaultAllocator;
	TEST_DEFAULT_ALLOCATOR_A< int >* as = defaultAllocator.allocate(2);

	defaultAllocator.construct(&as[0], TEST_DEFAULT_ALLOCATOR_A< int >());
	EXPECT_EQ(as[0].a, 1);
	EXPECT_EQ(as[0].b, 2);
	EXPECT_EQ(as[0].c, 3);

	defaultAllocator.construct(&as[1], TEST_DEFAULT_ALLOCATOR_A< int >(std::move(as[0])));
	EXPECT_EQ(as[1].a, 1);
	EXPECT_EQ(as[1].b, 2);
	EXPECT_EQ(as[1].c, 3);

	defaultAllocator.deallocate(as, 2);
}

/* Test in-place destruction of a default allocator. */
TEST(DefaultAllocator, Destruction) {
	// Not sure how to test this...
}