#pragma once

namespace dae
{
	struct Boundaries;

	struct Rectangle
	{
		Rectangle() = default;
		Rectangle(float _x, float _y, float _w, float _h);
		Rectangle(const Boundaries& bounds);

		float x{}, y{};
		float w{}, h{};
	};

	struct Boundaries
	{
		Boundaries() = default;
		Boundaries(float _x1, float _y1, float _x2, float _y2);
		Boundaries(const Rectangle& rect);

		float x1{}, y1{};
		float x2{}, y2{};
	};
}

