/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_SOUNDS
#define INCLUDED_SOUNDS

#include <iostream>
#include <SFML/Audio.hpp>
#include "../containers/dynamic_array.hpp"
#include "../events/sound_event.hpp"

#define MAX_SOUNDS 100 // The maximum amount of concurrent sounds.

namespace StevensDev {
namespace sound {

/* Todo. */
class Sounds {
	private:
		/* Constructor(s). */
		Sounds();
		Sounds(const Sounds& sounds) = delete;
		/* Operator(s). */
		Sounds& operator = (const Sounds& sounds) = delete;
		/* Data member(s). */
		static sf::SoundBuffer soundBuffers[MAX_SOUNDS];
		static sf::Sound sounds[MAX_SOUNDS];
	public:
		/* Function(s). */
		static Sounds& getInstance();
		void onSoundEvent(const sgde::IEvent* soundEvent);
};

}
}

#endif