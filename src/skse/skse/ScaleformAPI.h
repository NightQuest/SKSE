#pragma once

typedef void * (* _ScaleformHeap_Allocate)(UInt32 size);
extern const _ScaleformHeap_Allocate ScaleformHeap_Allocate;

typedef void (* _ScaleformHeap_Free)(void * ptr);
extern const _ScaleformHeap_Free ScaleformHeap_Free;
