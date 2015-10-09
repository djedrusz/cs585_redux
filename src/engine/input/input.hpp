/*
	Dominik Jedruszczak

	input.hpp
	Declaration of the "Input" singleton.
*/

#ifndef INCLUDED_INPUT
#define INCLUDED_INPUT

namespace StevensDev {
namespace sgdi { // Stevens Game Development Input

/* SFML input wrapper singleton. */
class Input {
	private:
		/* Constructor(s). */
		Input() {}; // Default constructor.
		Input(const Input& input) = delete; // Copy constructor.
		/* Operator(s). */
		Input& operator = (const Input& input) = delete; // Copy assignment operator.
	public:
		static Input& getInstance(); // Return the only instance.
};

}
}

#endif