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
	sgdm::IAllocator< sgdc::MapNode< JsonEntity > >* mapNodeAllocator,
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
		return parseArray(
			stringAllocator,
			dynamicArrayAllocator,
			mapNodeAllocator,
			mapAllocator,
			jsonEntityAllocator,
			json,
			index);
	}
	/* Object. */
	else if (json[index] == '{') {
		std::cout << "Parsing object." << std::endl;
		return parseObject(
			stringAllocator,
			dynamicArrayAllocator,
			mapNodeAllocator,
			mapAllocator,
			jsonEntityAllocator,
			json,
			index);
	}
	/* Invalid JSON. */
	else {
		JsonEntity* jsonEntity = jsonEntityAllocator->allocate(1);
		jsonEntityAllocator->construct(jsonEntity, JsonEntity());
		return Parse(jsonEntity, index);
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
				std::cout << "Read double from " << std::string(json, startingIndex, startingIndex - index) << std::endl;
				jsonEntityAllocator->construct(jsonEntity, JsonEntity(atof(std::string(json, startingIndex, startingIndex - index).c_str())));
				index--;
				return Parse(jsonEntity, index);
			}
			else { /* Invalid exponent format. */
				jsonEntityAllocator->construct(jsonEntity, JsonEntity());
				return Parse(jsonEntity, index);
			}
		}
		else { /* If number has no exponent, finish reading as double. */
			std::cout << "Read double from " << std::string(json, startingIndex, startingIndex - index) << std::endl;
			jsonEntityAllocator->construct(jsonEntity, JsonEntity(atof(std::string(json, startingIndex, startingIndex - index).c_str())));
			index--;
			return Parse(jsonEntity, index);
		}
	}
	else { /* If number has no decimal, read as integer. */
		std::cout << "Read integer from " << std::string(json, startingIndex, startingIndex - index) << std::endl;
		jsonEntityAllocator->construct(jsonEntity, JsonEntity(atoi(std::string(json, startingIndex, startingIndex - index).c_str())));
		index--;
		return Parse(jsonEntity, index);
	}
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
				jsonEntityAllocator->construct(jsonEntity, JsonEntity(std::string(json, startingIndex + 1, index - startingIndex - 1)));
			}
			else {
				jsonEntityAllocator->construct(jsonEntity, JsonEntity(stringAllocator, std::string(json, startingIndex + 1, index - startingIndex - 1)));
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
					json[index] <= 'F')) &&
					((json[index + 1] >= '0' && /* Four hexadecimal digits. */
					json[index + 1] <= '9') ||
					(json[index + 1] >= 'A' &&
					json[index + 1] <= 'F')) &&
					((json[index + 2] >= '0' && /* Four hexadecimal digits. */
					json[index + 2] <= '9') ||
					(json[index + 2] >= 'A' &&
					json[index + 2] <= 'F')) &&
					((json[index + 3] >= '0' && /* Four hexadecimal digits. */
					json[index + 3] <= '9') ||
					(json[index + 3] >= 'A' &&
					json[index + 3] <= 'F'))) {
					index+=4;
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

	std::cout << "String's last is " << json[index] << " at " << index << std::endl;
	return Parse(jsonEntity, index);
}

/* TODO. */
JsonParser::Parse JsonParser::parseArray(

	sgdm::IAllocator< std::string >* stringAllocator,
	sgdm::IAllocator< sgdc::DynamicArray< JsonEntity > >* dynamicArrayAllocator,
	sgdm::IAllocator< sgdc::MapNode< JsonEntity > >* mapNodeAllocator,
	sgdm::IAllocator< sgdc::Map< JsonEntity > >* mapAllocator,
	sgdm::IAllocator< JsonEntity >* jsonEntityAllocator,
	const std::string& json,
	unsigned int index) {

	JsonEntity* jsonEntity = jsonEntityAllocator->allocate(1);
	sgdc::DynamicArray< JsonEntity > dynamicArray(jsonEntityAllocator);

	index++; // Skip over bracket.
	while (true) {
		if (json[index] == ']') {
			break;
		}
		else {
			Parse parse = parseEntity(stringAllocator, dynamicArrayAllocator, mapNodeAllocator, mapAllocator, jsonEntityAllocator, json, index);
			if (parse.jsonEntity->isError()) {
				jsonEntityAllocator->deallocate(parse.jsonEntity, 1);
				jsonEntityAllocator->construct(jsonEntity, JsonEntity());
				return Parse(jsonEntity, index);
			}
			
			JsonEntity je = *parse.jsonEntity;
			dynamicArray.append(je);
			
			jsonEntityAllocator->deallocate(parse.jsonEntity, 1);
			index = parse.index + 1;

			/* Flush whitespaces. */
			while (json[index] == ASCII_TAB ||
				json[index] == ASCII_NEW_LINE ||
				json[index] == ASCII_CARRIAGE_RETURN ||
				json[index] == ASCII_SPACE) {
				std::cout << "Whitespace" << std::endl;
				index++;
			}
			if (json[index] == ',') {
				index++;
			}
		}
	}

	jsonEntityAllocator->construct(jsonEntity, JsonEntity(dynamicArrayAllocator, dynamicArray));
	return Parse(jsonEntity, index);
}

