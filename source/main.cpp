#include "main.hpp"

void (*originalNpadStateHandheldFunc)(nn::hid::NpadHandheldState *state, u32 const &controllerID);
void GetNpadStateHandheldHook(nn::hid::NpadHandheldState *state, u32 const &controllerID) {
    originalNpadStateHandheldFunc(state, controllerID);
    if(state->Buttons & nn::hid::KEY_A) {
        skyline::TcpLogger::SendRaw("[NpadStateHook] A button pressed\n");
    }
}

Result (*originalOpenFileFunc)(nn::fs::FileHandle *file, char const* path, s32 mode);
Result openFileHook(nn::fs::FileHandle *file, char const* path, s32 mode) {
    skyline::TcpLogger::SendRawFormat("[openFileHook] opened file %s\n", path);
    return originalOpenFileFunc(file, path, mode);
}

int main() {
        skyline::TcpLogger::SendRaw("HELLO FROM PLUGIN\n");

        // look up the function by symbol because it is an overloaded function
        u64 GetNpadStateHandheldAddr;
        nn::ro::LookupSymbol(&GetNpadStateHandheldAddr, "_ZN2nn3hid12GetNpadStateEPNS0_17NpadHandheldStateERKj");
        // Hook to log when the A button is pressed in hadnheld state
        A64HookFunction(
            reinterpret_cast<void*>(GetNpadStateHandheldAddr),
            reinterpret_cast<void*>(GetNpadStateHandheldHook),
            (void**) &originalNpadStateHandheldFunc
        );

        // This function has no overloads, so we don't need to look it up by its symbol
        // Hook to log the name of every opened file
        A64HookFunction(
            reinterpret_cast<void*>(nn::fs::OpenFile),
            reinterpret_cast<void*>(openFileHook),
            (void**) &originalOpenFileFunc
        );

}
