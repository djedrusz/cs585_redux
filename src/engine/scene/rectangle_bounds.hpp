/*
	Dominik Jedruszczak

	rectangle_bounds.hpp
	Declaration of the "RectangleBounds" class.
*/

#ifndef INCLUDED_RECTANGLE_BOUNDS
#define INCLUDED_RECTANGLE_BOUNDS

namespace StevensDev {
namespace sgds { // Stevens Game Development Scene.

/* A 2-dimensional bounding box. */
class RectangleBounds {
	private:
		/* Constructor(s). */
		RectangleBounds();
		/* Data member(s). */
		float x;
		float y;
		float width;
		float height;
	public:
		/* Constructor(s). */
		RectangleBounds(float x, float y, float width, float height);
		RectangleBounds(const RectangleBounds& rectangleBounds);
		RectangleBounds(RectangleBounds&& rectangleBounds);
		/* Operator(s). */
		RectangleBounds& operator = (const RectangleBounds& rectangleBounds);
		RectangleBounds& operator = (RectangleBounds&& rectangleBounds);
		/* Function(s). */
		const float getX() const;
		const float getY() const;
		const float getWidth() const;
		const float getHeight() const;
		void setX(float x);
		void setY(float y);
		void setPosition(float x, float y);
		void setWidth(float width);
		void setHeight(float height);
		void setDimensions(float width, float height);
		bool collides(const RectangleBounds& rectangleBounds) const;
};

}
}

#endif