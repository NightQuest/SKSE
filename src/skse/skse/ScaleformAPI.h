#pragma once

class GFxMovieView;
class FxResponseArgsList;

void * ScaleformHeap_Allocate(UInt32 size);
void ScaleformHeap_Free(void * ptr);

typedef void * (* _InvokeFunction)(GFxMovieView * movie, const char * fnName, FxResponseArgsList * arguments);
extern const _InvokeFunction InvokeFunction;