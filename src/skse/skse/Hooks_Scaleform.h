#pragma once

#include "skse/PluginAPI.h"

void SetLastControlDown(const char * control);
void SetLastControlUp(const char * control);

void Hooks_Scaleform_Commit(void);

bool RegisterScaleformPlugin(const char * name, SKSEScaleformInterface::RegisterCallback callback);
