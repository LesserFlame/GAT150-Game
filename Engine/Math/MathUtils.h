#pragma once

namespace jemgine
{
	const float Pi = 3.14159265f; // 180
	const float TwoPi = 6.2831853f; // 360
	const float HalfPi = 1.57079633f; // 90

	inline float DegToRad(float degrees){ return degrees * (Pi / 180); }
	inline float RadToDeg(float radians){ return radians * (180 / Pi); }

	int sqr(int v);
	inline int half(int v) { return v / 2; }
}