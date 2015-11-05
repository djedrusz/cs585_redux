/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_SOUND_EVENT
#define INCLUDED_SOUND_EVENT

#include "../events/ievent.hpp"

namespace StevensDev {
namespace sgde { // Stevens Game Development Events.

/* TODO. */
class SoundEvent : public sgde::IEvent {
	private:
		/* Data member(s). */
		const std::string type = "sound";
		const std::string path;
	public:
		/* Constructor(s). */
		SoundEvent(const std::string& path);
		/* Inherited function(s). */
		// IEvent.
		virtual const std::string& getType() const;
		/* Function(s). */
		const std::string& getPath() const;
};

}
}

#endif