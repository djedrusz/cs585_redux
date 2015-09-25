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

/* Copy constructor. 
JsonEntity::JsonEntity(const JsonEntity& jsonEntity) {
	std::cout << "Copy C" << std::endl;
	if (type == BOOL) {
		b = jsonEntity.b;
	}
	else if (type == INT) {
		i = jsonEntity.i;
	}
	else if (type == DOUBLE) {
		d = jsonEntity.d;
	}
	else if (type == STRING) {
		stringAllocator = jsonEntity.stringAllocator;
		s = stringAllocator->allocate(1);
		stringAllocator->construct(s, *jsonEntity.s);
	}
	else if (type == ARRAY) {
		dynamicArrayAllocator = jsonEntity.dynamicArrayAllocator;
		a = dynamicArrayAllocator->allocate(1);
		dynamicArrayAllocator->construct(a, *jsonEntity.a);
	}
	else if (type == OBJECT) {
		mapAllocator = jsonEntity.mapAllocator;
		o = mapAllocator->allocate(1);
		mapAllocator->construct(o, *jsonEntity.o);
	}
}

/* Move constructor. 
JsonEntity::JsonEntity(JsonEntity&& jsonEntity) {
	if (type == BOOL) {
		b = jsonEntity.b;
	}
	else if (type == INT) {
		i = jsonEntity.i;
	}
	else if (type == DOUBLE) {
		d = jsonEntity.d;
	}
	else if (type == STRING) {
		s = jsonEntity.s;
		jsonEntity.s = nullptr;
	}
	else if (type == ARRAY) {
		a = jsonEntity.a;
		jsonEntity.a = nullptr;
	}
	else if (type == OBJECT) {
		o = jsonEntity.o;
		jsonEntity.o = nullptr;
	}
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
JsonEntity::JsonEntity(const std::string& s)
:	JsonEntity(&defaultStringAllocator, s) {
	;
}

/* Constructor for type array. */
JsonEntity::JsonEntity(sgdc::DynamicArray< JsonEntity >* a)
:	JsonEntity(&defaultDynamicArrayAllocator, a) {
	;
}

/* Constructor for type object. */
JsonEntity::JsonEntity(sgdc::Map< JsonEntity >* o)
:	JsonEntity(&defaultMapAllocator, o) {
	;
}

JsonEntity::JsonEntity( /* Constructor for type string with specified allocator. */
	sgdm::IAllocator< std::string >* stringAllocator,
	const std::string& s)
:	type(STRING),
	stringAllocator(stringAllocator),
	s(stringAllocator->allocate(1)) {
	std::cout << "String in construtor: " << s <<std::endl;
	stringAllocator->construct(this->s, std::string(s));
	std::cout << "String after in-line constructor: " << asString() << std::endl << *asString() << std::endl;
}

JsonEntity::JsonEntity( /* Constructor for type array with specified allocator. */
	sgdm::IAllocator< sgdc::DynamicArray< JsonEntity > >* dynamicArrayAllocator,
	sgdc::DynamicArray< JsonEntity >* a)
:	type(ARRAY),
	dynamicArrayAllocator(dynamicArrayAllocator),
	a(dynamicArrayAllocator->allocate(1)) {
	dynamicArrayAllocator->construct(this->a, sgdc::DynamicArray< JsonEntity >());
}

JsonEntity::JsonEntity( /* Constructor for type object with specified allocator. */
	sgdm::IAllocator< sgdc::Map< JsonEntity > >* mapAllocator,
	sgdc::Map< JsonEntity >* o)
:	type(OBJECT),
	mapAllocator(mapAllocator),
	o(mapAllocator->allocate(1)) {
	mapAllocator->construct(this->o, sgdc::Map< JsonEntity >());
}

/* Default destructor. */
JsonEntity::~JsonEntity() {
	std::cout << "Destructor being called too soon!" << std::endl;
	if (type == STRING && s != NULL) {
		std::cout << "Dying!" << std::endl;
		//std::cout << "Deallocating memory location " << s << std::endl;
		//stringAllocator->deallocate(s, 1);
	}/*
	else if (type == ARRAY) {
		dynamicArrayAllocator->deallocate(a, 1);
	}
	else if (type == OBJECT) {
		mapAllocator->deallocate(o, 1);
	}*/
}

/* Copy assignment operator. 
JsonEntity& JsonEntity::operator = (const JsonEntity& jsonEntity) {
	if (type == BOOL) {
		b = jsonEntity.b;
	}
	else if (type == INT) {
		i = jsonEntity.i;
	}
	else if (type == DOUBLE) {
		d = jsonEntity.d;
	}
	else if (type == STRING) {
		stringAllocator = jsonEntity.stringAllocator;
		s = stringAllocator->allocate(1);
		stringAllocator->construct(s, *jsonEntity.s);
	}
	else if (type == ARRAY) {
		dynamicArrayAllocator = jsonEntity.dynamicArrayAllocator;
		a = dynamicArrayAllocator->allocate(1);
		dynamicArrayAllocator->construct(a, *jsonEntity.a);
	}
	else if (type == OBJECT) {
		mapAllocator = jsonEntity.mapAllocator;
		o = mapAllocator->allocate(1);
		mapAllocator->construct(o, *jsonEntity.o);
	}
}

/* Move assignment operator. 
JsonEntity& JsonEntity::operator = (JsonEntity&& jsonEntity) {
	if (type == BOOL) {
		b = jsonEntity.b;
	}
	else if (type == INT) {
		i = jsonEntity.i;
	}
	else if (type == DOUBLE) {
		d = jsonEntity.d;
	}
	else if (type == STRING) {
		stringAllocator = jsonEntity.stringAllocator;
		s = stringAllocator->allocate(1);
		stringAllocator->construct(s, *jsonEntity.s);
	}
	else if (type == ARRAY) {
		dynamicArrayAllocator = jsonEntity.dynamicArrayAllocator;
		a = dynamicArrayAllocator->allocate(1);
		dynamicArrayAllocator->construct(a, *jsonEntity.a);
	}
	else if (type == OBJECT) {
		mapAllocator = jsonEntity.mapAllocator;
		o = mapAllocator->allocate(1);
		mapAllocator->construct(o, *jsonEntity.o);
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
const std::string* JsonEntity::asString() {
	return s;
}

/* Return as array. */
const sgdc::DynamicArray< JsonEntity >* JsonEntity::asArray() {
	return a;
}

/* Return as object. */
const sgdc::Map< JsonEntity >* JsonEntity::asObject() {
	return o;
}

}
}