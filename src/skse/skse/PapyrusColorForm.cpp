#include "PapyrusColorForm.h"
 
#include "GameForms.h"
#include "GameObjects.h"
#include "GameRTTI.h"
 
#define MIN3(x,y,z)  ((y) <= (z) ? ((x) <= (y) ? (x) : (y)) : ((x) <= (z) ? (x) : (z)))
#define MAX3(x,y,z)  ((y) >= (z) ? ((x) >= (y) ? (x) : (y)) : ((x) >= (z) ? (x) : (z)))
 
struct HSVColor {
	double	h; // Hue between 0 and 1.0
	double	s; // Saturation between 0 and 1.0
	double	v; // Lum between 0 and 1.0
	double	a; // Alpha between 0 and 1.0
};

struct RGBColor {
	UInt8 a;
	UInt8 r;
	UInt8 g;
	UInt8 b;
};

HSVColor GetHSV(RGBColor rgb)
{
	double r,g,b, rgb_max, rgb_min, delta, h, s;
	r = rgb.r / 255.0;
	g = rgb.g / 255.0;
	b = rgb.b / 255.0;
	rgb_max = MAX3(r, g, b);
	rgb_min = MIN3(r, g, b);
	delta = rgb_max - rgb_min;
	h = 0;
	s = 0;

	if ( rgb_max != 0.0 )
		s = delta / rgb_max;

	if ( s != 0.0 )
	{
		double rc = (rgb_max - r) / delta;
		double gc = (rgb_max - g) / delta;
		double bc = (rgb_max - b) / delta;

		if ( r == rgb_max )
			h = bc - gc;
		else if ( g == rgb_max )
			h = 2.0f + rc - bc;
		else if ( b == rgb_max )
			h = 4.0f + gc - rc;

		h *= 60.0f;
		if ( h < 0.0 )
			h += 360.0f;
	}

	HSVColor out;
	out.a = rgb.a / 255.0;
	out.h = h;
	out.s = s;
	out.v = rgb_max;
	return out;
}

RGBColor GetRGBFromHSV(HSVColor hsv)
{
	double h,s,v;
	double r,g,b,a;

	a = hsv.a;
	h = hsv.h;
	s = hsv.s;
	v = hsv.v;

	if (h < 0.0)
		h += 360.0;

	if (s != 0.0) {
		double f, p, q, t;
		if (h == 360.0)
			h = 0.0;
		h /= 60.0;

		int i = (int)h;
		f = h - i;
		p = v * (1.0 - s);
		q = v * (1.0 - (s * f));
		t = v * (1.0 - (s * (1.0 - f)));

		switch (i) {
			case 0: r = v;	g = t;	b = p;	break;
			case 1: r = q;	g = v;	b = p;	break;
			case 2: r = p;	g = v;	b = t;	break;
			case 3: r = p;	g = q;	b = v;	break;
			case 4: r = t;	g = p;	b = v;	break;
			case 5: r = v;	g = p;	b = q;	break;
		}
	}
	else {
		r = v;
		g = v;
		b = v;
	}

	RGBColor out;
	out.a = a * 255;
	out.r = r * 255;
	out.g = g * 255;
	out.b = b * 255;
	return out;
}

