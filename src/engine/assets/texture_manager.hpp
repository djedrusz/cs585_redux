/*
	Dominik Jedruszczak

	Consider one of the following as the current map implementation does not 
	destroy removed values; textures will live (in full) in the map and graphics 
	card even when removed. Why does SFML not have a function to destroy textures?
	1.	Making TextureManager a regular class. As TextureManager is destroyed, 
		so are the textures.
	2.	Changing the texture map to hold pointers instead. Set textures to null 
		when they are removed. Do they still live on the GPU -- destructor does 
		not specify...
	3.	Leave as is; current implementation is fine for few textures used over 
		the course of the whole game -- which is what this engine is used for.
*/

#ifndef INCLUDED_TEXTURE_MANAGER
#define INCLUDED_TEXTURE_MANAGER

#include <SFML/Graphics/Texture.hpp>
#include "../containers/map.hpp"

namespace StevensDev {
namespace sgda { // Stevens Game Development Assets.

/* Handles loading and storing textures. */
class TextureManager {
	private:
		static sgdc::Map< sf::Texture > textures;
	public:
		static void add(const std::string& name, const std::string& path);
		static const sf::Texture& get(const std::string& name);
		/* No need for remove because map does not actually remove values. */
};

}
}

#endif