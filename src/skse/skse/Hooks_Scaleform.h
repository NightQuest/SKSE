#pragma once

#include "skse/PluginAPI.h"

void Hooks_Scaleform_Commit(void);

bool RegisterScaleformPlugin(const char * name, SKSEScaleformInterface::RegisterCallback callback);

