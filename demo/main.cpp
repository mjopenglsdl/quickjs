#include "demo_app.h"


int main(int argc, char **argv)
{
    DemoApp app;

    app.init(argc, argv);
    return app.run();

    return 0;
}