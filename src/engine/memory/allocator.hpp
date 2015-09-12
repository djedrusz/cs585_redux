/*
	Dominik Jedruszczak

	allocator.hpp
	Declaration of the "Allocator" abstract class.
*/

#ifndef INCLUDED_ALLOCATOR
#define INCLUDED_ALLOCATOR

namespace StevensDev{
	namespace sgdm { // Stevens Game Development Memory.
		/* The "Allocator" abstract class. */
		template<typename T>
		class Allocator {
			private:
			public:
				/* Function(s). */
				virtual T* allocate(unsigned int count) = 0; // Allocate the specified amount of memory and return a pointer to the newly created memory block.
				virtual void deallocate(T* memoryBlock, unsigned int count) = 0; // Deallocate the specified amount of memory from the specified memory block.
		};
	}
}

#endif
