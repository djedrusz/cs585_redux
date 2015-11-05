/*
	Dominik Jedruszczak
*/

#include "sounds.hpp"

namespace StevensDev {
namespace sound {

/* Define static variables. */
sf::SoundBuffer Sounds::soundBuffers[MAX_SOUNDS];
sf::Sound Sounds::sounds[MAX_SOUNDS];

Sounds::Sounds() {
	;
}

Sounds& Sounds::getInstance() {
	static Sounds sounds;

	return sounds;
}

void Sounds::onSoundEvent(const sgde::IEvent* soundEvent) {
	std::cout << "L";
	/*soundBuffers[0].loadFromFile(soundEvent->getPath());
	sounds[0].setBuffer(soundBuffers[0]);
	sounds[0].play();*/
}

}
}