/*
	Dominik Jedruszczak
*/

#include "texture_manager.hpp"

namespace StevensDev {
namespace sgda { // Stevens Game Development Assets.

/* Define static variables. */
sgdc::Map< sf::Texture > TextureManager::textures;

void TextureManager::add(const std::string& name, const std::string& path) {
	sf::Texture texture;
	if (texture.loadFromFile(path)) {
		textures.put(name, std::move(texture));
	}
}

const sf::Texture& TextureManager::get(const std::string& name) {
	return textures.get(name);
}

}
}