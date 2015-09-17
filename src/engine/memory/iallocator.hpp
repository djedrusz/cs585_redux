/*
	Dominik Jedruszczak

	iallocator.hpp
	Declaration of the "IAllocator" interface.
*/

#ifndef INCLUDED_IALLOCATOR
#define INCLUDED_IALLOCATOR

namespace StevensDev{
	namespace sgdm { // Stevens Game Development Memory.
		/* The "IAllocator" interface. */
		template< typename T >
		class IAllocator {
			private:
			public:
				/* Function(s). */
				virtual T* allocate(unsigned int count) = 0; // Allocate the specified amount of memory and return a pointer to the newly created memory block.
				virtual void deallocate(T* memoryBlock, unsigned int count) = 0; // Deallocate the specified amount of memory from the specified memory block.
		};
	}
}

#endif
