/*
	Dominik Jedruszczak
	
	json_parser.cpp
	Implementation of the "JsonParser" class.
*/

#include "json_parser.hpp"

namespace StevensDev {
namespace sgdd { /* Stevens Game Development. */

/* Initialize the default JSON entity allocator. */
sgdm::DefaultAllocator< JsonEntity > JsonParser::defaultJsonEntityAllocator;

/* TODO. */
JsonParser::Parse JsonParser::parseEntity(
	sgdm::IAllocator< std::string >* stringAllocator,
	sgdm::IAllocator< sgdc::DynamicArray< JsonEntity > >* dynamicArrayAllocator,
	sgdm::IAllocator< sgdc::Map< JsonEntity > >* mapAllocator,
	sgdm::IAllocator< JsonEntity >* jsonEntityAllocator,
	const std::string& json,
	unsigned int index) {

	std::cout << "Parse entity at index " << index << std::endl;

	/* Flush whitespaces. */
	while (json[index] == ASCII_TAB ||
		json[index] == ASCII_NEW_LINE ||
		json[index] == ASCII_CARRIAGE_RETURN ||
		json[index] == ASCII_SPACE) {
		std::cout << "Whitespace" << std::endl;
		index++;
	}

	/* Boolean. */
	if (json[index] == 't' || json[index] == 'f') {
		std::cout << "Parsing boolean." << std::endl;
		return parseBool(jsonEntityAllocator, json, index);
	}
	/* Number. */
	else if (json[index] == '-' ||
				(json[index] >= '0' && json[index] <= '9')) {
		std::cout << "Parsing number." << std::endl;
		return parseNumber(jsonEntityAllocator, json, index);
	}
	/* String. */
	else if (json[index] == '"') {
		std::cout << "Parsing string." << std::endl;
		return parseString(stringAllocator, jsonEntityAllocator, json, index);
	}
	/* Array. */
	else if (json[index] == '[') {
		std::cout << "Parsing array." << std::endl;
		return parseArray(dynamicArrayAllocator, jsonEntityAllocator, json, index);
	}
	/* Object. */
	else if (json[index] == '{') {
		std::cout << "Parsing object." << std::endl;
		return parseObject(mapAllocator, jsonEntityAllocator, json, index);
	}
	/* Invalid JSON. */
	else {
		return Parse(NULL, index);
	}
}

/* TODO. */
JsonParser::Parse JsonParser::parseBool(
	sgdm::IAllocator< JsonEntity >* jsonEntityAllocator,
	const std::string& json,
	unsigned int index) {

	JsonEntity* jsonEntity = jsonEntityAllocator->allocate(1);

	/* True. */
	if (json[index] == 't') {
		index++;
		if (json[index++] == 'r' && /* Read rest of 'true'. */
			json[index++] == 'u' &&
			json[index] == 'e') {
			jsonEntityAllocator->construct(jsonEntity, JsonEntity(true));
		}
		else {
			jsonEntityAllocator->construct(jsonEntity, JsonEntity());
		}
	}
	/* False. */
	else { /* Must begin with either 't' or 'f' to trigger function. */
		index++;
		if (json[index++] == 'a' && /* Read rest of 'false'. */
			json[index++] == 'l' &&
			json[index++] == 's' &&
			json[index] == 'e') {
			jsonEntityAllocator->construct(jsonEntity, JsonEntity(false));
		}
		else {
			jsonEntityAllocator->construct(jsonEntity, JsonEntity());
		}
	}

	return Parse(jsonEntity, index);
}

/* TODO. */
JsonParser::Parse JsonParser::parseNumber(
	sgdm::IAllocator< JsonEntity >* jsonEntityAllocator,
	const std::string& json,
	unsigned int index) {

	JsonEntity* jsonEntity = jsonEntityAllocator->allocate(1);
	unsigned int startingIndex = index;


	/* Optional negative flag. */
	if (json[index] == '-') {
		index++;
	}

	/* If number starts with zero, cannot be followed by any digits. */
	if (json[index] == '0') {
		index++;
	}
	else if (json[index] >= '1' && json[index] <= '9') { /* Otherwise, number must begin with non-zero digit. */
		index++;
		while (json[index] >= '0' && json[index] <= '9') { /* Number can then loop with any digit. */
			index++;
		}
	}

	/* If decimal point is read, number becomes double. */
	if (json[index] == '.') {
		index++;
		while (json[index] >= '0' && json[index] <= '9') { /* Loop decimal mantissa. */
			index++;
		}
		if (json[index] == 'e' || json[index] == 'E') { /* Read exponent. */
			index++;
			if (json[index] == '+' || /* Exponent can be negative or have optional positive flag. */
				json[index] == '-' ||
				(json[index] >= '0' && json[index] <= '9')) {
				index++;
				while (json[index] >= '0' && json[index] <= '9') { /* Loop (rest) of exponent digits. */
					index++;
				}
				/* Finish reading exponent and double. */
				index--;
				jsonEntityAllocator->construct(jsonEntity, JsonEntity(atof(std::string(json, startingIndex, startingIndex - index).c_str())));
			}
			else { /* Invalid exponent format. */
				jsonEntityAllocator->construct(jsonEntity, JsonEntity());
			}
		}
		else { /* If number has no exponent, finish reading as double. */
			jsonEntityAllocator->construct(jsonEntity, JsonEntity(atof(std::string(json, startingIndex, startingIndex - index).c_str())));
		}
	}
	else { /* If number has no decimal, read as integer. */
		index--;
		jsonEntityAllocator->construct(jsonEntity, JsonEntity(atoi(std::string(json, startingIndex, startingIndex - index).c_str())));
		return Parse(jsonEntity, index);
	}

	return Parse(jsonEntity, index);
}

/* TODO. */
JsonParser::Parse JsonParser::parseString(
	sgdm::IAllocator< std::string >* stringAllocator,
	sgdm::IAllocator< JsonEntity >* jsonEntityAllocator,
	const std::string& json,
	unsigned int index) {

	JsonEntity* jsonEntity = jsonEntityAllocator->allocate(1);
	unsigned int startingIndex = index;

	index++; // Skip over parenthesis.
	while (true) {
		if (json[index] == '"') { /* End of string. */
			if (stringAllocator == nullptr) {
				jsonEntityAllocator->construct(jsonEntity, JsonEntity(std::string(json, startingIndex + 1, index - 1)));
			}
			else {
				jsonEntityAllocator->construct(jsonEntity, JsonEntity(stringAllocator, std::string(json, startingIndex + 1, index - 1)));
			}


			break;
		}
		else if (json[index] == '\\') { /* Escape. */
			index++;
			if (json[index] == '"' || /* Special characters. */
				json[index] == '\\' ||
				json[index] == '/' ||
				json[index] == 'b' ||
				json[index] == 'f' ||
				json[index] == 'n' ||
				json[index] == 'r' ||
				json[index] == 't' ) {
				index++;
			}
			else if (json[index] == 'u') { /* Hexadecimal character. */
				index++;
				if (((json[index] >= '0' && /* Four hexadecimal digits. */
					json[index] <= '9') ||
					(json[index] >= 'A' &&
					json[index++] <= 'F')) &&
					((json[index] >= '0' && /* Four hexadecimal digits. */
					json[index] <= '9') ||
					(json[index] >= 'A' &&
					json[index++] <= 'F')) &&
					((json[index] >= '0' && /* Four hexadecimal digits. */
					json[index] <= '9') ||
					(json[index] >= 'A' &&
					json[index++] <= 'F')) &&
					((json[index] >= '0' && /* Four hexadecimal digits. */
					json[index] <= '9') ||
					(json[index] >= 'A' &&
					json[index] <= 'F'))) {
					index++;
				}
				else { /* Hexadecimal character not followed by four hexadecimal digits. */
					jsonEntityAllocator->construct(jsonEntity, JsonEntity());
					break;
				}
			}
			else { /* Invalid special character. */
				jsonEntityAllocator->construct(jsonEntity, JsonEntity());
				break;
			}
		}
		else { /* Regular character. */
			index++;
		}
	}

	return Parse(jsonEntity, index);
}

/* TODO. */
JsonParser::Parse JsonParser::parseArray(
	sgdm::IAllocator< sgdc::DynamicArray< JsonEntity > >* dynamicArrayAllocator,
	sgdm::IAllocator< JsonEntity >* jsonEntityAllocator,
	const std::string& json,
	unsigned int index) {

	JsonEntity* jsonEntity = jsonEntityAllocator->allocate(1);
	return Parse(jsonEntity, index);
}

/* TODO. */
JsonParser::Parse JsonParser::parseObject(
	sgdm::IAllocator< sgdc::Map< JsonEntity > >* mapAllocator,
	sgdm::IAllocator< JsonEntity >* jsonEntityAllocator,
	const std::string& json,
	unsigned int index) {

	JsonEntity* jsonEntity = jsonEntityAllocator->allocate(1);
	return Parse(jsonEntity, index);
}

/* Parse the specified JSON string into a JSON entity. */
JsonEntity* JsonParser::parse(const std::string& json) {
	return parse(
		nullptr,
		nullptr,
		nullptr,
		&defaultJsonEntityAllocator,
		json);
}

/* Parse the specified JSON string into a JSON entity with the specified allocator. */
JsonEntity* JsonParser::parse(
	sgdm::IAllocator< JsonEntity >* jsonEntityAllocator,
	const std::string& json) {

	return parse(
		nullptr,
		nullptr,
		nullptr,
		jsonEntityAllocator,
		json);
}

/* Parse the specified JSON string into a JSON entity with the specified allocators. */
JsonEntity* JsonParser::parse(
	sgdm::IAllocator< std::string >* stringAllocator,
	sgdm::IAllocator< sgdc::DynamicArray< JsonEntity > >* dynamicArrayAllocator,
	sgdm::IAllocator< sgdc::Map< JsonEntity > >* mapAllocator,
	sgdm::IAllocator< JsonEntity >* jsonEntityAllocator,
	const std::string& json) {

	return parseEntity(
		stringAllocator,
		dynamicArrayAllocator,
		mapAllocator,
		jsonEntityAllocator,
		json,
		0).jsonEntity;
}

}
}