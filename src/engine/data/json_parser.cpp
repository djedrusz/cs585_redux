/*
	Dominik Jedruszczak
	
	json_parser.cpp
	Implementation of the "JsonParser" class.
*/

#include "json_parser.hpp"

namespace StevensDev {
namespace sgdd { /* Stevens Game Development. */

/* TODO. */
JsonParser::Parse JsonParser::parseEntity(sgdm::IAllocator< JsonEntity >* allocator, const std::string& json, unsigned int index) {
	std::cout << "Parse entity at index " << index << std::endl;
	/* Boolean. */
	if (json[index] == 't' || json[index] == 'f') {
		return parseBool(allocator, json, index);
	}
	/* String. */
	else if (json[index] == '"') {
		return parseString(allocator, json, index);
	}
	else {
		return Parse(NULL, index);
	}
}

/* TODO. */
JsonParser::Parse JsonParser::parseBool(sgdm::IAllocator< JsonEntity >* allocator, const std::string& json, unsigned int index) {
	std::cout << "Parsing bool at index " << index << std::endl;
	JsonEntity* jsonEntity = allocator->allocate(1);

	/* Parse 'true'. */
	if (json[index] == 't') {
		index++;
		if (json[index++] == 'r' &&
			json[index++] == 'u' &&
			json[index] == 'e') {
			std::cout << "Parsed true" << std::endl;
			allocator->construct(jsonEntity, JsonEntity(true));
		}
		else {
			std::cout << "Parsed true error" << std::endl;
			allocator->construct(jsonEntity, JsonEntity());
		}
	}
	/* Parse 'false'. */
	else if (json[index] == 'f') {
		index++;
		if (json[index++] == 'a' &&
			json[index++] == 'l' &&
			json[index++] == 's' &&
			json[index] == 'e') {
			std::cout << "Parsed false" << std::endl;
			allocator->construct(jsonEntity, JsonEntity(false));
		}
		else {
			std::cout << "Parsed false error" << std::endl;
			allocator->construct(jsonEntity, JsonEntity());
		}
	}
	else {
		std::cout << "Parsed impossible bool error" << std::endl;
		allocator->construct(jsonEntity, JsonEntity());
	}

	return Parse(jsonEntity, index);
}

/* TODO. */
JsonParser::Parse JsonParser::parseString(sgdm::IAllocator< JsonEntity >* allocator, const std::string& json, unsigned int index) {
	std::cout << "Parsing string at index " << index << std::endl;
	JsonEntity* jsonEntity = allocator->allocate(1);
	unsigned int startingIndex = 0;

	if (json[index] == '"') {
		index++;
		while (true) {
			if (json[index] == '"') {
				std::cout << "Parsed good string" << std::endl;
				allocator->construct(jsonEntity, JsonEntity(new std::string(json, startingIndex + 1, index - 1)));
				break;
			}
			else if (json[index++] == '\\') {
				if (json[index] == '\\' ||
					json[index] == '/' ||
					json[index] == 'b' ||
					json[index] == 'f' ||
					json[index] == 'n' ||
					json[index] == 'r' ||
					json[index] == 't' ||
					json[index] == 'u') {
					index++;
				}
				else {
					std::cout << "Parsed bad string" << std::endl;
					allocator->construct(jsonEntity, JsonEntity());
				}
			}
			else {
				index++;
			}
		}
	}

	return Parse(jsonEntity, index);
}

/* Parse the specified JSON string into a JSON entity. */
JsonEntity* JsonParser::parse(const std::string& json) {
	sgdm::DefaultAllocator< JsonEntity >* allocator = new sgdm::DefaultAllocator< JsonEntity >();
	unsigned int index = 0;

	/* Flush whitespaces. */
	while (json[index] == ASCII_TAB ||
		json[index] == ASCII_NEW_LINE ||
		json[index] == ASCII_CARRIAGE_RETURN ||
		json[index] == ASCII_SPACE) {
		std::cout << "Whitespace" << std::endl;
		index++;
	}
	std::cout << "Begin parse entity" << std::endl;
	return parseEntity(allocator, json, index).jsonEntity;

	std::cout << "Parse failed" << std::endl;
	return NULL;
}

/* Parse the specified JSON string into a JSON entity with the specified allocator. */
JsonEntity* JsonParser::parse(sgdm::IAllocator< JsonEntity >* allocator, const std::string& json) {
	;
}

}
}