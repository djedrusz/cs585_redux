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
:	x(0.0f),
	y(0.0f) {
	;
}

/* Copy constructor. */
RenderableSprite::RenderableSprite(const RenderableSprite& renderableSprite)
:	sprite(renderableSprite.sprite),
	x(renderableSprite.x),
	y(renderableSprite.y) {
	;	
}

/* Move constructor. */
RenderableSprite::RenderableSprite(RenderableSprite&& renderableSprite)
:	sprite(std::move(renderableSprite.sprite)),
	x(renderableSprite.x),
	y(renderableSprite.y) {
	;	
}

/* Copy assignment operator. */
RenderableSprite& RenderableSprite::operator = (const RenderableSprite& renderableSprite) {
	sprite = renderableSprite.sprite;
	x = renderableSprite.x;
	y = renderableSprite.y;
}

/* Move assignment operator. */
RenderableSprite& RenderableSprite::operator = (RenderableSprite&& renderableSprite) {
	sprite = std::move(renderableSprite.sprite);
	x = renderableSprite.x;
	y = renderableSprite.y;
}

/* Return the sprite. */
const sf::Sprite& RenderableSprite::getSprite() const {
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
	this->x = x;
}

/* Set the y-position. */
void RenderableSprite::setPositionY(float y) {
	this->y = y;
}

/* Set the x and y-positions. */
void RenderableSprite::setPosition(float x, float y) {
	this->x = x;
	this->y = y;
}

/* Increment the x and y-positions. */
void RenderableSprite::move(float x, float y) {
	this->x += x;
	this->y += y;
}

}
}
