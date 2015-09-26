/*
	Dominik Jedruszczak

	json_entity.hpp
	Declaration of the "JsonValue" class.
*/

#ifndef INCLUDED_JSON_VALUE
#define INCLUDED_JSON_VALUE

#include "../containers/dynamic_array.hpp"
#include "../containers/map.hpp"

namespace StevensDev {
namespace sgdd { /* Stevens Game Development Data. */

/* A JSON value. */
class JsonValue {
public:
	/* The possible JSON value types. */
	enum Types {
		ERROR,
		BOOL,
		INT,
		DOUBLE,
		STRING,
		ARRAY,
		OBJECT
	};

	/* The data of a JSON value. */
	union Data {
		/* Data member(s). */
		bool b;
		int i;
		double d;
		std::string* s;
		sgdc::DynamicArray< JsonValue >* a;
		sgdc::Map< JsonValue >* o;
	};

	private:
		/* Data member(s). */
		static sgdm::DefaultAllocator< std::string > defaultStringAllocator;
		static sgdm::DefaultAllocator< sgdc::DynamicArray< JsonValue > > defaultDynamicArrayAllocator;
		static sgdm::DefaultAllocator< sgdc::MapNode< JsonValue > > defaultMapNodeAllocator;
		static sgdm::DefaultAllocator< sgdc::Map< JsonValue > > defaultMapAllocator;
		sgdm::IAllocator< std::string >* stringAllocator;
		sgdm::IAllocator< sgdc::DynamicArray< JsonValue > >* dynamicArrayAllocator;
		sgdm::IAllocator< sgdc::Map< JsonValue > >* mapAllocator;
		Types type; // The type.
		Data data; // The data.
	public:
		/* Constructor(s). */
		JsonValue(const JsonValue& jsonEntity); // Copy constructor.
		JsonValue(JsonValue&& jsonEntity); // Move constructor.
		JsonValue(); // Constructor for type error.
		JsonValue(bool b); // Constructor for type bool.
		JsonValue(int i); // Constructor for type int.
		JsonValue(double d); // Constructor for type double.
		JsonValue(const std::string& s); // Constructor for type string.
		JsonValue(const sgdc::DynamicArray< JsonValue >& a); // Constructor for type array.
		JsonValue(const sgdc::Map< JsonValue >& o); // Constructor for type object.
		JsonValue( // Constructor for type string with specified allocator.
			sgdm::IAllocator< std::string >* stringAllocator,
			const std::string& s);
		JsonValue( // Constructor for type array with specified allocator.
			sgdm::IAllocator< sgdc::DynamicArray< JsonValue > >* dynamicArrayAllocator,
			const sgdc::DynamicArray< JsonValue >& a);
		JsonValue( // Constructor for type object with specified allocator.
			sgdm::IAllocator< sgdc::Map< JsonValue > >* mapAllocator,
			const sgdc::Map< JsonValue >& o);
		/* Destructor(s). */
		~JsonValue(); // Default destructor.
		/* Operator(s). */
		JsonValue& operator = (const JsonValue& jsonEntity); // Copy assignment operator.
		JsonValue& operator = (JsonValue&& jsonEntity); // Move assignment operator.
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
		const std::string& asString() const; // Return as string.
		const sgdc::DynamicArray< JsonValue >& asArray() const; // Return as array.
		const sgdc::Map< JsonValue >& asObject() const; // Return as object.
};

}
}

#endif