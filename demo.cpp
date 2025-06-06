#include "demo.h"
#define MGDL_ROCKET

#ifdef MGDL_ROCKET
#include <mgdl/mgdl-rocket.h>

#ifdef SYNC_PLAYER
    #include MGDL_ROCKET_FILE_H
    //#include MGDL_ROCKET_FILE_CPP
#else
    static ROCKET_TRACK cube_scale;
    static ROCKET_TRACK camera_distance;
#endif

#endif

    static Color4f pink;

void Demo::Init()
{

    thxSound = LoadOgg("assets/graffathon_thx.ogg");
    icosaMesh = Mesh_CreateIcosahedron(0);
    icosaScene = Scene_CreateEmpty();

    debugFont = Font_GetDebugFont();

    RGBA8Floats p = gdl::ColorToFloats(Palette_GetColor(Palette_GetDefault(), 1));
    pink = {p.red, p.green, p.blue, p.alpha};



    mgdl_assert_print(debugFont != nullptr, "No debug font");
#ifdef MGDL_ROCKET
    bool rocketInit = Rocket_Init(thxSound, 120, 4);
    if (rocketInit == false)
    {
        mgdl_DoProgramExit();
    }
#ifndef SYNC_PLAYER
    cube_scale = Rocket_AddTrack("cube_scale");
    camera_distance = Rocket_AddTrack("camera:distance");
#endif
    Rocket_StartSync();
#endif

}

void Demo::Update()
{
    Rocket_UpdateRow();

#ifndef SYNC_PLAYER

    if (WiiController_ButtonPress(Platform_GetController(0), WiiButtons::Button2))
    {
       Rocket_SaveAllTracks();
    }
#endif
}


void Demo::Draw()
{
    mgdl_InitOrthoProjection();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    Font_Printf(debugFont, Colors::White, 10, 16, 16, "Cube scale %.2f", Rocket_Float(cube_scale));
    //Font_Print(debugFont, Colors::White, 10, 16, 16, "Cube scale");

    DrawCube();



}

void Demo::DrawCube()
{

    mgdl_InitPerspectiveProjection(75.0f, 0.1f, 100.0f);
    mgdl_InitCamera(V3f_Create(0.0f, 0.0f, Rocket_Float(camera_distance)), V3f_Create(0.0f, 0.0f, 0.0f), V3f_Create(0.0f, 1.0f, 0.0f));

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE); //  is this needed?



	// This is the other way around on Wii, but
	// hopefully OpenGX handles it
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glShadeModel(GL_FLAT);

    glColor3f(1.0f, 1.0f, 1.0f);

    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.0f);
    float cs = Rocket_Float(cube_scale);
    glScalef(cs, cs, cs);
    //glutSolidCube(10.0);
    Mesh_DrawElements(icosaMesh);
    mgdl_glColor4f(pink);
    Mesh_DrawLines(icosaMesh);
    /*
    float elp = mgdl_GetElapsedSeconds();
    glRotatef(elp * sceneRotation.x * 10.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(elp * sceneRotation.y * 10.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(elp * sceneRotation.z * 10.0f, 0.0f, 0.0f, 1.0f);
    glScalef(scale.x, scale.y, scale.z);

    Scene_Draw(scene);
    */

    glPopMatrix();
    glDisable(GL_DEPTH_TEST);
}


