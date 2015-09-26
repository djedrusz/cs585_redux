/*
	Dominik Jedruszczak

	json_entity.cpp
	Implementation of the "JsonValue" class.
*/

#include "json_value.hpp"

namespace StevensDev {
namespace sgdd { /* Stevens Game Development Data. */

/* Initialize static default allocators. */
sgdm::DefaultAllocator< std::string > JsonValue::defaultStringAllocator;
sgdm::DefaultAllocator< sgdc::DynamicArray< JsonValue > > JsonValue::defaultDynamicArrayAllocator;
sgdm::DefaultAllocator< sgdc::Map< JsonValue > > JsonValue::defaultMapAllocator;

/* Copy constructor. */
JsonValue::JsonValue(const JsonValue& jsonEntity)
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
JsonValue::JsonValue(JsonValue&& jsonEntity)
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
JsonValue::JsonValue()
:	type(ERROR) {
	data.b = false;
}

/* Constructor for type bool. */
JsonValue::JsonValue(bool b)
:	type(BOOL) {
	data.b = b;
}

/* Constructor for type int. */
JsonValue::JsonValue(int i)
:	type(INT) {
	data.i = i;
}

/* Constructor for type double. */
JsonValue::JsonValue(double d)
:	type(DOUBLE) {
	data.d = d;
}

/* Constructor for type string. */
JsonValue::JsonValue(const std::string& s)
:	JsonValue(&defaultStringAllocator, s) {
	;
}

/* Constructor for type array. */
JsonValue::JsonValue(const sgdc::DynamicArray< JsonValue >& a)
:	JsonValue(&defaultDynamicArrayAllocator, a) {
	;
}

/* Constructor for type object. */
JsonValue::JsonValue(const sgdc::Map< JsonValue >& o)
:	JsonValue(&defaultMapAllocator, o) {
	;
}

/* Constructor for type string with specified allocator. */
JsonValue::JsonValue(
	sgdm::IAllocator< std::string >* stringAllocator,
	const std::string& s)
:	type(STRING),
	stringAllocator(stringAllocator) {
	data.s = stringAllocator->allocate(1);
	stringAllocator->construct(data.s, std::string(s));
}

/* Constructor for type array with specified allocator. */
JsonValue::JsonValue(
	sgdm::IAllocator< sgdc::DynamicArray< JsonValue > >* dynamicArrayAllocator,
	const sgdc::DynamicArray< JsonValue >& a)
:	type(ARRAY),
	dynamicArrayAllocator(dynamicArrayAllocator) {
	data.a = dynamicArrayAllocator->allocate(1);
	dynamicArrayAllocator->construct(data.a, a);
}

/* Constructor for type object with specified allocator. */
JsonValue::JsonValue(
	sgdm::IAllocator< sgdc::Map< JsonValue > >* mapAllocator,
	const sgdc::Map< JsonValue >& o)
:	type(OBJECT),
	mapAllocator(mapAllocator) {
	data.o = mapAllocator->allocate(1);
	mapAllocator->construct(data.o, o);
}

/* Default destructor. */
JsonValue::~JsonValue() {
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
JsonValue& JsonValue::operator = (const JsonValue& jsonEntity) {
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
JsonValue& JsonValue::operator = (JsonValue&& jsonEntity) {
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
const bool JsonValue::isError() const {
	return type == ERROR;
}

/* Return whether the type is bool. */
const bool JsonValue::isBool() const {
	return type == BOOL;
}

/* Return whether the type is int. */
const bool JsonValue::isInt() const {
	return type == INT;
}

/* Return whether the type is double. */
const bool JsonValue::isDouble() const {
	return type == DOUBLE;
}

/* Return whether the type is string. */
const bool JsonValue::isString() const {
	return type == STRING;
}

/* Return whether the type is array. */
const bool JsonValue::isArray() const {
	return type == ARRAY;
}

/* Return whether the type is object. */
const bool JsonValue::isObject() const {
	return type == OBJECT;
}

/* Return the type. */
const JsonValue::Types JsonValue::getType() const {
	return type;
}

/* Return as bool. */
const bool JsonValue::asBool() const {
	return data.b;
}

/* Return as int. */
const int JsonValue::asInt() const {
	return data.i;
}

/* Return as double. */
const double JsonValue::asDouble() const {
	return data.d;
}

/* Return as string. */
const std::string& JsonValue::asString() const {
	return *data.s;
}

/* Return as array. */
const sgdc::DynamicArray< JsonValue >& JsonValue::asArray() const {
	return *data.a;
}

/* Return as object. */
const sgdc::Map< JsonValue >& JsonValue::asObject() const {
	return *data.o;
}

}
}