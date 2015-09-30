/*
	Dominik Jedruszczak

	json_parser.hpp
	Declaration of the "JsonParser" class.
*/

#ifndef INCLUDED_JSON_PARSER
#define INCLUDED_JSON_PARSER

#include "../memory/default_allocator.hpp"
#include "json_value.hpp"

#define ASCII_TAB 9
#define ASCII_NEW_LINE 10
#define ASCII_CARRIAGE_RETURN 13
#define ASCII_SPACE 32

namespace StevensDev {
namespace sgdd { /* Stevens Game Development Data. */

/* A JSON parser. */
class JsonParser {
	/* Return of a parse. */
	struct Parse {
		JsonValue* jsonValue; // The JSON value parsed.
		unsigned int index; // The index at which the parse returned.
		Parse(JsonValue* jsonValue, unsigned int index)
		:	jsonValue(jsonValue),
			index(index) {
			;
		}
	};

	private:
		/* Data member(s). */
		static sgdm::DefaultAllocator< JsonValue > defaultJsonValueAllocator; // Default JSON value allocator.
		/* Functions(s). */
		static Parse parseEntity( // TODO.
			sgdm::IAllocator< std::string >* stringAllocator,
			sgdm::IAllocator< sgdc::DynamicArray< JsonValue > >* dynamicArrayAllocator,
			sgdm::IAllocator< sgdc::MapNode< JsonValue > >* mapNodeAllocator,
			sgdm::IAllocator< sgdc::Map< JsonValue > >* mapAllocator,
			sgdm::IAllocator< JsonValue >* jsonValueAllocator,
			const std::string& json,
			unsigned int index);
		static Parse parseBool(sgdm::IAllocator< JsonValue >* allocator, const std::string& json, unsigned int index); // TODO.
		static Parse parseNumber(sgdm::IAllocator< JsonValue >* allocator, const std::string& json, unsigned int index); // TODO.
		static Parse parseString( // TODO.
			sgdm::IAllocator< std::string >* stringAllocator,
			sgdm::IAllocator< JsonValue >* jsonValueAllocator,
			const std::string& json,
			unsigned int index);
		static Parse parseArray( // TODO.
			sgdm::IAllocator< std::string >* stringAllocator,
			sgdm::IAllocator< sgdc::DynamicArray< JsonValue > >* dynamicArrayAllocator,
			sgdm::IAllocator< sgdc::MapNode< JsonValue > >* mapNodeAllocator,
			sgdm::IAllocator< sgdc::Map< JsonValue > >* mapAllocator,
			sgdm::IAllocator< JsonValue >* jsonValueAllocator,
			const std::string& json,
			unsigned int index);
		static Parse parseObject( // TODO.
			sgdm::IAllocator< std::string >* stringAllocator,
			sgdm::IAllocator< sgdc::DynamicArray< JsonValue > >* dynamicArrayAllocator,
			sgdm::IAllocator< sgdc::MapNode< JsonValue > >* mapNodeAllocator,
			sgdm::IAllocator< sgdc::Map< JsonValue > >* mapAllocator,
			sgdm::IAllocator< JsonValue >* jsonValueAllocator,
			const std::string& json,
			unsigned int index);
	public:
		/* Function(s). */
		static JsonValue* parse(const std::string& json); // Parse the specified JSON into a JSON value.
		static JsonValue* parse(sgdm::IAllocator< JsonValue >* jsonValueAllocator, const std::string& json); // Parse the specified JSON into a JSON value with the specified allocator.
		static JsonValue* parse(
			sgdm::IAllocator< std::string >* stringAllocator,
			sgdm::IAllocator< sgdc::DynamicArray< JsonValue > >* dynamicArrayAllocator,
			sgdm::IAllocator< sgdc::MapNode< JsonValue > >* mapNodeAllocator,
			sgdm::IAllocator< sgdc::Map< JsonValue > >* mapAllocator,
			sgdm::IAllocator< JsonValue >* jsonValueAllocator,
			const std::string& json);
};

}
}

#endif