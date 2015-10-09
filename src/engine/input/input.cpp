/*
	Dominik Jedruszczak

	input.cpp
	Implementation of the "Input" singleton.
*/

#include "input.hpp"

namespace StevensDev {
namespace sgdi { // Stevens Game Development Input.

/* Return the only instance. */
static Input& Input::getInstance() {
	static Input instance;

	return instance;
}

}
}