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

	std::function< void(const sgde::IEvent*) > soundEventCallback =
		std::bind(
			&sound::Sounds::onSoundEvent, 
			&sound::Sounds::getInstance(),
			std::placeholders::_1);
		&sound::Sounds::onSoundEvent;

	sgde::SoundEvent soundEvent("../sounds/cannon.wav");

	sgde::EventBus::getDispatcher().addListener(
		&soundEvent, 
		&soundEventCallback);

	sgds::Scene::getInstance().addTickable(&sgdi::Input::getInstance());
	sgds::Scene::getInstance().addTickable(&sgde::EventBus::getDispatcher());

	while(1) {
		sgds::Scene::getInstance().tick();

		if (sgdi::Input::getInstance().wasPressed(sgdi::Input::Type::A)) {
			sgde::EventBus::getDispatcher().dispatch(&soundEvent);
		}
	}

	return 0;
}