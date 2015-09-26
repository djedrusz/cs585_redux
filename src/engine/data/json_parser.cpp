/*
	Dominik Jedruszczak
	
	json_parser.cpp
	Implementation of the "JsonParser" class.
*/

#include "json_parser.hpp"

namespace StevensDev {
namespace sgdd { /* Stevens Game Development. */

/* Initialize the default JSON value allocator. */
sgdm::DefaultAllocator< JsonValue > JsonParser::defaultJsonValueAllocator;

/* TODO. */
JsonParser::Parse JsonParser::parseEntity(
	sgdm::IAllocator< std::string >* stringAllocator,
	sgdm::IAllocator< sgdc::DynamicArray< JsonValue > >* dynamicArrayAllocator,
	sgdm::IAllocator< sgdc::MapNode< JsonValue > >* mapNodeAllocator,
	sgdm::IAllocator< sgdc::Map< JsonValue > >* mapAllocator,
	sgdm::IAllocator< JsonValue >* jsonValueAllocator,
	const std::string& json,
	unsigned int index) {

	/* Flush whitespaces. */
	while (json[index] == ASCII_TAB ||
		json[index] == ASCII_NEW_LINE ||
		json[index] == ASCII_CARRIAGE_RETURN ||
		json[index] == ASCII_SPACE) {
		index++;
	}

	/* Boolean. */
	if (json[index] == 't' || json[index] == 'f') {
		return parseBool(jsonValueAllocator, json, index);
	}
	/* Number. */
	else if (json[index] == '-' ||
				(json[index] >= '0' && json[index] <= '9')) {
		return parseNumber(jsonValueAllocator, json, index);
	}
	/* String. */
	else if (json[index] == '"') {
		return parseString(stringAllocator, jsonValueAllocator, json, index);
	}
	/* Array. */
	else if (json[index] == '[') {
		return parseArray(
			stringAllocator,
			dynamicArrayAllocator,
			mapNodeAllocator,
			mapAllocator,
			jsonValueAllocator,
			json,
			index);
	}
	/* Object. */
	else if (json[index] == '{') {
		return parseObject(
			stringAllocator,
			dynamicArrayAllocator,
			mapNodeAllocator,
			mapAllocator,
			jsonValueAllocator,
			json,
			index);
	}
	/* Invalid JSON. */
	else {
		JsonValue* jsonValue = jsonValueAllocator->allocate(1);
		jsonValueAllocator->construct(jsonValue, JsonValue());
		return Parse(jsonValue, index);
	}
}

/* TODO. */
JsonParser::Parse JsonParser::parseBool(
	sgdm::IAllocator< JsonValue >* jsonValueAllocator,
	const std::string& json,
	unsigned int index) {

	JsonValue* jsonValue = jsonValueAllocator->allocate(1);

	/* True. */
	if (json[index] == 't') {
		index++;
		if (json[index++] == 'r' && /* Read rest of 'true'. */
			json[index++] == 'u' &&
			json[index] == 'e') {
			jsonValueAllocator->construct(jsonValue, JsonValue(true));
		}
		else {
			jsonValueAllocator->construct(jsonValue, JsonValue());
		}
	}
	/* False. */
	else { /* Must begin with either 't' or 'f' to trigger function. */
		index++;
		if (json[index++] == 'a' && /* Read rest of 'false'. */
			json[index++] == 'l' &&
			json[index++] == 's' &&
			json[index] == 'e') {
			jsonValueAllocator->construct(jsonValue, JsonValue(false));
		}
		else {
			jsonValueAllocator->construct(jsonValue, JsonValue());
		}
	}

	return Parse(jsonValue, index);
}

/* TODO. */
JsonParser::Parse JsonParser::parseNumber(
	sgdm::IAllocator< JsonValue >* jsonValueAllocator,
	const std::string& json,
	unsigned int index) {

	JsonValue* jsonValue = jsonValueAllocator->allocate(1);
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
				jsonValueAllocator->construct(jsonValue, JsonValue(atof(std::string(json, startingIndex, startingIndex - index).c_str())));
				index--;
				return Parse(jsonValue, index);
			}
			else { /* Invalid exponent format. */
				jsonValueAllocator->construct(jsonValue, JsonValue());
				return Parse(jsonValue, index);
			}
		}
		else { /* If number has no exponent, finish reading as double. */
			jsonValueAllocator->construct(jsonValue, JsonValue(atof(std::string(json, startingIndex, startingIndex - index).c_str())));
			index--;
			return Parse(jsonValue, index);
		}
	}
	else { /* If number has no decimal, read as integer. */
		jsonValueAllocator->construct(jsonValue, JsonValue(atoi(std::string(json, startingIndex, startingIndex - index).c_str())));
		index--;
		return Parse(jsonValue, index);
	}
}

/* TODO. */
JsonParser::Parse JsonParser::parseString(
	sgdm::IAllocator< std::string >* stringAllocator,
	sgdm::IAllocator< JsonValue >* jsonValueAllocator,
	const std::string& json,
	unsigned int index) {

	JsonValue* jsonValue = jsonValueAllocator->allocate(1);
	unsigned int startingIndex = index;

	index++; // Skip over parenthesis.
	while (true) {
		if (json[index] == '"') { /* End of string. */
			if (stringAllocator == nullptr) {
				jsonValueAllocator->construct(jsonValue, JsonValue(std::string(json, startingIndex + 1, index - startingIndex - 1)));
			}
			else {
				jsonValueAllocator->construct(jsonValue, JsonValue(stringAllocator, std::string(json, startingIndex + 1, index - startingIndex - 1)));
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
					jsonValueAllocator->construct(jsonValue, JsonValue());
					break;
				}
			}
			else { /* Invalid special character. */
				jsonValueAllocator->construct(jsonValue, JsonValue());
				break;
			}
		}
		else { /* Regular character. */
			index++;
		}
	}

	return Parse(jsonValue, index);
}

