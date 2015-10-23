m/* A node in the map. */
		template< typename T >
		class MapNode {
			private:
				/* Data member(s). */
				sgdm::IAllocator< MapNode< T > > allocator; // The allocator.
				bool d_hasValue; // Whether or not the node contains a value.
				T value; // The node's value.
				MapNode< T >* children[MAP_NODE_NUM_CHILDREN]; // Children.
			public:
				/* Constructor(s). */
				MapNode(sgdm::IAllocator< MapNode< T > >* allocator = new sgdm::DefaultAllocator< MapNode< T > >()); // Constructor with optional specified allocator.
				MapNode(const T& value, sgdm::IAllocator< MapNode< T > >* allocator = new sgdm::DefaultAllocator< MapNode< T > >()); // Constructor with specified value, and optional specified allocator.
				MapNode(const MapNode< T >& mapNode); // Copy constructor.
				/* Operator(s). */
				MapNode< T >& operator = (const MapNode< T >& mapNode); // Copy assignment operator.
				/* Function(s). */
				const bool hasValue(); // Return whether or not the node contains a value.
				const T& getValue(); // Return the value.
				const MapNode< T >** getChildren(); // Return the children.
				void add(const std::string key, const T& value); // Add the value at the specified key.
				T remove(const std::string key); // Remove the value at the specified key and return its value.
				bool has(const std::string key) const; // Return whether or not there exists a value at the specified key.
				T& get(const std::string key) const; // Return the value at the specified key.
		};

		/* Constructor with optional specified allocator. */
		template< typename T >
		MapNode< T >::MapNode(sgdm::IAllocator< MapNode< T > >* allocator)
		:	allocator(allocator) {
			d_hasValue = false;
		}

		/* Constructor with specified value, and optional specified allocator. */
		template< typename T >
		MapNode< T >::MapNode(const T& value, sgdm::IAllocator< MapNode< T > >* allocator)
		:	value(value), allocator(allocator) {
			d_hasValue = true;
		}

		/* Copy constructor. */
		template< typename T >
		MapNode< T >::MapNode(const MapNode< T >& mapNode)
		:	allocator(mapNode.allocator), d_hasValue(mapNode.d_hasValue), value(mapNode.value) {
			memcpy(children, mapNode.children, MAP_NODE_NUM_CHILDREN * sizeof(MapNode< T >*));
		}

		/* Copy assignment operator. */
		template< typename T >
		MapNode< T >& MapNode< T >::operator = (const MapNode< T >& mapNode) {
			if (*this != mapNode) { // Avoid self-assignment.
				allocator = mapNode.allocator;
				d_hasValue = mapNode.d_hasValue;
				value = mapNode.value;
				memcpy(children, mapNode.children, MAP_NODE_NUM_CHILDREN * sizeof(MapNode< T >*));
			}
		}

		/* Return whether or not the node contains a value. */
		template< typename T >
		const bool MapNode< T >::hasValue() {
			return d_hasValue;
		}

		/* Return the value. */
		template< typename T >
		const T& MapNode< T >::getValue() {
			return value;
		}

		/* Return the children. */
		template< typename T >
		const MapNode< T >** MapNode< T >::getChildren() {
			return children;
		}

		/* Add the value at the specified key. */
		template< typename T >
		void MapNode< T >::add(const std::string key, const T& value) {
			if (key.length() == 0) { // If this is the node at which the key ends...
				d_hasValue = true;
				this->value = value;
			}
			else { // Otherwise must search deeper within the map...
				if (children[key[0] - 'a'] == NULL) { // If the next subnode does not exist, create it.
					children[key[0] - 'a'];
				}
			}
		}