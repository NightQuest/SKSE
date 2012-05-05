Scriptname SKSE Hidden
; General SKSE-specific information

; get the major version of SKSE
int Function GetVersion() global native
; get the minor version of SKSE
int Function GetVersionMinor() global native
; get the beta version of SKSE
int Function GetVersionBeta() global native
; get the release index of SKSE.  This number is incremented every time
; SKSE is released outside of the development team
int Function GetVersionRelease() global native
