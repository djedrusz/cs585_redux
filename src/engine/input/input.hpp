/*
	Dominik Jedruszczak

	input.hpp
	Declaration of the "Input" singleton.
*/

#ifndef INCLUDED_INPUT
#define INCLUDED_INPUT

#include "../scene/itickable.hpp"
#include <SFML/Window.hpp>

#define INPUT_NUM_TYPE 28

namespace StevensDev {
namespace sgdi { // Stevens Game Development Input

/* SFML input wrapper singleton. */
class Input : public sgds::ITickable {
	public:
		/* The possible input types. */
		enum Type {
			A,
			B,
			C,
			D,
			E,
			F,
			G,
			H,
			I,
			J,
			K,
			L,
			M,
			N,
			O,
			P,
			Q,
			R,
			S,
			T,
			U,
			V,
			W,
			X,
			Y,
			Z,
			MOUSE_LEFT,
			MOUSE_RIGHT
		};

	private:
		/* Constructor(s). */
		Input() {}; // Default constructor.
		Input(const Input& input) = delete; // Copy constructor.
		/* Operator(s). */
		Input& operator = (const Input& input) = delete; // Copy assignment operator.
		/* Data member(s). */
		bool previousStates[INPUT_NUM_TYPE] = {0};
		bool currentStates[INPUT_NUM_TYPE] = {0};

	public:
		/* Function(s). */
		void preTick(); // Pre-tick logic.
		void tick(float deltaTime); // Tick logic.
		void postTick(); // Post-tick logic.
		static Input& getInstance(); // Return the only instance.
		bool isDown(Type input); // Return whether the input type is down.
		bool isUp(Type input); // Return whether the input type is up.
		bool wasPressed(Type input); // Return whether the input type was pressed.
};

}
}

#endif