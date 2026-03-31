#include <Windows.h>
#include "FlashRuntimeExtensions.h"

static void log_to_file(const char* msg)
{
    HANDLE h = CreateFileA(
        "C:\\Users\\teams\\Desktop\\FRESteamWorks_log.txt",
        FILE_APPEND_DATA,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    if (h == INVALID_HANDLE_VALUE) return;

    DWORD written;
    WriteFile(h, msg, (DWORD)lstrlenA(msg), &written, NULL);
    WriteFile(h, "\r\n", 2, &written, NULL);
    CloseHandle(h);
}

// Forward declaration so the compiler knows the symbol before use
FREObject AIRSteam_Init_stub(FREContext ctx, void* data, uint32_t argc, FREObject argv[]);

// ------------------------------------------------------------
// AIRSteam_Init stub — always returns TRUE
// ------------------------------------------------------------
/* FREObject AIRSteam_Init_stub(FREContext ctx, void* data, uint32_t argc, FREObject argv[])
{
    log_to_file("AIRSteam_Init_stub called");

    FREObject result = NULL;
    FRENewObjectFromBool(1, &result);   // return true
    return result;
} */
FREObject AIRSteam_Init_stub(FREContext ctx, void* data, uint32_t argc, FREObject argv[])
{
    log_to_file("AIRSteam_Init_stub called");

    // Return a non-NULL pointer so AS3 sees "true"
    return (FREObject)1;
}


// ------------------------------------------------------------
// Context initializer — registers AIRSteam_Init
// ------------------------------------------------------------
void ContextInitializerImpl(void* extData,
                            const uint8_t* ctxType,
                            FREContext ctx,
                            uint32_t* numFunctionsToSet,
                            const FRENamedFunction** functionsToSet)
{
    log_to_file("ContextInitializerImpl called");

    static FRENamedFunction functions[1];

    functions[0].name = (const uint8_t*)"AIRSteam_Init";
    functions[0].functionData = NULL;
    functions[0].function = (void*)&AIRSteam_Init_stub;

    *numFunctionsToSet = 1;
    *functionsToSet = functions;
}

void ContextFinalizerImpl(FREContext ctx)
{
    log_to_file("ContextFinalizerImpl called");
}

// ------------------------------------------------------------
// Exported AIR-required symbols (cdecl)
// ------------------------------------------------------------
__declspec(dllexport) void FREExtensionInitializer(
    void** extDataToSet,
    FREContextInitializerFunc* ctxInitializerToSet,
    FREContextFinalizerFunc* ctxFinalizerToSet)
{
    log_to_file("FREExtensionInitializer called");

    *extDataToSet = NULL;
    *ctxInitializerToSet = &ContextInitializerImpl;
    *ctxFinalizerToSet = &ContextFinalizerImpl;
}

__declspec(dllexport) void FREExtensionFinalizer(void* extData)
{
    log_to_file("FREExtensionFinalizer called");
}

__declspec(dllexport) void FREContextInitializer(
    void* extData,
    const uint8_t* ctxType,
    FREContext ctx,
    uint32_t* numFunctionsToSet,
    const FRENamedFunction** functionsToSet)
{
    log_to_file("FREContextInitializer exported wrapper called");
    ContextInitializerImpl(extData, ctxType, ctx, numFunctionsToSet, functionsToSet);
}

__declspec(dllexport) void FREContextFinalizer(FREContext ctx)
{
    log_to_file("FREContextFinalizer exported wrapper called");
    ContextFinalizerImpl(ctx);
}
