/*
	Dominik Jedruszczak
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