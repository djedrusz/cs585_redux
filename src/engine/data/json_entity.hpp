/*
	Dominik Jedruszczak

	json_entity.hpp
	Declaration of the "JsonEntity" class.
*/

#ifndef INCLUDED_JSON_ENTITY
#define INCLUDED_JSON_ENTITY

#include "../containers/dynamic_array.hpp"
#include "../containers/map.hpp"

namespace StevensDev {
namespace sgdd { /* Stevens Game Development Data. */

/* A JSON entity. */
class JsonEntity {
public:
	/* The possible JSON entity types. */
	enum Types {
		ERROR,
		BOOL,
		INT,
		DOUBLE,
		STRING,
		ARRAY,
		OBJECT
	};

	/* The data of a JSON entity. 
	union Data {
		/* Data member(s). 
		bool b;
		int i;
		double d;
		std::string* s;
		sgdc::DynamicArray< JsonEntity >* a;
		sgdc::Map< JsonEntity >* o;
		/* Constructor(s). 
		Data(); // Default constructor.
		Data(bool b); // Boolean constructor.
		Data(int i); // Integer constructor.
		Data(double d); // Double constructor.
		Data(std::string* s); // String constructor.
		Data(sgdc::DynamicArray< JsonEntity >* a); // Array constructor.
		//Data(sgdc::Map< JsonEntity >* o); // Object constructor.
		/* Destructor(s). 
		~Data() { ; }; // Default destructor.
	};*/

	private:
		/* Data member(s). */
		Types type; // The type.
		//Data data; // The data.
		bool b;
		int i;
		double d;
		std::string* s;
		sgdc::DynamicArray< JsonEntity >* a;
		sgdc::Map< JsonEntity >* o;
	public:
		/* Constructor. */
		JsonEntity(); // Default constructor.
		JsonEntity(bool b); // Constructor for type bool.
		JsonEntity(int i); // Constructor for type int.
		JsonEntity(double d); // Constructor for type double.
		JsonEntity(std::string* s); // Constructor for type string.
		JsonEntity(sgdc::DynamicArray< JsonEntity >* a); // Constructor for type array.
		JsonEntity(sgdc::Map< JsonEntity >* o); // Constructor for type object.
		/* Destructor(s). */
		//~JsonEntity(); // Default destructor.
		/* Function(s). */
		const bool isError() const; // Return whether the type is error.
		const bool isBool() const; // Return whether the type is bool.
		const bool isInt() const; // Return whether the type is int.
		const bool isDouble() const; // Return whether the type is double.
		const bool isString() const; // Return whether the type is string.
		const bool isArray() const; // Return whether the type is array.
		const bool isObject() const; // Return whether the type is object.
		const Types getType() const; // Return the type.
		const bool asBool() const; // Return as bool.
		const int asInt() const; // Return as int.
		const double asDouble() const; // Return as double.
		const std::string* asString() const; // Return as string.
		const sgdc::DynamicArray< JsonEntity >* asArray() const; // Return as array.
		const sgdc::Map< JsonEntity >* asObject() const; // Return as object.
};

}
}

#endif