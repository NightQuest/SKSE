Scriptname Ammo extends Form Hidden

; SKSE additions built 2014-12-23 07:36:08.038000 UTC

; Returns whether this ammo is a bolt
bool Function IsBolt() native

; Returns the projectile associated with this ammo
Projectile Function GetProjectile() native

; Returns the base damage of this ammo
float Function GetDamage() native
