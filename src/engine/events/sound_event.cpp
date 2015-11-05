/*
	Dominik Jedruszczak
*/

#include "sound_event.hpp"

namespace StevensDev{
namespace sgde { // Stevens Game Development Events.

SoundEvent::SoundEvent(const std::string& path)
:	path(path) {
	;
}

const std::string& SoundEvent::getType() const {
	return type;
}

const std::string& SoundEvent::getPath() const {
	return path;
}


}
}