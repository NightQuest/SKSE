#include "GameAPI.h"

const _FormHeap_Allocate FormHeap_Allocate = (_FormHeap_Allocate)0x00402460;
const _FormHeap_Free FormHeap_Free = (_FormHeap_Free)0x00402420;

PlayerCharacter	** g_thePlayer = (PlayerCharacter **)0x01588324;
