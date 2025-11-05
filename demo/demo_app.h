#include "quickjs.h"


class DemoApp
{
public:
    bool init(int argc, char *argv[]);
    int run();

private:
    void cleanup();

private:
    JSRuntime *m_runtime;
    JSContext *m_ctx;
};