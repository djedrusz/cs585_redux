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

void Sounds::onSoundEvent(const sgde::IEvent* soundEvent) {
	std::cout << "THIS SHOULD BE HIT." << std::endl;
	
	const sgde::SoundEvent* se = 
				dynamic_cast< const sgde::SoundEvent* >(soundEvent);;
	
	soundBuffers[0].loadFromFile(se->getPath());
	sounds[0].setBuffer(soundBuffers[0]);
	sounds[0].play();
	while(1);
}

}
}