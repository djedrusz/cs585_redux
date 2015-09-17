/*
	Dominik Jedruszczak

	default_allocator.hpp
	The declaration of the "DefaultAllocator" class.
*/

#ifndef INCLUDED_DEFAULT_ALLOCATOR
#define INCLUDED_DEFAULT_ALLOCATOR

#include "iallocator.hpp"

namespace StevensDev {
	namespace sgdm { // Stevens Game Development Memory.
		/* The default allocator for containers. */
		template< typename T >
		class DefaultAllocator : public IAllocator< T > {
			private:
			public:
				/* Function(s). */
				T* allocate(unsigned int count); // Allocate the specified amount of memory and return a pointer to the newly allocated memory block.
				void deallocate(T* memoryBlock, unsigned int count); // Deallocate the specified amount of memory from the specified memory block.
		};

		/* Allocate the specified amount of memory and return a pointer to the newly allocated memory block. */
		template< typename T >
		T* DefaultAllocator< T >::allocate(unsigned int count) {
		    return new T[count];
		}

		/* Deallocate the specified amount of memory from the specified memory block. */
		template< typename T >
		void DefaultAllocator< T >::deallocate(T* memoryBlock, unsigned int count) {
			delete memoryBlock;
		}
	}
}

#endif
