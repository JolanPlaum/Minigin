#include "Rectangle.h"
#include <utility>


dae::Rectangle::Rectangle(float _x, float _y, float _w, float _h)
	: x{ _x }
	, y{ _y }
	, w{ _w }
	, h{ _h }
{
}

dae::Rectangle::Rectangle(const Boundaries& bounds)
	: x{ bounds.x1 }
	, y{ bounds.y1 }
	, w{ bounds.x2 - bounds.x1 }
	, h{ bounds.y2 - bounds.y1 }
{
}

dae::Boundaries::Boundaries(float _x1, float _y1, float _x2, float _y2)
	: x1{ _x1 }
	, y1{ _y1 }
	, x2{ _x2 }
	, y2{ _y2 }
{
}

dae::Boundaries::Boundaries(const Rectangle& rect)
	: x1{ rect.x }
	, y1{ rect.y }
	, x2{ rect.x + rect.w }
	, y2{ rect.y + rect.h }
{
}

bool dae::IsLeftCollision(const Boundaries& bounds, const Boundaries& otherBounds)
{
	return bounds.x1 < otherBounds.x1 && bounds.x2 > otherBounds.x1;
}
bool dae::IsRightCollision(const Boundaries& bounds, const Boundaries& otherBounds)
{
	return bounds.x1 < otherBounds.x2 && bounds.x2 > otherBounds.x2;
}
bool dae::IsBottomCollision(const Boundaries& bounds, const Boundaries& otherBounds)
{
	return bounds.y1 < otherBounds.y1 && bounds.y2 > otherBounds.y1;
}
bool dae::IsTopCollision(const Boundaries& bounds, const Boundaries& otherBounds)
{
	return bounds.y1 < otherBounds.y2 && bounds.y2 > otherBounds.y2;
}

float dae::OverlapPercentageX(const Boundaries& bounds, const Boundaries& otherBounds)
{
	float overlapX{ std::min(bounds.x2, otherBounds.x2) - std::max(bounds.x1, otherBounds.x1) };
	float smallestX{ std::min(bounds.x2 - bounds.x1, otherBounds.x2 - otherBounds.x1) };

	return overlapX / smallestX;
}
float dae::OverlapPercentageY(const Boundaries& bounds, const Boundaries& otherBounds)
{
	float overlapY{ std::min(bounds.y2, otherBounds.y2) - std::max(bounds.y1, otherBounds.y1) };
	float smallestY{ std::min(bounds.y2 - bounds.y1, otherBounds.y2 - otherBounds.y1) };

	return overlapY / smallestY;
}
float dae::OverlapPercentageTotal(const Boundaries& bounds, const Boundaries& otherBounds)
{
	return OverlapPercentageX(bounds, otherBounds) * OverlapPercentageY(bounds, otherBounds);
}
