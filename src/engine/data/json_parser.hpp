/*
	Dominik Jedruszczak

	json_parser.hpp
	Declaration of the "JsonParser" class.
*/

#ifndef INCLUDED_JSON_PARSER
#define INCLUDED_JSON_PARSER

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
		static sgdm::DefaultAllocator< JsonEntity > defaultJsonEntityAllocator; // Default JSON entity allocator.
	public:
		/* Function(s). */
		static Parse parseEntity( // TODO.
			sgdm::IAllocator< std::string >* stringAllocator,
			sgdm::IAllocator< sgdc::DynamicArray< JsonEntity > >* dynamicArrayAllocator,
			sgdm::IAllocator< sgdc::MapNode< JsonEntity > >* mapNodeAllocator,
			sgdm::IAllocator< sgdc::Map< JsonEntity > >* mapAllocator,
			sgdm::IAllocator< JsonEntity >* jsonEntityAllocator,
			const std::string& json,
			unsigned int index);
		static Parse parseBool(sgdm::IAllocator< JsonEntity >* allocator, const std::string& json, unsigned int index); // TODO.
		static Parse parseNumber(sgdm::IAllocator< JsonEntity >* allocator, const std::string& json, unsigned int index); // TODO.
		static Parse parseString( // TODO.
			sgdm::IAllocator< std::string >* stringAllocator,
			sgdm::IAllocator< JsonEntity >* jsonEntityAllocator,
			const std::string& json,
			unsigned int index);
		static Parse parseArray( // TODO.
			sgdm::IAllocator< std::string >* stringAllocator,
			sgdm::IAllocator< sgdc::DynamicArray< JsonEntity > >* dynamicArrayAllocator,
			sgdm::IAllocator< sgdc::MapNode< JsonEntity > >* mapNodeAllocator,
			sgdm::IAllocator< sgdc::Map< JsonEntity > >* mapAllocator,
			sgdm::IAllocator< JsonEntity >* jsonEntityAllocator,
			const std::string& json,
			unsigned int index);
		static Parse parseObject( // TODO.
			sgdm::IAllocator< std::string >* stringAllocator,
			sgdm::IAllocator< sgdc::DynamicArray< JsonEntity > >* dynamicArrayAllocator,
			sgdm::IAllocator< sgdc::MapNode< JsonEntity > >* mapNodeAllocator,
			sgdm::IAllocator< sgdc::Map< JsonEntity > >* mapAllocator,
			sgdm::IAllocator< JsonEntity >* jsonEntityAllocator,
			const std::string& json,
			unsigned int index);
		static Parse parseObject(sgdm::IAllocator< JsonEntity >* allocator, const std::string& json, unsigned int index); // TODO.
		static JsonEntity* parse(const std::string& json); // Parse the specified JSON into a JSON entity.
		static JsonEntity* parse(sgdm::IAllocator< JsonEntity >* jsonEntityAllocator, const std::string& json); // Parse the specified JSON into a JSON entity with the specified allocator.
		static JsonEntity* parse(
			sgdm::IAllocator< std::string >* stringAllocator,
			sgdm::IAllocator< sgdc::DynamicArray< JsonEntity > >* dynamicArrayAllocator,
			sgdm::IAllocator< sgdc::MapNode< JsonEntity > >* mapNodeAllocator,
			sgdm::IAllocator< sgdc::Map< JsonEntity > >* mapAllocator,
			sgdm::IAllocator< JsonEntity >* jsonEntityAllocator,
			const std::string& json);
};

}
}

#endif