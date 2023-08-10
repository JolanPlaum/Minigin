#pragma once

namespace dae
{
	struct Boundaries;

	struct Rectangle
	{
		Rectangle() = default;
		Rectangle(const Boundaries& bounds);

		float x{}, y{};
		float w{}, h{};
	};

	struct Boundaries
	{
		Boundaries() = default;
		Boundaries(const Rectangle& rect);

		float x1{}, y1{};
		float x2{}, y2{};
	};
}

