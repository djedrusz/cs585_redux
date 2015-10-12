/*
	Dominik Jedruszczak

	input.cpp
	Implementation of the "Input" singleton.
*/

#include "input.hpp"

namespace StevensDev {
namespace sgdi { // Stevens Game Development Input.

/* Pre-tick logic. */
void Input::preTick() {
	for (unsigned int i = 0; i < INPUT_NUM_TYPE; i++) {
		previousStates[i] = currentStates[i];
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		currentStates[Type::A] = 1;
	}
	else {
		currentStates[Type::A] = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
		currentStates[Type::B] = 1;
	}
	else {
		currentStates[Type::B] = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		currentStates[Type::C] = 1;
	}
	else {
		currentStates[Type::C] = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		currentStates[Type::D] = 1;
	}
	else {
		currentStates[Type::D] = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		currentStates[Type::E] = 1;
	}
	else {
		currentStates[Type::E] = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
		currentStates[Type::F] = 1;
	}
	else {
		currentStates[Type::F] = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
		currentStates[Type::G] = 1;
	}
	else {
		currentStates[Type::G] = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
		currentStates[Type::H] = 1;
	}
	else {
		currentStates[Type::H] = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
		currentStates[Type::I] = 1;
	}
	else {
		currentStates[Type::I] = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
		currentStates[Type::J] = 1;
	}
	else {
		currentStates[Type::J] = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
		currentStates[Type::K] = 1;
	}
	else {
		currentStates[Type::K] = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
		currentStates[Type::L] = 1;
	}
	else {
		currentStates[Type::L] = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
		currentStates[Type::M] = 1;
	}
	else {
		currentStates[Type::M] = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
		currentStates[Type::N] = 1;
	}
	else {
		currentStates[Type::N] = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
		currentStates[Type::O] = 1;
	}
	else {
		currentStates[Type::O] = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
		currentStates[Type::P] = 1;
	}
	else {
		currentStates[Type::P] = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		currentStates[Type::Q] = 1;
	}
	else {
		currentStates[Type::Q] = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		currentStates[Type::R] = 1;
	}
	else {
		currentStates[Type::R] = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		currentStates[Type::S] = 1;
	}
	else {
		currentStates[Type::S] = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
		currentStates[Type::T] = 1;
	}
	else {
		currentStates[Type::T] = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
		currentStates[Type::U] = 1;
	}
	else {
		currentStates[Type::U] = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
		currentStates[Type::V] = 1;
	}
	else {
		currentStates[Type::V] = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		currentStates[Type::W] = 1;
	}
	else {
		currentStates[Type::W] = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
		currentStates[Type::X] = 1;
	}
	else {
		currentStates[Type::X] = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
		currentStates[Type::Y] = 1;
	}
	else {
		currentStates[Type::Y] = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		currentStates[Type::Z] = 1;
	}
	else {
		currentStates[Type::Z] = 0;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		currentStates[Type::MOUSE_LEFT] = 1;
	}
	else {
		currentStates[Type::MOUSE_LEFT] = 0;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		currentStates[Type::MOUSE_RIGHT] = 1;
	}
	else {
		currentStates[Type::MOUSE_RIGHT] = 0;
	}
}

/* Tick logic. */
void Input::tick(float deltaTime) {
	;
}

/* Post-tick logic. */
void Input::postTick() {
	;
}

/* Return the only instance. */
Input& Input::getInstance() {
	static Input instance;

	return instance;
}

/* Return whether or not the input type is down. */
bool Input::isDown(Type input) {
	return currentStates[input];
}

/* Return whether or not the input type is up. */
bool Input::isUp(Type input) {
	return !currentStates[input];
}

/* Return whether or not the input type was pressed. */
bool Input::wasPressed(Type input) {
	return ((previousStates[input] == 0) && (currentStates[input] == 1));
}

}
}