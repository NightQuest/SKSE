Scriptname Armor extends Form Hidden


; SKSE additions built 2012-04-14 06:33:02.075000 UTC
int Function GetArmorRating() native
int Function GetAR()
	return GetArmorRating()
endFunction

Function SetArmorRating(int armorRating) native
Function SetAR(int armorRating)
	return SetArmorRating(armorRating)
endFunction

Function ModArmorRating(int modBy) native
Function ModAR(int modBy)
	return ModArmorRating(modBy)
endFunction