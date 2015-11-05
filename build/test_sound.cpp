/*
	Dominik Jedruszczak

	A simple program to test SFML sounds support.
*/

#include <SFML/Audio.hpp>

#include "../src/engine/input/input.hpp"
#include "../src/engine/scene/scene.hpp"
#include "../src/engine/sound/sounds.hpp"
#include "../src/engine/events/event_bus.hpp"

int main(int argc, char** argv) {
	using namespace StevensDev;

	//static sound::Sounds& sounds = sound::Sounds::getInstance();
	
	//std::function< void(const sgde::IEvent*) > soundEventCallback =
		/*std::bind(
			&sound::Sounds::onSoundEvent, 
			//&sounds,
			std::placeholders::_1);*/
		//&sound::Sounds::onSoundEvent;

	//sgde::SoundEvent soundEvent("../sounds/cannon.wav");

	/*sgde::EventBus::getDispatcher().addListener(
		&soundEvent, 
		&soundEventCallback);
	sgde::EventBus::getDispatcher().preTick();
	sgde::EventBus::getDispatcher().tick(0);
	sgde::EventBus::getDispatcher().postTick();

	sgde::EventBus::getDispatcher().dispatch(&soundEvent);
	soundEventCallback(&soundEvent);*/

	sound::Sounds::getInstance().onSoundEvent(NULL);

	return 0;
}