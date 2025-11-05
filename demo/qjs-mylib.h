#pragma once

#include <quickjs.h>

#ifdef __cplusplus
extern "C" {
#endif

    JSModuleDef *js_init_module_mylib(JSContext *ctx, const char *module_name);

#ifdef __cplusplus
}
#endif