/* TODO. */
JsonParser::Parse JsonParser::parseArray(

	sgdm::IAllocator< std::string >* stringAllocator,
	sgdm::IAllocator< sgdc::DynamicArray< JsonValue > >* dynamicArrayAllocator,
	sgdm::IAllocator< sgdc::MapNode< JsonValue > >* mapNodeAllocator,
	sgdm::IAllocator< sgdc::Map< JsonValue > >* mapAllocator,
	sgdm::IAllocator< JsonValue >* jsonValueAllocator,
	const std::string& json,
	unsigned int index) {

	JsonValue* jsonValue = jsonValueAllocator->allocate(1);
	sgdc::DynamicArray< JsonValue > dynamicArray(jsonValueAllocator);

	index++; // Skip over bracket.
	while (true) {
		if (json[index] == ']') {
			break;
		}
		else {
			Parse parse = parseEntity(stringAllocator, dynamicArrayAllocator, mapNodeAllocator, mapAllocator, jsonValueAllocator, json, index);
			if (parse.jsonValue->isError()) {
				jsonValueAllocator->deallocate(parse.jsonValue, 1);
				jsonValueAllocator->construct(jsonValue, JsonValue());
				return Parse(jsonValue, index);
			}
			
			JsonValue je = *parse.jsonValue;
			dynamicArray.append(je);
			
			jsonValueAllocator->deallocate(parse.jsonValue, 1);
			index = parse.index + 1;

			/* Flush whitespaces. */
			while (json[index] == ASCII_TAB ||
				json[index] == ASCII_NEW_LINE ||
				json[index] == ASCII_CARRIAGE_RETURN ||
				json[index] == ASCII_SPACE) {
				index++;
			}
			if (json[index] == ',') {
				index++;
			}
		}
	}

	jsonValueAllocator->construct(jsonValue, JsonValue(dynamicArrayAllocator, dynamicArray));
	return Parse(jsonValue, index);
}

/* TODO. */
JsonParser::Parse JsonParser::parseObject(
	sgdm::IAllocator< std::string >* stringAllocator,
	sgdm::IAllocator< sgdc::DynamicArray< JsonValue > >* dynamicArrayAllocator,
	sgdm::IAllocator< sgdc::MapNode< JsonValue > >* mapNodeAllocator,
	sgdm::IAllocator< sgdc::Map< JsonValue > >* mapAllocator,
	sgdm::IAllocator< JsonValue >* jsonValueAllocator,
	const std::string& json,
	unsigned int index) {

	JsonValue* jsonValue = jsonValueAllocator->allocate(1);
	sgdc::Map< JsonValue > map(mapNodeAllocator, stringAllocator, jsonValueAllocator);

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
			Parse stringParse = parseString(stringAllocator, jsonValueAllocator, json, index);
			if (stringParse.jsonValue->isError()) {
				jsonValueAllocator->deallocate(stringParse.jsonValue, 1);
				jsonValueAllocator->construct(jsonValue, JsonValue());
				return Parse(jsonValue, index);
			}

			index = stringParse.index + 1;
			std::string key = stringParse.jsonValue->asString();
			jsonValueAllocator->deallocate(stringParse.jsonValue, 1);

			/* Flush whitespaces. */
			while (json[index] == ASCII_TAB ||
				json[index] == ASCII_NEW_LINE ||
				json[index] == ASCII_CARRIAGE_RETURN ||
				json[index] == ASCII_SPACE) {
				index++;
			}
			if (json[index] != ':') {
				jsonValueAllocator->construct(jsonValue, JsonValue());
				return Parse(jsonValue, index);
			}
			index++;

			Parse valueParse = parseEntity(stringAllocator, dynamicArrayAllocator, mapNodeAllocator, mapAllocator, jsonValueAllocator, json, index);
			if (valueParse.jsonValue->isError()) {
				jsonValueAllocator->deallocate(valueParse.jsonValue, 1);
				jsonValueAllocator->construct(jsonValue, JsonValue());
				return Parse(jsonValue, index);
			}
			index = valueParse.index + 1;
			JsonValue value = *valueParse.jsonValue;
			jsonValueAllocator->deallocate(valueParse.jsonValue, 1);

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

	jsonValueAllocator->construct(jsonValue, JsonValue(mapAllocator, map));
	return Parse(jsonValue, index);
}

/* Parse the specified JSON string into a JSON value. */
JsonValue* JsonParser::parse(const std::string& json) {
	return parse(
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		&defaultJsonValueAllocator,
		json);
}

/* Parse the specified JSON string into a JSON value with the specified allocator. */
JsonValue* JsonParser::parse(
	sgdm::IAllocator< JsonValue >* jsonValueAllocator,
	const std::string& json) {

	return parse(
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		jsonValueAllocator,
		json);
}

/* Parse the specified JSON string into a JSON value with the specified allocators. */
JsonValue* JsonParser::parse(
	sgdm::IAllocator< std::string >* stringAllocator,
	sgdm::IAllocator< sgdc::DynamicArray< JsonValue > >* dynamicArrayAllocator,
	sgdm::IAllocator< sgdc::MapNode< JsonValue > >* mapNodeAllocator,
	sgdm::IAllocator< sgdc::Map< JsonValue > >* mapAllocator,
	sgdm::IAllocator< JsonValue >* jsonValueAllocator,
	const std::string& json) {

	return parseEntity(
		stringAllocator,
		dynamicArrayAllocator,
		mapNodeAllocator,
		mapAllocator,
		jsonValueAllocator,
		json,
		0).jsonValue;
}

}
}