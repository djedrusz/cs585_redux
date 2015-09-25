/*
	Dominik Jedruszczak

	json_entity.cpp
	Implementation of the "JsonEntity" class.
*/

#include "json_entity.hpp"

namespace StevensDev {
namespace sgdd { /* Stevens Game Development Data. */

/* Default constructor. 
JsonEntity::Data::Data()
:	b(false) {
	;
}

/* Boolean constructor. 
JsonEntity::Data::Data(bool b)
:	b(b) {
	;
}

/* Integer constructor. 
JsonEntity::Data::Data(int i)
:	i(i) {
	;
}

/* Double constructor. 
JsonEntity::Data::Data(double d)
:	d(d) {
	;
}

/* String constructor. 
JsonEntity::Data::Data(std::string* s)
:	s(s) {
	;
}

/* Array constructor. 
JsonEntity::Data::Data(sdgc::DynamicArray< JsonEntity >* a)
:	a(a) {
	;
}

/* Object constructor. 
JsonEntity::Data::Data(sgdc::Map< JsonEntity >* o)
:	o(o) {
	;
}

/* Constructor for type int. */
JsonEntity::JsonEntity()
:	type(ERROR), b(false) {
	;
}

/* Constructor for type bool. */
JsonEntity::JsonEntity(bool b)
:	type(BOOL), b(b) {
	;
}

/* Constructor for type int. */
JsonEntity::JsonEntity(int i)
:	type(INT), i(i) {
	;
}

/* Constructor for type double. */
JsonEntity::JsonEntity(double d)
:	type(DOUBLE), d(d) {
	;
}

/* Constructor for type string. */
JsonEntity::JsonEntity(std::string* s)
:	type(STRING), s(s) {
	;
}

/* Constructor for type array. */
JsonEntity::JsonEntity(sgdc::DynamicArray< JsonEntity >* a)
:	type(ARRAY), a(a) {
	;
}

/* Constructor for type object. */
JsonEntity::JsonEntity(sgdc::Map< JsonEntity >* o)
:	type(OBJECT), o(o) {
	;
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
	return b;
}

/* Return as int. */
const int JsonEntity::asInt() const {
	return i;
}

/* Return as double. */
const double JsonEntity::asDouble() const {
	return d;
}

/* Return as string. */
const std::string* JsonEntity::asString() const {
	return s;
}

/* Return as array. */
const sgdc::DynamicArray< JsonEntity >* JsonEntity::asArray() const {
	return a;
}

/* Return as object. */
const sgdc::Map< JsonEntity >* JsonEntity::asObject() const {
	return o;
}

}
}