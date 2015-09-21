/*
	Dominik Jedruszczak

	dynamic_array.hpp
	Declaration of the "DynamicArray" class.
*/

#ifndef INCLUDED_DYNAMIC_ARRAY
#define INCLUDED_DYNAMIC_ARRAY

#include <algorithm>
#include "../memory/default_allocator.hpp"

#define DYNAMIC_ARRAY_DEFAULT_CAPACITY 10 // The default capacity.
#define DYNAMIC_ARRAY_GROW_RATIO 1.6 // The ratio at which the array grows. Modelled after Chris Taylor's explanation of the golden ratio.
#define DYNAMIC_ARRAY_MINIMUM_CAPACITY 10 // The minimum capacity.
#define DYNAMIC_ARRAY_SHRINK_THRESHOLD_RATIO 0.25 // The threshold at which the array shrinks.
// The ratio at which the array shrinks. The shrink ratio is greater than the threshold so that a grow does not immediately follow a shrink.
#define DYNAMIC_ARRAY_SHRINK_RATIO 0.5

namespace StevensDev {
	namespace sgdc { // Stevens Game Development Containers.
		/* An array which grows and shrinks dynamically. */
		template< typename T >
		class DynamicArray {
			private:
				/* Data member(s). */
				sgdm::IAllocator< T >* allocator; // The allocator->
				T* array; // The underlying array.
				unsigned int capacity; // The current maximum number of elements.
				unsigned int size; // The current number of elements.
				/* Function(s). */
				void grow(); // Increase the capacity of the array.
				void shrink(); // Decrease the capacity of the array.
			public:
				/* Constructor(s). */
				// Constructor with optional specified allocator and capacity.
				DynamicArray(sgdm::IAllocator< T >* allocator = new sgdm::DefaultAllocator< T >, unsigned int capacity = DYNAMIC_ARRAY_DEFAULT_CAPACITY);
				DynamicArray(const DynamicArray< T >& dynamicArray); // Copy constructor.
				DynamicArray(DynamicArray< T >&& dynamicArray); // Move constructor.
				/* Destructor(s). */
				~DynamicArray(); // Default destructor.
				/* Operator(s). */
				DynamicArray< T >& operator = (const DynamicArray< T >& dynamicArray); // Copy assignment operator.
				DynamicArray< T >& operator = (DynamicArray< T >&& dynamicArray); // Move assignment operator.
				T& operator [] (unsigned int index); // Subscript set.
				const T& operator [] (unsigned int index) const; // Subscript get.
				/* Function(s). */
				void prepend(const T& element); // Prepend an element.
				void append(const T& element); // Append an element.
				void insert(unsigned int index, const T& element); // Insert an element at the specified index.
				T pull(); // Remove and return the first element.
				T push(); // Remove and return the last element.
				T remove(unsigned int index); // Remove and return the element at the specified index.
				void set(unsigned int index, const T& element); // Set the element at the specified index.
				const T& get(unsigned int index); // Return the element at the specified index.
				const unsigned int getSize() const; // Return the size.
		};

	    /* Increase the capacity of the array. */
	    template< typename T >
	    void DynamicArray< T >::grow() {
	    	if (size  >= capacity) {
	            unsigned int newCapacity = (unsigned int)(capacity * DYNAMIC_ARRAY_GROW_RATIO);
	            T* newArray = allocator->allocate(newCapacity);
	            std::move(array, &array[size], newArray);
	            allocator->deallocate(array, capacity);
	            capacity = newCapacity;
	            array = newArray;
	        }
	    }

	    /* Decrease the capacity of the array. */
	    template< typename T >
	    void DynamicArray< T >::shrink() {
	    	if (size <= capacity * DYNAMIC_ARRAY_SHRINK_THRESHOLD_RATIO) {
		        unsigned int newCapacity = (unsigned int)(capacity * DYNAMIC_ARRAY_SHRINK_RATIO);
		        if (newCapacity <  DYNAMIC_ARRAY_MINIMUM_CAPACITY) {
		        	newCapacity = DYNAMIC_ARRAY_MINIMUM_CAPACITY;
		        }
		        T* newArray = allocator->allocate(newCapacity);
		        std::move(array, &array[size], newArray);
		        allocator->deallocate(array, capacity);
		        capacity = newCapacity;
		        array = newArray;
		    }
	    }

