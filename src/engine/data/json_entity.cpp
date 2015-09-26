/*
	Dominik Jedruszczak

	json_entity.cpp
	Implementation of the "JsonEntity" class.
*/

#include "json_entity.hpp"

namespace StevensDev {
namespace sgdd { /* Stevens Game Development Data. */

/* Initialize static default allocators. */
sgdm::DefaultAllocator< std::string > JsonEntity::defaultStringAllocator;
sgdm::DefaultAllocator< sgdc::DynamicArray< JsonEntity > > JsonEntity::defaultDynamicArrayAllocator;
sgdm::DefaultAllocator< sgdc::Map< JsonEntity > > JsonEntity::defaultMapAllocator;

/* Copy constructor. */
JsonEntity::JsonEntity(const JsonEntity& jsonEntity)
:	type(jsonEntity.type) {
	if (type == BOOL) {
		data.b = jsonEntity.data.b;
	}
	else if (type == INT) {
		data.i = jsonEntity.data.i;
	}
	else if (type == DOUBLE) {
		data.d = jsonEntity.data.d;
	}
	else if (type == STRING) {
		stringAllocator = jsonEntity.stringAllocator;
		data.s = stringAllocator->allocate(1);
		stringAllocator->construct(data.s, *jsonEntity.data.s);
	}
	else if (type == ARRAY) {
		dynamicArrayAllocator = jsonEntity.dynamicArrayAllocator;
		data.a = dynamicArrayAllocator->allocate(1);
		dynamicArrayAllocator->construct(data.a, *jsonEntity.data.a);
	}
	else if (type == OBJECT) {
		mapAllocator = jsonEntity.mapAllocator;
		data.o = mapAllocator->allocate(1);
		mapAllocator->construct(data.o, *jsonEntity.data.o);
	}
}

/* Move constructor. */
JsonEntity::JsonEntity(JsonEntity&& jsonEntity)
:	type(jsonEntity.type) {
	if (type == BOOL) {
		data.b = jsonEntity.data.b;
	}
	else if (type == INT) {
		data.i = jsonEntity.data.i;
	}
	else if (type == DOUBLE) {
		data.d = jsonEntity.data.d;
	}
	else if (type == STRING) {
		stringAllocator = jsonEntity.stringAllocator;
		data.s = std::move(jsonEntity.data.s);
		jsonEntity.data.s = nullptr;
	}
	else if (type == ARRAY) {
		dynamicArrayAllocator = jsonEntity.dynamicArrayAllocator;
		data.a = std::move(jsonEntity.data.a);
		jsonEntity.data.a = nullptr;
	}
	else if (type == OBJECT) {
		mapAllocator = jsonEntity.mapAllocator;
		data.o = std::move(jsonEntity.data.o);
		jsonEntity.data.o = nullptr;
	}
}

/* Constructor for type error. */
JsonEntity::JsonEntity()
:	type(ERROR) {
	data.b = false;
}

/* Constructor for type bool. */
JsonEntity::JsonEntity(bool b)
:	type(BOOL) {
	data.b = b;
}

/* Constructor for type int. */
JsonEntity::JsonEntity(int i)
:	type(INT) {
	data.i = i;
}

/* Constructor for type double. */
JsonEntity::JsonEntity(double d)
:	type(DOUBLE) {
	data.d = d;
}

/* Constructor for type string. */
JsonEntity::JsonEntity(const std::string& s)
:	JsonEntity(&defaultStringAllocator, s) {
	;
}

/* Constructor for type array. */
JsonEntity::JsonEntity(const sgdc::DynamicArray< JsonEntity >& a)
:	JsonEntity(&defaultDynamicArrayAllocator, a) {
	;
}

/* Constructor for type object. */
JsonEntity::JsonEntity(const sgdc::Map< JsonEntity >& o)
:	JsonEntity(&defaultMapAllocator, o) {
	;
}

/* Constructor for type string with specified allocator. */
JsonEntity::JsonEntity(
	sgdm::IAllocator< std::string >* stringAllocator,
	const std::string& s)
:	type(STRING),
	stringAllocator(stringAllocator) {
	data.s = stringAllocator->allocate(1);
	stringAllocator->construct(data.s, std::string(s));
}

/* Constructor for type array with specified allocator. */
JsonEntity::JsonEntity(
	sgdm::IAllocator< sgdc::DynamicArray< JsonEntity > >* dynamicArrayAllocator,
	const sgdc::DynamicArray< JsonEntity >& a)
:	type(ARRAY),
	dynamicArrayAllocator(dynamicArrayAllocator) {
	data.a = dynamicArrayAllocator->allocate(1);
	dynamicArrayAllocator->construct(data.a, a);
}

/* Constructor for type object with specified allocator. */
JsonEntity::JsonEntity(
	sgdm::IAllocator< sgdc::Map< JsonEntity > >* mapAllocator,
	const sgdc::Map< JsonEntity >& o)
:	type(OBJECT),
	mapAllocator(mapAllocator) {
	data.o = mapAllocator->allocate(1);
	mapAllocator->construct(data.o, o);
}

/* Default destructor. */
JsonEntity::~JsonEntity() {
	if (type == STRING && data.s != nullptr) {
		stringAllocator->deallocate(data.s, 1);
	}
	else if (type == ARRAY && data.a != nullptr) {
		dynamicArrayAllocator->deallocate(data.a, 1);
	}
	else if (type == OBJECT && data.o != nullptr) {
		mapAllocator->deallocate(data.o, 1);
	}
}

/* Copy assignment operator. */
JsonEntity& JsonEntity::operator = (const JsonEntity& jsonEntity) {
	type = jsonEntity.type;
	if (type == BOOL) {
		data.b = jsonEntity.data.b;
	}
	else if (type == INT) {
		data.i = jsonEntity.data.i;
	}
	else if (type == DOUBLE) {
		data.d = jsonEntity.data.d;
	}
	else if (type == STRING) {
		stringAllocator = jsonEntity.stringAllocator;
		data.s = stringAllocator->allocate(1);
		stringAllocator->construct(data.s, *jsonEntity.data.s);
	}
	else if (type == ARRAY) {
		dynamicArrayAllocator = jsonEntity.dynamicArrayAllocator;
		data.a = dynamicArrayAllocator->allocate(1);
		dynamicArrayAllocator->construct(data.a, *jsonEntity.data.a);
	}
	else if (type == OBJECT) {
		mapAllocator = jsonEntity.mapAllocator;
		data.o = mapAllocator->allocate(1);
		mapAllocator->construct(data.o, *jsonEntity.data.o);
	}
}

/* Move assignment operator. */
JsonEntity& JsonEntity::operator = (JsonEntity&& jsonEntity) {
	type = jsonEntity.type;
	if (type == BOOL) {
		data.b = jsonEntity.data.b;
	}
	else if (type == INT) {
		data.i = jsonEntity.data.i;
	}
	else if (type == DOUBLE) {
		data.d = jsonEntity.data.d;
	}
	else if (type == STRING) {
		stringAllocator = jsonEntity.stringAllocator;
		data.s = std::move(jsonEntity.data.s);
		jsonEntity.data.s = nullptr;
	}
	else if (type == ARRAY) {
		dynamicArrayAllocator = jsonEntity.dynamicArrayAllocator;
		data.a = std::move(jsonEntity.data.a);
		jsonEntity.data.a = nullptr;
	}
	else if (type == OBJECT) {
		mapAllocator = jsonEntity.mapAllocator;
		data.o = std::move(jsonEntity.data.o);
		jsonEntity.data.o = nullptr;
	}
}

/* Return whether the type is error. */
const bool JsonEntity::isError() const {
	return type == ERROR;
}

/* Return whether the type is bool. */
const bool JsonEntity::isBool() const {
	return type == BOOL;
}

/* Return whether the type is int. */
const bool JsonEntity::isInt() const {
	return type == INT;
}

/* Return whether the type is double. */
const bool JsonEntity::isDouble() const {
	return type == DOUBLE;
}

/* Return whether the type is string. */
const bool JsonEntity::isString() const {
	return type == STRING;
}

/* Return whether the type is array. */
const bool JsonEntity::isArray() const {
	return type == ARRAY;
}

/* Return whether the type is object. */
const bool JsonEntity::isObject() const {
	return type == OBJECT;
}

/* Return the type. */
const JsonEntity::Types JsonEntity::getType() const {
	return type;
}

/* Return as bool. */
const bool JsonEntity::asBool() const {
	return data.b;
}

/* Return as int. */
const int JsonEntity::asInt() const {
	return data.i;
}

/* Return as double. */
const double JsonEntity::asDouble() const {
	return data.d;
}

/* Return as string. */
const std::string& JsonEntity::asString() const {
	return *data.s;
}

/* Return as array. */
const sgdc::DynamicArray< JsonEntity >& JsonEntity::asArray() const {
	return *data.a;
}

/* Return as object. */
const sgdc::Map< JsonEntity >& JsonEntity::asObject() const {
	return *data.o;
}

}
}