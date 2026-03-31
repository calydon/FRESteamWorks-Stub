#ifndef FRE_MINIMAL_H
#define FRE_MINIMAL_H

#include <stdint.h>

typedef void* FREContext;
typedef void* FREObject;

typedef struct {
    const uint8_t* name;
    void* functionData;
    void* function;
} FRENamedFunction;

// Minimal FREResult type
typedef int32_t FREResult;

// Minimal declaration for FRENewObjectFromBool
FREResult FRENewObjectFromBool(uint32_t value, FREObject* result);

// Rename typedefs to avoid collisions with exported function names
typedef void (*FREContextInitializerFunc)(
    void* extData,
    const uint8_t* ctxType,
    FREContext ctx,
    uint32_t* numFunctionsToSet,
    const FRENamedFunction** functionsToSet
);

typedef void (*FREContextFinalizerFunc)(
    FREContext ctx
);

typedef void (*FREExtensionInitializerFunc)(
    void** extDataToSet,
    FREContextInitializerFunc* ctxInitializerToSet,
    FREContextFinalizerFunc* ctxFinalizerToSet
);

typedef void (*FREExtensionFinalizerFunc)(
    void* extData
);

#endif
