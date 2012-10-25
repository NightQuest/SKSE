Scriptname ColorForm extends Form Hidden

int Function GetColor() native

int Function GetRed()
	return ColorComponent.GetRed(Self.GetColor())
EndFunction

int Function GetGreen()
	return ColorComponent.GetGreen(Self.GetColor())
EndFunction

int Function GetBlue()
	return ColorComponent.GetBlue(Self.GetColor())
EndFunction

float Function GetHue()
	return ColorComponent.GetHue(Self.GetColor())
EndFunction

float Function GetSaturation()
	return ColorComponent.GetSaturation(Self.GetColor())
EndFunction

float Function GetLuminosity()
	return ColorComponent.GetLuminosity(Self.GetColor())
EndFunction