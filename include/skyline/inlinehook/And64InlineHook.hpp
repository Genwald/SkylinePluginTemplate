#pragma once

extern "C" void A64HookFunction(void *const symbol, void *const replace, void **result);
extern "C" void A64InlineHook(void* const symbol, void* const replace);

struct InlineCtx {
    nn::os::CpuRegister registers[29];
};