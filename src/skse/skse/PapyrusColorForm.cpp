#include "PapyrusColorForm.h"
 
#include "GameForms.h"
#include "GameObjects.h"
#include "GameRTTI.h"
 
#define MIN3(x,y,z)  ((y) <= (z) ? ((x) <= (y) ? (x) : (y)) : ((x) <= (z) ? (x) : (z)))
#define MAX3(x,y,z)  ((y) >= (z) ? ((x) >= (y) ? (x) : (y)) : ((x) >= (z) ? (x) : (z)))
 
struct HSLColor {
	float	h; // Hue between 0 and 1.0
	float	s; // Saturation between 0 and 1.0
	float	l; // Lum between 0 and 1.0
};

struct RGBColor {
	UInt8 r;
	UInt8 g;
	UInt8 b;
};

HSLColor GetHSL(RGBColor rgb) {
	double r = rgb.r / 255.0;
	double g = rgb.g / 255.0;
	double b = rgb.b / 255.0;
	double rgb_max, rgb_min, diff;
	double r2, g2, b2;

	HSLColor out;
	out.h = 0; // default to black
	out.s = 0;
	out.l = 0;
	rgb_max = MAX3(r, g, b);
	rgb_min = MIN3(r, g, b);
	out.l = (rgb_min + rgb_max) / 2.0;
	if (out.l <= 0.0)
		return out;

	diff = rgb_max - rgb_min;
	out.s = diff;
	if (out.s > 0.0)
		out.s /= (out.l <= 0.5) ? (rgb_max - rgb_min) / (rgb_max + rgb_min) : (2.0 - rgb_max - rgb_min);
	else
		return out;

	r2 = (rgb_max - r) / diff;
	g2 = (rgb_max - g) / diff;
	b2 = (rgb_max - b) / diff;
	if (r == rgb_max)
		out.h = (g == rgb_min ? 5.0 + b2 : 1.0 - g2);
	else if (g == rgb_max)
		out.h = (b == rgb_min ? 1.0 + r2 : 3.0 - b2);
	else
		out.h = (r == rgb_min ? 3.0 + g2 : 5.0 - r2);

	out.h /= 6.0;
	return out;
}

RGBColor GetRGB(HSLColor hsl)
{
	double v;
	double r,g,b;

	r = hsl.l;   // default to gray
	g = hsl.l;
	b = hsl.l;
	v = (hsl.l <= 0.5) ? (hsl.l * (1.0 + hsl.s)) : (hsl.l + hsl.s - hsl.l * hsl.s);
	if (v > 0)
	{
		double m, sv, fract, vsf, mid1, mid2;
		int sextant;
		m = hsl.l + hsl.l - v;
		sv = (v - m) / v;
		hsl.h *= 6.0;
		sextant = (SInt32)hsl.h;
		fract = hsl.h - sextant;
		vsf = v * sv * fract;
		mid1 = m + vsf;
		mid2 = v - vsf;
		switch (sextant)
		{
			case 0:	r = v;		g = mid1;	b = m;		break;
			case 1:	r = mid2;	g = v;		b = m;		break;
			case 2:	r = m;		g = v;		b = mid1;	break;
			case 3:	r = m;		g = mid2;	b = v;		break;
			case 4:	r = mid1;	g = m;		b = v;		break;
			case 5:	r = v;		g = m;		b = mid2;	break;
		}
	}

	RGBColor out;
	out.r = r * 255;
	out.g = g * 255;
	out.b = b * 255;
	return out;
}

