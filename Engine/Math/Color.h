#pragma once
#include <cstdint>
#include <sstream>

namespace jemgine
{
	struct Color
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;

		friend std::istream& operator >> (std::istream& stream, Color& color);
	};
	inline std::istream& operator >> (std::istream& stream, Color& color) {

		std::string line;
		std::getline(stream, line);
		//line: { #r, #g, #b }
		//^line formatting

		std::string str;

		line = line.substr(line.find("{") + 1);
		str = line.substr(0, line.find(","));
		color.r = (uint8_t)(std::stof(str) * 255);

		line = line.substr(line.find(",") + 1);
		str = line.substr(0, line.find(","));
		color.g = (uint8_t)(std::stof(str) * 255);

		line = line.substr(line.find(",") + 1);
		str = line.substr(0, line.find("}"));
		color.b = (uint8_t)(std::stof(str) * 255);


		/*
		line = line.substr(line.find("{") + 1);

		str = line.substr(color.r);

		line = line.substr(line.find(",") + 1);

		
		str = line.substr(color.b);
		color.b = (uint8_t)(std::stof(str) * 255);
		
		line = line.substr(line.find(",") + 1);

		str = line.substr(color.g);
		color.g = (uint8_t)(std::stof(str) * 255);
		*/
		color.a = 255;

		return stream;
	}
}