		/* Constructor with specified allocator and inital capacity. */
		template< typename T >
		DynamicArray< T >::DynamicArray(sgdm::IAllocator< T >* allocator, unsigned int capacity)
		:	allocator(allocator),
			array(allocator->allocate(capacity)),
			capacity(capacity),
			size(0) {
		}

		/* Copy constructor. */
		template< typename T >
		DynamicArray< T >::DynamicArray(const DynamicArray& dynamicArray)
		:	allocator(dynamicArray.allocator),
			capacity(dynamicArray.capacity),
			size(dynamicArray.size) {
			array = allocator->allocate(capacity);
			std::copy(dynamicArray.array, &dynamicArray.array[size], array);
		}

		/* Move constructor. */
		template< typename T >
		DynamicArray< T >::DynamicArray(DynamicArray&& dynamicArray)
		:	allocator(dynamicArray.allocator),
			capacity(dynamicArray.capacity),
			size(dynamicArray.size) {
			array = dynamicArray.array;
			dynamicArray.array = NULL;
		}

		/* Default destructor. */
		template< typename T >
		DynamicArray< T >::~DynamicArray() {
			if (array != NULL) { // If the dynamic array has not been moved...
				allocator->deallocate(array, capacity);
			}
		}

		/* Copy assignment operator. */
		template< typename T >
		DynamicArray< T >& DynamicArray< T >::operator = (const DynamicArray< T >& dynamicArray) {
			if (this != &dynamicArray) { // Avoid self-assignment.
				allocator->deallocate(array, dynamicArray.capacity); // Clean up old data.

				allocator = dynamicArray.allocator;
				array = allocator->allocate(dynamicArray.capacity);
				capacity = dynamicArray.capacity;
				size = dynamicArray.size;
				std::copy(dynamicArray.array, &dynamicArray.array[size], array);
			}
		}

		/* Move assignment operator. */
		template< typename T >
		DynamicArray< T >& DynamicArray< T >::operator = (DynamicArray< T >&& dynamicArray) {
			if (this != &dynamicArray) { // Avoid self-assignment.
				allocator->deallocate(array, dynamicArray.capacity); // Clean up old data.

				allocator = dynamicArray.allocator;
				capacity = dynamicArray.capacity;
				size = dynamicArray.size;
				array = dynamicArray.array;
				dynamicArray.array = NULL;
			}
		}

		/* Subscript set. */
		template< typename T >
		T& DynamicArray< T >::operator [] (unsigned int index) {
			return array[index];
		}

		/* Subscript get. */
		template< typename T >
		const T& DynamicArray< T >::operator [] (unsigned int index) const {
			return array[index];
		}

		/* Prepend an element. */
		template< typename T >
		void DynamicArray< T >::prepend(const T& element) {
			grow();

			std::move(array, &array[size], &array[1]);
			array[0] = element;
			size++;
		}

		/* Append an element. */
		template< typename T >
		void DynamicArray< T >::append(const T& element) {
			grow();

			array[size] = element;
			size++;
		}

		/* Insert an element at the specified index. */
		template< typename T >
		void DynamicArray< T >::insert(unsigned int index, const T& element) {
			grow();
			
			std::move(&array[index], &array[size], &array[index + 1]);
			array[index] = element;
			size++;
		}

		/* Remove and return the first element. */
		template< typename T >
		T DynamicArray< T >::pull() {
			T element = array[0];
			std::move_backward(&array[1], &array[size], &array[size - 1]);
			size--;

			shrink();

			return element;
		}

		/* Remove and return the last element. */
		template< typename T >
		T DynamicArray< T >::push() {
			T element = array[size - 1];
			size--;

			shrink();

			return element;
		}

		/* Remove and return the element at the specified index. */
		template< typename T >
		T DynamicArray< T >::remove(unsigned int index) {
			T element = array[index];
			std::move_backward(&array[index + 1], &array[size], &array[size - 1]);
			size--;

			shrink();

			return element;
		}

		/* Set the element at the specified index. */
		template< typename T >
		void DynamicArray< T >::set(unsigned int index, const T& element) {
			array[index] = element;
		}

		/* Return the element at the specified index. */
		template< typename T >
		const T& DynamicArray< T >::get(unsigned int index) {
			return array[index];
		}

		/* Return the size. */
		template< typename T >
		const unsigned int DynamicArray< T >::getSize() const {
			return size;
		}
	}
}

#endif
