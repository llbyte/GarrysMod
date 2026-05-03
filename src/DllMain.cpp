#include <windows.h>
#include <DllLauncher/CDllLauncher.hpp>

BOOL APIENTRY DllMain(
    const HMODULE hInstance,
    const DWORD reason,
    const void* lpReserved
) {
    switch (reason) {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hInstance);
            GetDllLauncher()->OnDllMain(lpReserved, hInstance);
            break;

        case DLL_PROCESS_DETACH:
            GetDllLauncher()->OnDestroy();
            break;

        default:
            break;
    }

    return TRUE;
}