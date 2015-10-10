/*
	Dominik Jedruszczak

	renderable_sprite.cpp
	Implementation of the "RenderableSprite" class.
*/

#include "renderable_sprite.hpp"

namespace StevensDev {
namespace sgdr { // Stevens Game Development Rendering.

/* Default constructor. */
RenderableSprite::RenderableSprite()
:	RenderableSprite(0.0f, 0.0f) {
	;
}

/* Constructor with specified position. */
RenderableSprite::RenderableSprite(float x, float y) {
	setPosition(x, y);
}

/* Copy constructor. */
RenderableSprite::RenderableSprite(const RenderableSprite& renderableSprite)
:	sprite(renderableSprite.sprite) {
	setPosition(renderableSprite.x, renderableSprite.y);
}

/* Move constructor. */
RenderableSprite::RenderableSprite(RenderableSprite&& renderableSprite)
:	sprite(std::move(renderableSprite.sprite)) {
	setPosition(renderableSprite.x, renderableSprite.y);	
}

/* Copy assignment operator. */
RenderableSprite& RenderableSprite::operator = (const RenderableSprite& renderableSprite) {
	sprite = renderableSprite.sprite;
	setPosition(renderableSprite.x, renderableSprite.y);
}

/* Move assignment operator. */
RenderableSprite& RenderableSprite::operator = (RenderableSprite&& renderableSprite) {
	sprite = std::move(renderableSprite.sprite);
	setPosition(renderableSprite.x, renderableSprite.y);
}

/* Return the sprite. */
sf::Sprite& RenderableSprite::getSprite() {
	return sprite;
}

/* Return the x-position. */
const float RenderableSprite::getPositionX() const {
	return x;
}

/* Return the y-position. */
const float RenderableSprite::getPositionY() const {
	return y;
}

/* Set the x-position. */
void RenderableSprite::setPositionX(float x) {
	setPosition(x, y);
}

/* Set the y-position. */
void RenderableSprite::setPositionY(float y) {
	setPosition(x, y);
}

/* Set the x and y-positions. */
void RenderableSprite::setPosition(float x, float y) {
	this->x = x;
	this->y = y;
	sprite.setPosition(this->x, this->y);
}

/* Increment the x and y-positions. */
void RenderableSprite::move(float x, float y) {
	setPosition(this->x + x, this->y + y);
}

}
}
