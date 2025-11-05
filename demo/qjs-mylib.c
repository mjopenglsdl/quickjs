#include <cutils.h>
#include <quickjs.h>

#include "qjs-mylib.h"


static JSValue js_mylib_mytest(JSContext *ctx, JSValueConst this_val,
                           int argc, JSValueConst *argv)
{
    int input_value, ret;
    if (JS_ToInt32(ctx, &input_value, argv[0]))
        return JS_EXCEPTION;
    ret = input_value + 100;
    return JS_NewInt32(ctx, ret);
}

static const JSCFunctionListEntry js_mylib_funcs[] = {
    JS_CFUNC_DEF("mytest", 1, js_mylib_mytest ),

};

int js_mylib_init(JSContext *ctx, JSModuleDef *m)
{
    return JS_SetModuleExportList(ctx, m, js_mylib_funcs, countof(js_mylib_funcs));
}

JSModuleDef *js_init_module_mylib(JSContext *ctx, const char *module_name)
{
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_mylib_init);
    if (!m)
        return NULL;

    JS_AddModuleExportList(ctx, m, js_mylib_funcs, countof(js_mylib_funcs));


    return m;
}