/* TODO. */
JsonParser::Parse JsonParser::parseObject(
	sgdm::IAllocator< std::string >* stringAllocator,
	sgdm::IAllocator< sgdc::DynamicArray< JsonEntity > >* dynamicArrayAllocator,
	sgdm::IAllocator< sgdc::MapNode< JsonEntity > >* mapNodeAllocator,
	sgdm::IAllocator< sgdc::Map< JsonEntity > >* mapAllocator,
	sgdm::IAllocator< JsonEntity >* jsonEntityAllocator,
	const std::string& json,
	unsigned int index) {

	JsonEntity* jsonEntity = jsonEntityAllocator->allocate(1);
	sgdc::Map< JsonEntity > map(mapNodeAllocator, stringAllocator, jsonEntityAllocator);

	index++; // Skip over curly brace.
	while (true) {
		/* Flush whitespaces. */
		while (json[index] == ASCII_TAB ||
			json[index] == ASCII_NEW_LINE ||
			json[index] == ASCII_CARRIAGE_RETURN ||
			json[index] == ASCII_SPACE) {
			index++;
		}
		if (json[index] == '}') {
			break;
		}
		else {
			Parse stringParse = parseString(stringAllocator, jsonEntityAllocator, json, index);
			if (stringParse.jsonEntity->isError()) {
				jsonEntityAllocator->deallocate(stringParse.jsonEntity, 1);
				jsonEntityAllocator->construct(jsonEntity, JsonEntity());
				return Parse(jsonEntity, index);
			}

			index = stringParse.index + 1;
			std::cout << "Parsing after key: " << json[index] << " at index: " << index << std::endl;
			std::string key = stringParse.jsonEntity->asString();
			std::cout << "key is: " << key << std::endl;
			jsonEntityAllocator->deallocate(stringParse.jsonEntity, 1);

			/* Flush whitespaces. */
			while (json[index] == ASCII_TAB ||
				json[index] == ASCII_NEW_LINE ||
				json[index] == ASCII_CARRIAGE_RETURN ||
				json[index] == ASCII_SPACE) {
				index++;
			}
			if (json[index] != ':') {
				std::cout << "ERROR NO COLON at index " << index << std::endl;
			}
			index++;

			Parse entityParse = parseEntity(stringAllocator, dynamicArrayAllocator, mapNodeAllocator, mapAllocator, jsonEntityAllocator, json, index);
			if (entityParse.jsonEntity->isError()) {
				jsonEntityAllocator->deallocate(entityParse.jsonEntity, 1);
				jsonEntityAllocator->construct(jsonEntity, JsonEntity());
				return Parse(jsonEntity, index);
			}
			index = entityParse.index + 1;
			std::cout << "Parsing after value: " << json[index] << " at index: " << index << std::endl;
			JsonEntity value = *entityParse.jsonEntity;
			std::cout << "value is of type: " << value.getType() << std::endl;
			if (value.isInt()) {
				std::cout << "value is int and is " << value.asInt() << std::endl;
			}
			jsonEntityAllocator->deallocate(entityParse.jsonEntity, 1);

			map.put(key, value);

			/* Flush whitespaces. */
			while (json[index] == ASCII_TAB ||
				json[index] == ASCII_NEW_LINE ||
				json[index] == ASCII_CARRIAGE_RETURN ||
				json[index] == ASCII_SPACE) {
				index++;
			}
			if (json[index] == ',') {
				index++;
				/* Flush whitespaces. */
				while (json[index] == ASCII_TAB ||
					json[index] == ASCII_NEW_LINE ||
					json[index] == ASCII_CARRIAGE_RETURN ||
					json[index] == ASCII_SPACE) {
					index++;
				}
			}
			/* Flush whitespaces. */
			while (json[index] == ASCII_TAB ||
				json[index] == ASCII_NEW_LINE ||
				json[index] == ASCII_CARRIAGE_RETURN ||
				json[index] == ASCII_SPACE) {
				index++;
			}
		}
	}

	jsonEntityAllocator->construct(jsonEntity, JsonEntity(mapAllocator, map));
	return Parse(jsonEntity, index);
}

/* Parse the specified JSON string into a JSON entity. */
JsonEntity* JsonParser::parse(const std::string& json) {
	return parse(
		nullptr,
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
		nullptr,
		jsonEntityAllocator,
		json);
}

/* Parse the specified JSON string into a JSON entity with the specified allocators. */
JsonEntity* JsonParser::parse(
	sgdm::IAllocator< std::string >* stringAllocator,
	sgdm::IAllocator< sgdc::DynamicArray< JsonEntity > >* dynamicArrayAllocator,
	sgdm::IAllocator< sgdc::MapNode< JsonEntity > >* mapNodeAllocator,
	sgdm::IAllocator< sgdc::Map< JsonEntity > >* mapAllocator,
	sgdm::IAllocator< JsonEntity >* jsonEntityAllocator,
	const std::string& json) {

	return parseEntity(
		stringAllocator,
		dynamicArrayAllocator,
		mapNodeAllocator,
		mapAllocator,
		jsonEntityAllocator,
		json,
		0).jsonEntity;
}

}
}