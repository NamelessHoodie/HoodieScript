#pragma once

#include <cstdio>
#include "logging.h"
#include "minhook/MinHook.h"
#include "goods_use_hook.h"
#include "Ds3LuaHelper.h"

void attach();
void detach();
void prepare_console();
void free_console();

hoodie_script::goods_use_hook *goodsUseHook = nullptr;