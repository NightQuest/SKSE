Scriptname Weather extends Form Hidden

; Tells the sky to release its overriding weather. 
function ReleaseOverride() native global

; Forces the active weather on the sky to be this weather.
function ForceActive( bool abOverride=false ) native

; Sets the active weather on the sky to be this weather.
function SetActive( bool abOverride=false, bool abAccelerate=false ) native

; Finds a weather from the current region/climate whose classification matches the given one.
; 0 - Pleasant
; 1 - Cloudy
; 2 - Rainy
; 3 - Snow
Weather function FindWeather( int auiType ) native global

; Gets this weather's classification
; -1 - No classification
;  0 - Pleasant
;  1 - Cloudy
;  2 - Rainy
;  3 - Snow
int function GetClassification() native

; Gets the sky's current weather
Weather function GetCurrentWeather() native global

; Gets the sky's outgoing weather
Weather function GetOutgoingWeather() native global

; Gets the transition percentage of the current weather
float function GetCurrentWeatherTransition() native global

; Gets the sky's current mode
; 0 - No sky (SM_NONE)
; 1 - Interior (SM_INTERIOR)
; 2 - Skydome only (SM_SKYDOME_ONLY)
; 3 - Full sky (SM_FULL)
int function GetSkyMode() native global

; SKSE additions built 2015-05-24 00:46:48.937000 UTC

; Returns the sun glare percentage
float Function GetSunGlare() native

; Returns the sun damage percentage
float Function GetSunDamage() native

; Returns the wind direction in degrees (0-360)
float Function GetWindDirection() native

; Returns the wind direction range in degrees (0-180)
float Function GetWindDirectionRange() native

; 0 - Near
; 1 - Far
; 2 - Power
; 3 - Max
float Function GetFogDistance(bool day, int type) native
