#include "Rectangle.h"


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
