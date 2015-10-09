/*
	Dominik Jedruszczak

	renderable_sprite.hpp
	Declaration of the "RenderableSprite" class.
*/

#ifndef INCLUDED_RENDERABLE_SPRITE
#define INCLUDED_RENDERABLE_SPRITE

#include <SFML/Graphics/Sprite.hpp>

namespace StevensDev {
namespace sgdr { // Stevens Game Development Rendering.

/* A renderable sprite. */
class RenderableSprite {
	private:
		/* Data member(s). */
		sf::Sprite sprite; // The sprite.
		float x; // The x-position.
		float y; // The y-position.
	public:
		/* Constructor(s). */
		RenderableSprite(); // Default constructor.
		RenderableSprite(const RenderableSprite& renderableSprite); // Copy constructor.
		RenderableSprite(RenderableSprite&& renderableSprite); // Move constructor.
		/* Operator(s). */
		RenderableSprite& operator = (const RenderableSprite& renderableSprite); // Copy assignment operator.
		RenderableSprite& operator = (RenderableSprite&& renderableSprite); // Move assignment operator.
		/* Function(s). */
		const sf::Sprite& getSprite() const; // Return the sprite;
		const float getPositionX() const; // Return the x-position.
		const float getPositionY() const; // Return the y-position.
		void setPositionX(float x); // Set the x-position.
		void setPositionY(float y); // Set the y-position.
		void setPosition(float x, float y); // Set the x and y-positions.
		void move(float x, float y); // Increment the x and y-positions.
};

}
}

#endif