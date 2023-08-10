#include "Rectangle.h"


dae::Rectangle::Rectangle(const Boundaries& bounds)
	: x{ bounds.x1 }
	, y{ bounds.y1 }
	, w{ bounds.x2 - bounds.x1 }
	, h{ bounds.y2 - bounds.y1 }
{
}

dae::Boundaries::Boundaries(const Rectangle& rect)
	: x1{ rect.x }
	, y1{ rect.y }
	, x2{ rect.x + rect.w }
	, y2{ rect.y + rect.h }
{
}
