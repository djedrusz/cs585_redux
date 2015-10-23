/*
	Dominik Jedruszczak

	rectangle_bounds.cpp
	Implementation of the "RectangleBounds" class.
*/

#include "rectangle_bounds.hpp"

namespace StevensDev {
namespace sgds { // Stevens Game Development Scene.

RectangleBounds::RectangleBounds(float x, float y, float width, float height)
:	x(x),
	y(y),
	width(width),
	height(height) {
	;
}

RectangleBounds::RectangleBounds(const RectangleBounds& rectangleBounds)
:	x(rectangleBounds.x),
	y(rectangleBounds.y),
	width(rectangleBounds.width),
	height(rectangleBounds.height) {
	;
}

RectangleBounds::RectangleBounds(RectangleBounds&& rectangleBounds)
:	x(rectangleBounds.x),
	y(rectangleBounds.y),
	width(rectangleBounds.width),
	height(rectangleBounds.height) {
	;
}

RectangleBounds& RectangleBounds::operator = (const RectangleBounds& rectangleBounds) {
	this->x = rectangleBounds.x;
	this->y = rectangleBounds.y;
	this->width = rectangleBounds.width;
	this->height = rectangleBounds.height;
}

RectangleBounds& RectangleBounds::operator = (RectangleBounds&& rectangleBounds) {
	this->x = rectangleBounds.x;
	this->y = rectangleBounds.y;
	this->width = rectangleBounds.width;
	this->height = rectangleBounds.height;
}

const float RectangleBounds::getX() const {
	return x;
}

const float RectangleBounds::getY() const {
	return y;
}

const float RectangleBounds::getWidth() const {
	return width;
}

const float RectangleBounds::getHeight() const {
	return height;
}

void RectangleBounds::setX(float x) {
	this->x = x;
}

void RectangleBounds::setY(float y) {
	this->y = y;
}

void RectangleBounds::setPosition(float x, float y) {
	this->x = x;
	this->y = y;
}

void RectangleBounds::setWidth(float width) {
	this->width = width;
}

void RectangleBounds::setHeight(float height) {
	this->height = height;
}

void RectangleBounds::setDimensions(float width, float height) {
	this->width = width;
	this->height = height;
}

bool RectangleBounds::collides(const RectangleBounds& rectangleBounds) const {
	return
		(
			x < rectangleBounds.x + rectangleBounds.width &&
			x + width > rectangleBounds.x &&
			y < rectangleBounds.y + rectangleBounds.height &&
			y + height > rectangleBounds.y
		);
}

}
}