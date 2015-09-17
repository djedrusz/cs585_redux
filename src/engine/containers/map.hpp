/*
	Dominik Jedruszczak

	map.hpp
	Declaration of the "MapNode" and "Map" classes.
*/

#ifndef INCLUDED_MAP
#define INCLUDED_MAP

#include "dynamic_array.hpp"
#include <string>
#include <stdio.h>

#define MAP_NODE_NUM_CHILDREN 26 // The number of children in a map node. One for each lower-case letter in the english alphabet.

namespace StevensDev {
	namespace sgdc { // Stevens Game Development Containers.
		/* A node in the map. */
		template< typename T >
		struct MapNode {
			bool hasValue; // Whether or not the node contains a value.
			T value; // The value.
			MapNode< T >* children[MAP_NODE_NUM_CHILDREN]; // The children.
		};

		/* A mapping of key and value pairs. */
		template< typename T >
		class Map {
			private:
				/* Data member(s). */
				sgdm::IAllocator< MapNode< T > >* allocator; // The allocator.
				MapNode< T >* root; // The root node.
				//DynamicArray< const char* > keys; // The keys.
				DynamicArray< T > values; // The values.
				/* Function(s). */
				MapNode< T >* copyMapNode(MapNode< T >* mapNode); // Return a copy of a map node.
				void deallocateMapNode(MapNode< T >* mapNode); // Deallocate a map node.
				void deallocateMap(); // Deallocate the map.
				void print(MapNode< T >* mapNode, unsigned int depth); // Print out a map node.
			public:
				/* Constructor(s). */
				Map(sgdm::IAllocator< MapNode< T > >* allocator = new sgdm::DefaultAllocator< MapNode< T > >()); // Constructor with optional specified allocator.
				Map(const Map< T >& map); // Copy constructor.
				/* Destructor(s). */
				~Map(); // Default destructor.
				/* Operator(s). */
				Map< T >& operator = (const Map< T >& map); // Copy assignment operator.
				T& operator [] (const std::string& key); // Subscript set.
				const T& operator [] (const std::string& key) const; // Subscript get.
				/* Function(s). */
				void add(const std::string& key, const T& value); // Add a value with the specified key.
				T remove(const std::string& key); // Remove the value with the specified key.
				bool has(const std::string& key) const; // Return whether or not there exists a value at the specified key.
				T& get(const std::string& key) const; // Return the value at the specified key.
				//const DynamicArray< const char* >& getKeys() const; // Return the keys.
				const DynamicArray< T >& getValues() const; // Return the values.
				void print(); // Print out the map.
		};

		/* Return a copy of a map node. */
		template< typename T >
		MapNode< T >* Map< T >::copyMapNode(MapNode< T >* mapNode) {
			MapNode< T >* newMapNode = allocator->allocate(1);
			newMapNode->hasValue = mapNode->hasValue;
			newMapNode->value = mapNode->value;
			for (unsigned int i = 0; i < MAP_NODE_NUM_CHILDREN; i++) {
				newMapNode->children[i] = copyMapNode(mapNode->children[i]);
			}

			return newMapNode;
		}

		/* Deallocate a map node. */
		template< typename T >
		void Map< T >::deallocateMapNode(MapNode< T >* mapNode) {
			for (unsigned int i = 0; i < MAP_NODE_NUM_CHILDREN; i++) {
				if (mapNode->children[i] != NULL) {
					deallocateMapNode(mapNode->children[i]);
					allocator->deallocate(mapNode->children[i], 1);
				}
			}
		}

		/* Deallocate the map. */
		template< typename T >
		void Map< T >::deallocateMap() {
			deallocateMapNode(root);
			allocator->deallocate(root, 1);
		}

		/* Print out a map node. */
		template< typename T >
		void Map< T >::print(MapNode< T >* mapNode, unsigned int depth) {
			for (unsigned int i = 0; i < MAP_NODE_NUM_CHILDREN; i++) {
				if (mapNode->children[i] != NULL) {
					for (unsigned int j = 0; j < depth; j++) {
						printf("\t");
					}
					printf("%c", 'a' + (char)i);
					if (mapNode->children[i]->hasValue) {
						printf(":%i", mapNode->children[i]->value);
					}
					printf("\n");
					print(mapNode->children[i], depth + 1);
				}
			}
		}

