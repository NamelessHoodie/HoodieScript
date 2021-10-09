#pragma once

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
