#pragma once
#include <cstdint>
#include <d3d9.h>
#include <cmath>
#define M_PI 3.14159265358979323846

struct Color {
	float A, R, G, B;
	Color() = default;
	Color(float r, float g, float b, float a = 255) {
		this->R = r;
		this->G = g;
		this->B = b;
		this->A = a;
	}
	Color(uint32_t color) {
		this->A = (color >> 24) & 0xff;
		this->R = (color >> 16) & 0xff;
		this->G = (color >> 8) & 0xff;
		this->B = (color & 0xff);
	}
	Color from_uint(uint32_t uint) {
		return Color(uint);
	}
	static Color FromHSB(float flHue, float flSaturation, float flBrightness)
	{
		const float h = std::fmodf(flHue, 1.0f) / (60.0f / 360.0f);
		const int i = static_cast<int>(h);
		const float f = h - static_cast<float>(i);
		const float p = flBrightness * (1.0f - flSaturation);
		const float q = flBrightness * (1.0f - flSaturation * f);
		const float t = flBrightness * (1.0f - flSaturation * (1.0f - f));

		float r = 0.0f, g = 0.0f, b = 0.0f;

		switch (i)
		{
		case 0:
			r = flBrightness, g = t, b = p;
			break;
		case 1:
			r = q, g = flBrightness, b = p;
			break;
		case 2:
			r = p, g = flBrightness, b = t;
			break;
		case 3:
			r = p, g = q, b = flBrightness;
			break;
		case 4:
			r = t, g = p, b = flBrightness;
			break;
		case 5:
		default:
			r = flBrightness, g = p, b = q;
			break;
		}

		return Color(r, g, b);
	}
	void random_color(int iTick)
	{
		this->R = sin(3.f * iTick + 0.f) * 127 + 128;
		this->G = sin(3.f * iTick + ((2.f * M_PI) / 3)) * 127 + 128;
		this->B = sin(3.f * iTick + ((4.f * M_PI) / 3)) * 127 + 128;
		this->A = 255;
		// decrease 0.3f if you want it smoother
	}

	static Color black(float a = 255) { return { 0, 0, 0, a }; }
	static Color white(float a = 255) { return { 255, 255, 255, a }; }
	static Color red(float   a = 255) { return { 255, 0, 0, a }; }
	static Color green(float a = 255) { return { 0, 255, 0, a }; }
	static Color blue(float  a = 255) { return { 0, 0, 255, a }; }
};

static void rainbow(Color& Color_)
{
	static uint32_t cnt = 0;
	DWORD freq = .005f;

	Color _Color = Color(
		std::sin(freq * cnt + 0) * 127 + 128,
		std::sin(freq * cnt + 2) * 127 + 128,
		std::sin(freq * cnt + 4) * 127 + 128,
		255);

	// Probably redundant
	if (cnt++ >= (uint32_t)-1) cnt = 0;

	Color_ = _Color;
}
