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
	assert(width > 0);
	assert(height > 0);
}

RectangleBounds::RectangleBounds(const RectangleBounds& rectangleBounds)
:	x(rectangleBounds.x),
	y(rectangleBounds.y),
	width(rectangleBounds.width),
	height(rectangleBounds.height) {
	assert(width > 0);
	assert(height > 0);
}

RectangleBounds::RectangleBounds(RectangleBounds&& rectangleBounds)
:	x(rectangleBounds.x),
	y(rectangleBounds.y),
	width(rectangleBounds.width),
	height(rectangleBounds.height) {
	assert(width > 0);
	assert(height > 0);
}

RectangleBounds& RectangleBounds::operator = (const RectangleBounds& rectangleBounds) {
	this->x = rectangleBounds.x;
	this->y = rectangleBounds.y;
	this->width = rectangleBounds.width;
	this->height = rectangleBounds.height;
	assert(this->width > 0);
	assert(this->height > 0);
}

RectangleBounds& RectangleBounds::operator = (RectangleBounds&& rectangleBounds) {
	this->x = rectangleBounds.x;
	this->y = rectangleBounds.y;
	this->width = rectangleBounds.width;
	this->height = rectangleBounds.height;
	assert(this->width > 0);
	assert(this->height > 0);
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
	assert(this->width > 0);
}

void RectangleBounds::setHeight(float height) {
	this->height = height;
	assert(this->height > 0);
}

void RectangleBounds::setDimensions(float width, float height) {
	this->width = width;
	this->height = height;
	assert(this->width > 0);
	assert(this->height > 0);
}

bool RectangleBounds::collides(const RectangleBounds& rectangleBounds) const {
	return
		(
			(this->x < (rectangleBounds.x + rectangleBounds.width)) &&
			((this->x + this->width) > rectangleBounds.x) &&
			(this->y < (rectangleBounds.y + rectangleBounds.height)) &&
			((this->y + this->height) > rectangleBounds.y)
		);
}

}
}