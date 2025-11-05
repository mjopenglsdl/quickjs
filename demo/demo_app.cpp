#include <cstring>

#include <quickjs.h>
#include <quickjs-libc.h>

#include "qjs-mylib.h"
#include "demo_app.h"


static JSContext *JS_NewCustomContext(JSRuntime *runtime)
{
    JSContext *ctx = JS_NewContext(runtime);
    if (!ctx)
        return NULL;

    js_init_module_mylib(ctx, "mylib");
    return ctx;
}


bool DemoApp::init(int argc, char *argv[])
{
    m_runtime = JS_NewRuntime();
    js_std_set_worker_new_context_func(JS_NewCustomContext);
    js_std_init_handlers(m_runtime);
    JS_SetModuleLoaderFunc(m_runtime, NULL, js_module_loader, NULL);

    m_ctx = JS_NewCustomContext(m_runtime);

    // add func: console
    js_std_add_helpers(m_ctx, argc, argv);

    return true;
}

int DemoApp::run()
{
    const char *code = R"(
        import { mytest } from 'mylib';  
        console.log("-------------");
        console.log("mytest(10): ", mytest(10));
    )";

    JSValue compiled = JS_Eval(m_ctx, code, strlen(code), "<input>", 
                                JS_EVAL_TYPE_MODULE | JS_EVAL_FLAG_COMPILE_ONLY);
    
    if (JS_ResolveModule(m_ctx, compiled) < 0) {  
        JS_FreeValue(m_ctx, compiled);  
        js_std_dump_error(m_ctx);  
        return -1;  
    }  

    JSValue result = JS_EvalFunction(m_ctx, compiled);
    if (JS_IsException(result)) {
        js_std_dump_error(m_ctx);
        JS_FreeValue(m_ctx, result);  
    }

    result = js_std_await(m_ctx, result);
    JS_FreeValue(m_ctx, result);
    js_std_loop(m_ctx);

    cleanup();
    
    return 0;
}

void DemoApp::cleanup()
{
    js_std_free_handlers(m_runtime);
    JS_FreeContext(m_ctx);
    JS_FreeRuntime(m_runtime);
}