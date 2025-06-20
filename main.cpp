#include <mgdl.h>

#include "demo.h"

static Demo demo;

void init()
{
    glViewport(0, 0, mgdl_GetScreenWidth(), mgdl_GetScreenHeight());
    mgdl_InitOrthoProjection();


    demo.Init();

}
// Rendering callback. glFlush etc.. is done automatically after it
void render()
{
    demo.Draw();
}


// Called before render()
void update()
{
    if (WiiController_ButtonPress(Platform_GetController(0), WiiButtons::ButtonHome))
    {
        mgdl_DoProgramExit();
    }
    demo.Update();

    if (demo.WantQuit())
    {
        mgdl_DoProgramExit();
    }
}

int main()
{
    u32 flags = gdl::PlatformInitFlag::FlagFullScreen;
    mgdl_InitSystem(MGDL_PLATFORM,
        gdl::ScreenAspect::Screen4x3,
        init,
        update,  // std::function callbacks
        render,
        flags
    );
}
