Scriptname Ammo extends Form Hidden

; SKSE additions built 2014-07-08 04:02:05.441000 UTC

; Returns whether this ammo is a bolt
bool Function IsBolt() native

; Returns the projectile associated with this ammo
Projectile Function GetProjectile() native

; Returns the base damage of this ammo
float Function GetDamage() native