namespace papyrusColorComponent
{
	UInt32 GetRed(StaticFunctionTag* base, UInt32 argb)
	{
		return (argb & 0x00FF0000) >> 16;
	}
	UInt32 GetGreen(StaticFunctionTag* base, UInt32 argb)
	{
		return (argb & 0x0000FF00) >> 8;
	}
	UInt32 GetBlue(StaticFunctionTag* base, UInt32 argb)
	{
		return (argb & 0x000000FF);
	}
	float GetHue(StaticFunctionTag* base, UInt32 argb)
	{
		RGBColor rgb;
		rgb.r = GetRed(NULL, argb);
		rgb.g = GetGreen(NULL, argb);
		rgb.b = GetBlue(NULL, argb);
		HSLColor hsl = GetHSL(rgb);
		return hsl.h;
	}
	float GetSaturation(StaticFunctionTag* base, UInt32 argb)
	{
		RGBColor rgb;
		rgb.r = GetRed(NULL, argb);
		rgb.g = GetGreen(NULL, argb);
		rgb.b = GetBlue(NULL, argb);
		HSLColor hsl = GetHSL(rgb);
		return hsl.s;
	}
	float GetLuminosity(StaticFunctionTag* base, UInt32 argb)
	{
		RGBColor rgb;
		rgb.r = GetRed(NULL, argb);
		rgb.g = GetGreen(NULL, argb);
		rgb.b = GetBlue(NULL, argb);
		HSLColor hsl = GetHSL(rgb);
		return hsl.l;
	}
	UInt32 SetColor(StaticFunctionTag* base, UInt32 red, UInt32 green, UInt32 blue, UInt32 alpha)
	{
		return (alpha << 24) | (red << 16) | (green << 8) | blue;
	}
	UInt32 SetRed(StaticFunctionTag* base, UInt32 argb, UInt32 red)
	{
		return (argb & ~0x00FF0000) | (red << 16);
	}
	UInt32 SetGreen(StaticFunctionTag* base, UInt32 argb, UInt32 green)
	{
		return (argb & ~0x0000FF00) | (green << 8);
	}
	UInt32 SetBlue(StaticFunctionTag* base, UInt32 argb, UInt32 blue)
	{
		return (argb & ~0x000000FF) | blue;
	}
	UInt32 SetHue(StaticFunctionTag* base, UInt32 argb, float hue)
	{
		RGBColor rgb;
		rgb.r = GetRed(NULL, argb);
		rgb.g = GetGreen(NULL, argb);
		rgb.b = GetBlue(NULL, argb);
		HSLColor hsl = GetHSL(rgb);
		hsl.h = hue;
		RGBColor newRgb = GetRGB(hsl);
		return (newRgb.r << 16) | (newRgb.g << 8) | newRgb.b;
	}
	UInt32 SetSaturation(StaticFunctionTag* base, UInt32 argb, float sat)
	{
		RGBColor rgb;
		rgb.r = GetRed(NULL, argb);
		rgb.g = GetGreen(NULL, argb);
		rgb.b = GetBlue(NULL, argb);
		HSLColor hsl = GetHSL(rgb);
		hsl.s = sat;
		RGBColor newRgb = GetRGB(hsl);
		return (newRgb.r << 16) | (newRgb.g << 8) | newRgb.b;
	}
	UInt32 SetLuminosity(StaticFunctionTag* base, UInt32 argb, float lum)
	{
		RGBColor rgb;
		rgb.r = GetRed(NULL, argb);
		rgb.g = GetGreen(NULL, argb);
		rgb.b = GetBlue(NULL, argb);
		HSLColor hsl = GetHSL(rgb);
		hsl.l = lum;
		RGBColor newRgb = GetRGB(hsl);
		return (newRgb.r << 16) | (newRgb.g << 8) | newRgb.b;
	}
};

namespace papyrusColorForm
{
	UInt32 GetColor(BGSColorForm* colorForm)
	{
		return (colorForm) ? (MACRO_SWAP32(colorForm->abgr) >> 8) | (colorForm->color.alpha << 24) : 0;
	}
}

#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"

void papyrusColorComponent::RegisterFuncs(VMClassRegistry* registry)
{
	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, UInt32, UInt32>("GetRed", "ColorComponent", papyrusColorComponent::GetRed, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, UInt32, UInt32>("GetGreen", "ColorComponent", papyrusColorComponent::GetGreen, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, UInt32, UInt32>("GetBlue", "ColorComponent", papyrusColorComponent::GetBlue, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, float, UInt32>("GetHue", "ColorComponent", papyrusColorComponent::GetHue, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, float, UInt32>("GetSaturation", "ColorComponent", papyrusColorComponent::GetSaturation, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, float, UInt32>("GetLuminosity", "ColorComponent", papyrusColorComponent::GetLuminosity, registry));

	registry->RegisterFunction(
		new NativeFunction2 <StaticFunctionTag, UInt32, UInt32, UInt32>("SetRed", "ColorComponent", papyrusColorComponent::SetRed, registry));

	registry->RegisterFunction(
		new NativeFunction2 <StaticFunctionTag, UInt32, UInt32, UInt32>("SetGreen", "ColorComponent", papyrusColorComponent::SetGreen, registry));

	registry->RegisterFunction(
		new NativeFunction2 <StaticFunctionTag, UInt32, UInt32, UInt32>("SetBlue", "ColorComponent", papyrusColorComponent::SetBlue, registry));

	registry->RegisterFunction(
		new NativeFunction2 <StaticFunctionTag, UInt32, UInt32, float>("SetHue", "ColorComponent", papyrusColorComponent::SetHue, registry));

	registry->RegisterFunction(
		new NativeFunction2 <StaticFunctionTag, UInt32, UInt32, float>("SetSaturation", "ColorComponent", papyrusColorComponent::SetSaturation, registry));

	registry->RegisterFunction(
		new NativeFunction2 <StaticFunctionTag, UInt32, UInt32, float>("SetLuminosity", "ColorComponent", papyrusColorComponent::SetLuminosity, registry));
}
 
void papyrusColorForm::RegisterFuncs(VMClassRegistry* registry)
{
	registry->RegisterForm(BGSColorForm::kTypeID, "ColorForm");

	registry->RegisterFunction(
		new NativeFunction0 <BGSColorForm, UInt32>("GetColor", "ColorForm", papyrusColorForm::GetColor, registry));
}
