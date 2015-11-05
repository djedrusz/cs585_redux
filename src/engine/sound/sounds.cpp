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

	std::cout << "Getting instance." << std::endl;
	return sounds;
}

void Sounds::onSoundEvent(const sgde::IEvent* event) {
	const sgde::SoundEvent* soundEvent = (const sgde::SoundEvent*)event;
	
	/* Simple iteration for now. */
	for (unsigned int i = 0; i < MAX_SOUNDS; i++) {
		if (sounds[i].getStatus() == sf::Sound::Status::Stopped) {
			soundBuffers[i].loadFromFile(soundEvent->getPath());
			sounds[i].setBuffer(soundBuffers[i]);
			sounds[i].play();
			break;
		}
	}
}

}
}