		/* Constructor with optional specified allocator. */
		template< typename T >
		Map< T >::Map(sgdm::IAllocator< MapNode< T > >* allocator)
		:	root(allocator->allocate(1)), allocator(allocator) {
			root->hasValue = false;
			for (unsigned int i = 0; i < MAP_NODE_NUM_CHILDREN; i++) {
				root->children[i] = NULL;
			}
		}

		/* Copy constructor. */
		template< typename T >
		Map< T >::Map(const Map< T >& map) {
			deallocateMap();

			allocator = map.allocator;

			root = copyMapNode(map.root);

			/* TODO: Copy keys and values. */
		}

		/* Subscript set. */
		template< typename T >
		T& Map< T >::operator [] (const std::string& key) {
			get(key);
		}

		/* Subscript get. */
		template< typename T >
		const T& Map< T >::operator [] (const std::string& key) const {
			get(key);
		}

		/* Default destructor. */
		template< typename T >
		Map< T >::~Map() {
			deallocateMap();
		}

		/* Copy assignment operator. */
		template< typename T >
		Map< T >& Map< T >::operator = (const Map< T >& map) {
			deallocateMap();

			allocator = map.allocator;

			root = copyMapNode(map.root);

			/* TODO: Copy keys and values. */
		}

		/* TODO: Operators. */

		/* Add a value with the specified key. */
		template< typename T >
		void Map< T >::add(const std::string& key, const T& value) {
			if (key.length() > 0) {
				MapNode< T >* current = root;
				unsigned int depth = 0;
				while (depth < key.length()) {
					if (current->children[key[depth] - 'a'] == NULL) {
						current->children[key[depth] - 'a'] = allocator->allocate(1);
						current->children[key[depth] - 'a']->hasValue = false;
						for (unsigned int i = 0; i < MAP_NODE_NUM_CHILDREN; i++) {
							current->children[key[depth] - 'a']->children[i] = NULL;
						}
					}
					current = current->children[key[depth] - 'a'];
					depth++;
				}
				current->hasValue = true;
				current->value = value;

				//keys.append(key.c_str());
				values.append(value);
			}
		}

		/* Remove the value with the specified key. */
		template< typename T >
		T Map< T >::remove(const std::string& key) {
			MapNode< T >* current = root;
			unsigned int depth = 0;
			while (depth < key.length()) {
				current = current->children[key[depth] - 'a'];
				depth++;
			}
			current->hasValue = false;
			return current->value;

			/* TODO: Remove from keys and values. */
		}

		/* Return whether or not the map contains a value at the specified key. */
		template< typename T >
		bool Map< T >::has(const std::string& key) const {
			MapNode< T >* current = root;
			unsigned int depth = 0;
			while (depth < key.length()) {
				if (current->children[key[depth] - 'a'] == NULL) {
					return false;
				}
				current = current->children[key[depth] - 'a'];
				depth++;
			}
			return current->hasValue;
		}

		/* Return the value at the specified key. */
		template< typename T >
		T& Map< T >::get(const std::string& key) const {
			MapNode< T >* current = root;
			unsigned int depth = 0;
			while (depth < key.length()) {
				current = current->children[key[depth] - 'a'];
				depth++;
			}
			return current->value;
		}

		/* Return the keys. 
		template< typename T >
		const DynamicArray< const char* >& Map< T >::getKeys() const {
			return keys;
		}

		/* Return the values. */
		template< typename T >
		const DynamicArray< T >& Map< T >::getValues() const {
			return values;
		}

		/* Print the map. */
		template< typename T >
		void Map< T >::print() {
			printf("ROOT\n");
			print(root, 1);
			printf("printed root\n");
			printf("\n");
		}
	}
}

#endif