#include "PapyrusColorForm.h"
 
#include "GameForms.h"
#include "GameObjects.h"
#include "GameRTTI.h"
 
#define MIN3(x,y,z)  ((y) <= (z) ? ((x) <= (y) ? (x) : (y)) : ((x) <= (z) ? (x) : (z)))
#define MAX3(x,y,z)  ((y) >= (z) ? ((x) >= (y) ? (x) : (y)) : ((x) >= (z) ? (x) : (z)))
 
struct HSVColor {
	UInt8 hue; // Hue between 0 and 255
	UInt8 sat; // Saturation between 0 and 255
	UInt8 val; // Value between 0 and 255
};
 
HSVColor GetHSV(BGSColorForm* colorForm) {
	HSVColor hsv;
	UInt8 rgb_min, rgb_max;
	rgb_min = MIN3(colorForm->color.red, colorForm->color.green, colorForm->color.blue);
	rgb_max = MAX3(colorForm->color.red, colorForm->color.green, colorForm->color.blue);

	// Value
	hsv.val = rgb_max;
	if(hsv.val == 0) {
		hsv.hue = hsv.sat = 0;
		return hsv;
	}

	// Saturation
	hsv.sat = 255 * long(rgb_max - rgb_min) / hsv.val;
	if(hsv.sat == 0) {
		hsv.hue = 0;
		return hsv;
	}

	// Hue
	if (rgb_max == colorForm->color.red)
		hsv.hue = 0 + 43 * (colorForm->color.green - colorForm->color.blue) / (rgb_max - rgb_min);
	else if (rgb_max == colorForm->color.green)
		hsv.hue = 85 + 43 * (colorForm->color.blue - colorForm->color.red) / (rgb_max - rgb_min);
	else
		hsv.hue = 171 + 43 * (colorForm->color.red - colorForm->color.green) / (rgb_max - rgb_min);

	return hsv;
}
 
namespace papyrusColorForm
{
	UInt32 GetRed(BGSColorForm* colorForm)
	{
		return (colorForm) ? colorForm->color.red : 0;
	}

	UInt32 GetGreen(BGSColorForm* colorForm)
	{
		return (colorForm) ? colorForm->color.green : 0;
	}

	UInt32 GetBlue(BGSColorForm* colorForm)
	{
		return (colorForm) ? colorForm->color.blue : 0;
	}

	// RGB aren't always the most useful values
	UInt32 GetHue(BGSColorForm* colorForm)
	{
		if(!colorForm)
			return 0;

		HSVColor hsv = GetHSV(colorForm);
		return hsv.hue;
	}

	UInt32 GetSaturation(BGSColorForm* colorForm)
	{
		if(!colorForm)
			return 0;

		HSVColor hsv = GetHSV(colorForm);
		return hsv.sat;
	}

	UInt32 GetLuminosity(BGSColorForm* colorForm)
	{
		if(!colorForm)
			return 0;

		HSVColor hsv = GetHSV(colorForm);
		return hsv.val;
	}
}
 
#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"
 
void papyrusColorForm::RegisterFuncs(VMClassRegistry* registry)
{
	registry->RegisterForm(BGSColorForm::kTypeID, "ColorForm");

	registry->RegisterFunction(
		new NativeFunction0 <BGSColorForm, UInt32>("GetRed", "ColorForm", papyrusColorForm::GetRed, registry));

	registry->RegisterFunction(
		new NativeFunction0 <BGSColorForm, UInt32>("GetGreen", "ColorForm", papyrusColorForm::GetGreen, registry));

	registry->RegisterFunction(
		new NativeFunction0 <BGSColorForm, UInt32>("GetBlue", "ColorForm", papyrusColorForm::GetBlue, registry));

	registry->RegisterFunction(
		new NativeFunction0 <BGSColorForm, UInt32>("GetHue", "ColorForm", papyrusColorForm::GetHue, registry));

	registry->RegisterFunction(
		new NativeFunction0 <BGSColorForm, UInt32>("GetSaturation", "ColorForm", papyrusColorForm::GetSaturation, registry));

	registry->RegisterFunction(
		new NativeFunction0 <BGSColorForm, UInt32>("GetLuminosity", "ColorForm", papyrusColorForm::GetLuminosity, registry));
}
