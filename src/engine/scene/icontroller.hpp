/*
	Dominik Jedruszczak
*/

#ifndef INCLUDED_ICONTROLLER
#define INCLUDED_ICONTROLLER

#include "itickable.hpp"
#include "iactor.hpp"

namespace StevensDev {
namespace sgds { // Stevens Game Development Scene.

/* An abstract controller object. */
class IController : public ITickable {
	public:
		/* Function(s). */
		virtual void possess(IActor* actor) = 0; 
};

}
}

#endif