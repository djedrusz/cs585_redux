/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_SMART_MAP
#define INCLUDED_SMART_MAP

#include <iostream>
#include <string>
#include "dynamic_array.hpp"

#define SMART_MAP_NODE_NUM_CHILDREN 26

namespace StevensDev {
namespace sgdc { // Stevens Game Development Containers.

/* 
	A map which culls empty branches on removal.
	Possible characters: 'a' - 'z'.
*/
template< typename T >
class SmartMap {
	private:
		/* Class(es). */
		class SmartMapNode {
			private:
				/* Data member(s). */
				SmartMapNode* parent;
				bool b_hasValue;
				T value;
				bool b_hasChildren;
				SmartMapNode* children[SMART_MAP_NODE_NUM_CHILDREN];
			public:
				/* Constructor(s). */
				SmartMapNode(SmartMapNode* parent);
				SmartMapNode(const SmartMapNode& smartMapNode);
				SmartMapNode(SmartMapNode&& smartMapNode);
				/* Destructor(s). */
				~SmartMapNode();
				/* Operator(s). */
				SmartMapNode& operator = (const SmartMapNode& smartMapNode);
				SmartMapNode& operator = (SmartMapNode&& smartMapNode);
				/* Function(s). */
				SmartMapNode* getParent();
				// Value.
				bool hasValue() const;
				void setValue(T value);
				T& getValue();
				const T& getValue() const;
				void removeValue();
				// Children.
				bool hasChildren() const;
				void addChild(const char& character);
				SmartMapNode* getChild(const char& character);
				void removeChild(const char& character);
#ifdef SMART_MAP_DEBUG
				void print(unsigned int level) const;
#endif

		};
		/* Data member(s). */
		SmartMapNode* root; // Must be pointer or compiler yells.
		DynamicArray< std::string > keys;
		DynamicArray< T > values;
	public:
		/* Constructor(s). */
		SmartMap();
		SmartMap(const SmartMap& smartMap);
		SmartMap(SmartMap&& smartMap);
		/* Destructor(s). */
		~SmartMap();
		/* Operator(s). */
		SmartMap& operator = (const SmartMap& smartMap);
		SmartMap& operator = (SmartMap&& smartMap);
		/* Function(s). */
		void put(const std::string& key, const T& value);
		void putIfAbsent(const std::string& key, const T& value);
		void remove(const std::string& key);
		bool has(const std::string& key) const;
		T& get(const std::string& key);
		const T& get(const std::string& key) const;
		const DynamicArray< std::string >& getKeys() const;
		const DynamicArray< T >& getValues() const;
#ifdef SMART_MAP_DEBUG
		void print() const;
#endif
};

template< typename T >
SmartMap< T >::SmartMapNode::SmartMapNode(SmartMapNode* parent) 
:	parent(parent),
	b_hasValue(false),
	b_hasChildren(false) {
	for (unsigned int i = 0; i < SMART_MAP_NODE_NUM_CHILDREN; i++) {
		children[i] = nullptr;
	}
#ifdef SMART_MAP_DEBUG
	std::cout << "SmartMapNode default construction." << std::endl;
#endif
}

template< typename T >
SmartMap< T >::SmartMapNode::SmartMapNode(const SmartMapNode& smartMapNode)
:	parent(parent),
	b_hasValue(smartMapNode.b_hasValue),
	value(smartMapNode.value),
	b_hasChildren(smartMapNode.b_hasChildren) {
	for (unsigned int i = 0; i < SMART_MAP_NODE_NUM_CHILDREN; i++) {
		children[i] = smartMapNode.children[i];
	}
#ifdef SMART_MAP_DEBUG
	std::cout << "SmartMapNode copy construction." << std::endl;
#endif	
}

template< typename T >
SmartMap< T >::SmartMapNode::SmartMapNode(SmartMapNode&& smartMapNode)
:	parent(std::move(parent)),
	b_hasValue(std::move(smartMapNode.b_hasValue)),
	value(std::move(smartMapNode.value)),
	b_hasChildren(std::move(smartMapNode.b_hasChildren)) {
	for (unsigned int i = 0; i < SMART_MAP_NODE_NUM_CHILDREN; i++) {
		children[i] = std::move(smartMapNode.children[i]);
	}
#ifdef SMART_MAP_DEBUG
	std::cout << "SmartMapNode move construction." << std::endl;
#endif
}

template< typename T >
SmartMap< T >::SmartMapNode::~SmartMapNode() {
	for (unsigned int i = 0; i < SMART_MAP_NODE_NUM_CHILDREN; i++) {
		if (children[i] != nullptr) {
			delete children[i];
		}
	}
#ifdef SMART_MAP_DEBUG
	std::cout << "SmartMapNode default destruction." << std::endl;
#endif
}

template< typename T >
typename SmartMap< T >::SmartMapNode& SmartMap< T >::SmartMapNode::
operator = (const SmartMap< T >::SmartMapNode& smartMapNode) {
	parent = smartMapNode.parent;
	b_hasValue = smartMapNode.b_hasValue;
	value = smartMapNode.value;
	b_hasChildren = smartMapNode.b_hasChildren;
	for (unsigned int i = 0; i < SMART_MAP_NODE_NUM_CHILDREN; i++) {
		children[i] = smartMapNode.children[i];
	}
}

template< typename T >
typename SmartMap< T >::SmartMapNode& SmartMap< T >::SmartMapNode::
operator = (SmartMap< T >::SmartMapNode&& smartMapNode) {
	parent = std::move(smartMapNode.parent);
	b_hasValue = std::move(smartMapNode.b_hasValue);
	value = std::move(smartMapNode.value);
	b_hasChildren = smartMapNode.b_hasChildren;
	for (unsigned int i = 0; i < SMART_MAP_NODE_NUM_CHILDREN; i++) {
		children[i] = std::move(smartMapNode.children[i]);
	}
}

template< typename T >
typename SmartMap< T >::SmartMapNode* SmartMap< T >::SmartMapNode::
getParent() {
	return parent;
}

template< typename T >
bool SmartMap< T >::SmartMapNode::hasValue() const {
	return b_hasValue;
}

template< typename T >
void SmartMap< T >::SmartMapNode::setValue(T value) {
	b_hasValue = true;
	this->value = value;
}

template< typename T >
T& SmartMap< T >::SmartMapNode::getValue() {
	return value;
}

template< typename T >
const T& SmartMap< T >::SmartMapNode::getValue() const {
	return value;
}

template< typename T >
void SmartMap< T >::SmartMapNode::removeValue() {
	b_hasValue = false;
}

template< typename T >
bool SmartMap< T >::SmartMapNode::hasChildren() const {
	return b_hasChildren;
}

template< typename T >
void SmartMap< T >::SmartMapNode::addChild(const char& character) {
	b_hasChildren = true;
	if (children[character - 'a'] == nullptr) {
		children[character - 'a'] = new SmartMapNode(this);
	}
}

template< typename T >
typename SmartMap< T >::SmartMapNode* SmartMap< T >::SmartMapNode::
getChild(const char& character) {
	return children[character - 'a'];
}

template< typename T >
void SmartMap< T >::SmartMapNode::removeChild(const char& character) {
	if (children[character - 'a'] != nullptr) {
		delete children[character - 'a'];
		children[character - 'a'] = nullptr;
	}

	b_hasChildren = false;
	for (unsigned int i = 0; i < SMART_MAP_NODE_NUM_CHILDREN; i++) {
		if (children[i] != nullptr) {
			b_hasChildren = true;
		}
	}
}

#ifdef SMART_MAP_DEBUG
template< typename T>
void SmartMap< T >::SmartMapNode::print(unsigned int level) const {
	if (b_hasValue) {
		std::cout << value;
	}
	else {
		std::cout << "empty";
	}
	std::cout << std::endl;

	for (unsigned int i = 0; i < SMART_MAP_NODE_NUM_CHILDREN; i++) {
		if (children[i] != nullptr) {
			for (unsigned int j = 0; j < level; j++) {
				std::cout << '\t';
			}
			std::cout << (char)('a' + i) << ":";
			children[i]->print(level + 1);
		}
	}

}
#endif

template< typename T >
SmartMap< T >::SmartMap() {
	root = new SmartMapNode(nullptr);
}

template< typename T >
SmartMap< T >::SmartMap(const SmartMap& smartMap)
:	root(smartMap.root),
	keys(smartMap.keys),
	values(smartMap.values) {
	;
}

template< typename T >
SmartMap< T >::SmartMap(SmartMap&& smartMap)
:	root(std::move(smartMap.root)),
	keys(std::move(smartMap.keys)),
	values(std::move(smartMap.values)) {
	;
}

template< typename T >
SmartMap< T >::~SmartMap() {
	delete root;
}

template< typename T >
SmartMap< T >& SmartMap< T >::SmartMap::operator = (const SmartMap& smartMap) {
	root = smartMap.root;
	keys = smartMap.keys;
	values = smartMap.values;
}

template< typename T >
SmartMap< T >& SmartMap< T >::SmartMap::operator = (SmartMap&& smartMap) {
	root = std::move(smartMap.root);
	keys = std::move(smartMap.keys);
	values = std::move(smartMap.values);
}

template< typename T >
void SmartMap< T >::put(const std::string& key, const T& value) {
	SmartMapNode* current = root;

	for (unsigned int i = 0; i < key.size(); i++) {
		if (current->getChild(key.at(i)) == nullptr) {
			current->addChild(key.at(i));
		}
		current = current->getChild(key.at(i));
	}
	current->setValue(value);
}

template< typename T >
void SmartMap< T >::putIfAbsent(const std::string& key, const T& value) {
	SmartMapNode* current = root;

	for (unsigned int i = 0; i < key.size(); i++) {
		if (current->getChild(key.at(i)) == nullptr) {
			current->addChild(key.at(i));
		}
		current = current->getChild(key.at(i));
	}
	if (current->hasValue()) {
		current->setValue(value);
	}
}

template< typename T >
void SmartMap< T >::remove(const std::string& key) {
	unsigned int i;
	SmartMapNode* current = root;
	SmartMapNode* parent;
	bool cullFlag = true;

	/* Remove the value. */
	for (i = 0; i < key.size(); i++) {
		current = current->getChild(key.at(i));
	}
	current->removeValue();

	/* Cull the map. */
	for (i; i > 0; i--) {
		if (!current->hasChildren() && !current->hasValue()) {
			parent = current->getParent();
			parent->removeChild(key.at(i - 1));
			current = parent;
		}
		else {
			break;
		}
	}
}

template< typename T >
bool SmartMap< T >::has(const std::string& key) const {
	SmartMapNode* current = root;

	for (unsigned int i = 0; i < key.size(); i++) {
		if (!current->hasChild(key.at(i))) {
			return false;
		}
		current = current->getChild(key.at(i));
	}
	return current->hasValue();
}

template< typename T >
T& SmartMap< T >::get(const std::string& key) {
	SmartMapNode* current = root;

	for (unsigned int i = 0; i < key.size(); i++) {
		current = current->getChild(key.at(i));
	}
	return current->getValue();
}

template< typename T >
const T& SmartMap< T >::get(const std::string& key) const {
	SmartMapNode* current = root;

	for (unsigned int i = 0; i < key.size(); i++) {
		current = current->getChild(key.at(i));
	}
	return current->getValue();
}

template< typename T >
const DynamicArray< std::string >& SmartMap< T >::getKeys() const {
	return keys;
}

template< typename T >
const DynamicArray< T >& SmartMap< T >::getValues() const {
	return values;
}

#ifdef SMART_MAP_DEBUG
template< typename T >
void SmartMap< T >::print() const {
	std::cout << "root:";
	root->print(1);
}
#endif

}
}

#endif