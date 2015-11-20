/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_IFACTORY
#define INCLUDED_IFACTORY

#include "icontroller.hpp"

namespace StevensDev {
namespace sgds { // Stevens Game Development Scene.

/* An actor/controller factory. */
class IFactory {
	public
		/* Function(s). */
		virtual const IController* createController() = 0;
		virtual const IActor* createActor() = 0;

};

}
}

#endif