namespace papyrusColorComponent
{
	UInt32 GetAlpha(StaticFunctionTag* base, UInt32 argb)
	{
		return (argb & 0xFF000000) >> 24;
	}
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
		HSVColor hsl = GetHSV(rgb);
		return hsl.h;
	}
	float GetSaturation(StaticFunctionTag* base, UInt32 argb)
	{
		RGBColor rgb;
		rgb.r = GetRed(NULL, argb);
		rgb.g = GetGreen(NULL, argb);
		rgb.b = GetBlue(NULL, argb);
		HSVColor hsl = GetHSV(rgb);
		return hsl.s;
	}
	float GetValue(StaticFunctionTag* base, UInt32 argb)
	{
		RGBColor rgb;
		rgb.r = GetRed(NULL, argb);
		rgb.g = GetGreen(NULL, argb);
		rgb.b = GetBlue(NULL, argb);
		HSVColor hsv = GetHSV(rgb);
		return hsv.v;
	}
	UInt32 SetColor(StaticFunctionTag* base, UInt32 red, UInt32 green, UInt32 blue, UInt32 alpha)
	{
		return (alpha << 24) | (red << 16) | (green << 8) | blue;
	}
	UInt32 SetAlpha(StaticFunctionTag* base, UInt32 argb, UInt32 alpha)
	{
		return (argb & ~0xFF000000) | (alpha << 24);
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
		rgb.a = GetAlpha(NULL, argb);
		HSVColor hsl = GetHSV(rgb);
		hsl.h = hue;
		RGBColor newRgb = GetRGBFromHSV(hsl);
		return (newRgb.a << 24 | newRgb.r << 16 | newRgb.g << 8 | newRgb.b);
	}
	UInt32 SetSaturation(StaticFunctionTag* base, UInt32 argb, float sat)
	{
		RGBColor rgb;
		rgb.r = GetRed(NULL, argb);
		rgb.g = GetGreen(NULL, argb);
		rgb.b = GetBlue(NULL, argb);
		rgb.a = GetAlpha(NULL, argb);
		HSVColor hsv = GetHSV(rgb);
		hsv.s = sat;
		RGBColor newRgb = GetRGBFromHSV(hsv);
		return (newRgb.a << 24 | newRgb.r << 16 | newRgb.g << 8 | newRgb.b);
	}
	UInt32 SetValue(StaticFunctionTag* base, UInt32 argb, float val)
	{
		RGBColor rgb;
		rgb.r = GetRed(NULL, argb);
		rgb.g = GetGreen(NULL, argb);
		rgb.b = GetBlue(NULL, argb);
		rgb.a = GetAlpha(NULL, argb);
		HSVColor hsv = GetHSV(rgb);
		hsv.v = val;
		RGBColor newRgb = GetRGBFromHSV(hsv);
		return (newRgb.a << 24 | newRgb.r << 16 | newRgb.g << 8 | newRgb.b);
	}
};

namespace papyrusColorForm
{
	UInt32 GetColor(BGSColorForm* colorForm)
	{
		return (colorForm) ? (MACRO_SWAP32(colorForm->abgr) >> 8) | (colorForm->color.alpha << 24) : 0;
	}

	void SetColor(BGSColorForm* colorForm, UInt32 color)
	{
		colorForm->color.red = (color & 0x00FF0000) >> 16;
		colorForm->color.green = (color & 0x0000FF00) >> 8;
		colorForm->color.blue = (color & 0x000000FF);
	}
}

#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"

void papyrusColorComponent::RegisterFuncs(VMClassRegistry* registry)
{
	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, UInt32, UInt32>("GetAlpha", "ColorComponent", papyrusColorComponent::GetRed, registry));

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
		new NativeFunction1 <StaticFunctionTag, float, UInt32>("GetValue", "ColorComponent", papyrusColorComponent::GetValue, registry));

	registry->RegisterFunction(
		new NativeFunction2 <StaticFunctionTag, UInt32, UInt32, UInt32>("SetAlpha", "ColorComponent", papyrusColorComponent::SetAlpha, registry));

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
		new NativeFunction2 <StaticFunctionTag, UInt32, UInt32, float>("SetValue", "ColorComponent", papyrusColorComponent::SetValue, registry));

	registry->SetFunctionFlags("ColorComponent", "GetAlpha", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("ColorComponent", "GetRed", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("ColorComponent", "GetGreen", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("ColorComponent", "GetBlue", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("ColorComponent", "GetHue", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("ColorComponent", "GetSaturation", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("ColorComponent", "GetValue", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("ColorComponent", "SetAlpha", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("ColorComponent", "SetRed", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("ColorComponent", "SetGreen", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("ColorComponent", "SetBlue", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("ColorComponent", "SetHue", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("ColorComponent", "SetSaturation", VMClassRegistry::kFunctionFlag_NoWait);
	registry->SetFunctionFlags("ColorComponent", "SetValue", VMClassRegistry::kFunctionFlag_NoWait);
}

void papyrusColorForm::RegisterFuncs(VMClassRegistry* registry)
{
	registry->RegisterForm(BGSColorForm::kTypeID, "ColorForm");

	registry->RegisterFunction(
		new NativeFunction0 <BGSColorForm, UInt32>("GetColor", "ColorForm", papyrusColorForm::GetColor, registry));

	registry->RegisterFunction(
		new NativeFunction1 <BGSColorForm, void, UInt32>("SetColor", "ColorForm", papyrusColorForm::SetColor, registry));
}
