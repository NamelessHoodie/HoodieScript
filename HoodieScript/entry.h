#pragma once

#include <cstdio>
#include "logging.h"
#include "minhook/MinHook.h"
#include "Hooks/goods_use_hook.h"
#include "Ds3LuaHelper.h"

void attach();
void detach();
void prepare_console();
void free_console();

//Thanks Sfix from ?servername? for providing the original template function.
template<typename T, typename ...Ts>
inline T* mlp(void* base, Ts... offsets) {
    const auto len = sizeof...(Ts);
    const int offsets_unpacked[len] = { offsets... };

    for (unsigned i = 0; i < len; i++) {
        if (*(uintptr_t*)base == 0) {
            return (T*)nullptr;
        }
        else {
            base = (T*)(*(uintptr_t*)base + offsets_unpacked[i]);
        }
    }

    return (T*)base;
}


hoodie_script::goods_use_hook *goodsUseHook = nullptr;