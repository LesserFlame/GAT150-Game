#pragma once
#include <cstdint>
#include <sstream>
#include <iostream>
#include <string>

namespace jemgine
{
	struct Color
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;

		static const Color red;
		static const Color green;
		static const Color blue;
		static const Color white;
		static const Color black;

		uint8_t  operator [] (size_t index) const { return (&r)[index]; }
		uint8_t& operator [] (size_t index) { return (&r)[index]; }
		//friend std::istream& operator >> (std::istream& stream, Color& color);
	};
	std::istream& operator >> (std::istream& stream, Color& color);
	std::ostream& operator << (std::ostream& stream, const Color& v);
}