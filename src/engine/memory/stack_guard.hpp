/*
	Dominik Jedruszczak

	stack_guard.hpp
	Declaration of the "StackGuard" class.
*/

#ifndef INCLUDED_STACK_GUARD
#define INCLUDED_STACK_GUARD

#include "default_allocator.hpp"

namespace StevensDev {
namespace sgdm { /* Stevens Game Development Memory. */
/* A stack guard. */
template< typename T >
class StackGuard {
	private:
		/* Constructor(s). */
		/* Data member(s). */
		IAllocator< T >* allocator; // The allocator.
		T* guarded; // A pointer to the guarded object.
	public:
		/* Constructor(s). */
		StackGuard(T* guarded); // Constructor with specified guarded object pointer.
		StackGuard(IAllocator< T >* allocator, T* guarded); // Constructor with specified allocator and guarded object pointer.
		StackGuard(StackGuard< T >&& stackGuard); // Move constructor.
		/* Destructor(s). */
		~StackGuard(); // Default destructor.
		/* Operator(s). */
		StackGuard< T >& operator = (StackGuard< T >&& stackGuard); // Move assignment operator.
		/* Function(s). */
		const T* getGuarded() const; // Return the guarded object pointer.
};

/* Constructor with specified guarded object pointer. */
template< typename T >
StackGuard< T >::StackGuard(T* guarded)
:	allocator(new DefaultAllocator< T >()),
	guarded(guarded) {
	;
}

/* Constructor with specified allocator and guarded object pointer. */
template< typename T >
StackGuard< T >::StackGuard(IAllocator< T >* allocator, T* guarded)
:	allocator(allocator),
	guarded(guarded) {
	;
}

/* Move constructor. */
template< typename T >
StackGuard< T >::StackGuard(StackGuard< T >&& stackGuard)
:	allocator(stackGuard.allocator),
	guarded(stackGuard.guarded) {
	stackGuard.guarded = NULL;
}

/* Default destructor. */
template< typename T >
StackGuard< T >::~StackGuard() {
	allocator->deallocate(guarded, 1);
}

/* Move assignment operator. */
template< typename T >
StackGuard< T >& StackGuard< T >::operator = (StackGuard< T >&& stackGuard) {
	allocator = stackGuard.allocator;
	guarded = stackGuard.guarded;
	stackGuard.guarded = NULL;
}

/* Return the guarded object pointer. */
template< typename T >
const T* StackGuard< T >::getGuarded() const {
	return guarded;
}

}
}

#endif