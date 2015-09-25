/*
	Dominik Jedruszczak

	json_parser.hpp
	Declaration of the "JsonParser" class.
*/

#ifndef INCLUDED_JSON_PARSER
#define INCLUDED_JSON_PARSER

#include <iostream> // Remove later.
#include "../memory/default_allocator.hpp"
#include "json_entity.hpp"

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
		JsonEntity* jsonEntity; // The JSON entity parsed.
		unsigned int index; // The index at which the parse returned.
		Parse(JsonEntity* jsonEntity, unsigned int index)
		:	jsonEntity(jsonEntity),
			index(index) {
			;
		}
	};

	private:
		/* Data member(s). */
		static sgdm::DefaultAllocator< std::string > stringAllocator;
		static sgdm::DefaultAllocator< sgdc::DynamicArray< JsonEntity > > dynamicArrayAllocator;
		static sgdm::DefaultAllocator< sgdc::Map< JsonEntity > > mapAllocator;
		static sgdm::DefaultAllocator< JsonEntity > jsonEntityAllocator;
	public:
		/* Function(s). */
		static Parse parseEntity(
			sgdm::IAllocator< std::string >* stringAllocator,
			sgdm::IAllocator< sgdc::DynamicArray< JsonEntity > >* dynamicArrayAllocator,
			sgdm::IAllocator< sgdc::Map< JsonEntity > >* mapAllocator,
			sgdm::IAllocator< JsonEntity >* jsonEntityAllocator,
			const std::string& json,
			unsigned int index); // TODO.
		static Parse parseBool(sgdm::IAllocator< JsonEntity >* allocator, const std::string& json, unsigned int index); // TODO.
		static Parse parseNumber(sgdm::IAllocator< JsonEntity >* allocator, const std::string& json, unsigned int index); // TODO.
		static Parse parseString(
			sgdm::IAllocator< std::string >* stringAllocator,
			sgdm::IAllocator< JsonEntity >* jsonEntityAllocator,
			const std::string& json,
			unsigned int index); // TODO.
		static Parse parseArray(
			sgdm::IAllocator< sgdc::DynamicArray< JsonEntity > >* dynamicArrayAllocator,
			sgdm::IAllocator< JsonEntity >* jsonEntityAllocator,
			const std::string& json,
			unsigned int index); // TODO.
		static Parse parseObject(sgdm::IAllocator< JsonEntity >* allocator, const std::string& json, unsigned int index); // TODO.
		static JsonEntity* parse(const std::string& json); // Parse the specified JSON into a JSON entity.
		static JsonEntity* parse(sgdm::IAllocator< JsonEntity >* jsonEntityAllocator, const std::string& json); // Parse the specified JSON into a JSON entity with the specified allocator.
		static JsonEntity* parse(
			sgdm::IAllocator< std::string >* stringAllocator,
			sgdm::IAllocator< sgdc::DynamicArray< JsonEntity > >* dynamicArrayAllocator,
			sgdm::IAllocator< sgdc::Map< JsonEntity > >* mapAllocator,
			sgdm::IAllocator< JsonEntity >* jsonEntityAllocator,
			const std::string& json);
};

}
}

#endif