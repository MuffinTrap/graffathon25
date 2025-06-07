#include "demo.h"
#define MGDL_ROCKET

#ifdef MGDL_ROCKET
#include <mgdl/mgdl-rocket.h>

#ifdef SYNC_PLAYER
    #include MGDL_ROCKET_FILE_H
    //#include MGDL_ROCKET_FILE_CPP
#else
    static ROCKET_TRACK clear_i;
    static ROCKET_TRACK cube_scale;
    static ROCKET_TRACK camera_distance;


    static ROCKET_TRACK logo_pentaBorder;
    static ROCKET_TRACK logo_pentaRadius;
    static ROCKET_TRACK logo_pentaScale;
    static ROCKET_TRACK logo_pentaIntensity;
    static ROCKET_TRACK logo_pentaSharpness;

#endif

#endif

    static Color4f pink;


void Demo::Init()
{

    thxSound = LoadOgg("assets/graffathon_thx.ogg");
    icosaMesh = Mesh_CreateIcosahedron(0);
    icosaScene = Scene_CreateEmpty();

    debugFont = Font_GetDebugFont();

    pink = ColorToFloats(Palette_GetColor(Palette_GetDefault(), 1));



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
    clear_i = Rocket_AddTrack("clear_i");

    logo_pentaBorder = Rocket_AddTrack("logo:pentaBorder");
    logo_pentaRadius = Rocket_AddTrack("logo:pentaRadius");
    logo_pentaScale = Rocket_AddTrack("logo:pentaScale");
    logo_pentaIntensity = Rocket_AddTrack("logo:pentaIntensity");
    logo_pentaSharpness = Rocket_AddTrack("logo:pentaSharpness");
#endif
    Rocket_StartSync();
#endif

    activeScene = LOGO;

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
    switch(activeScene)
    {
        case LOGO:
            LogoScene();

            break;
        case CUBEMIST:

            break;

        case MENU:

            break;
    }

    mgdl_InitOrthoProjection();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.4f, 0.4f, 0.39f, 1.0f);

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

void Demo::LogoScene()
{
    float bgInt= Rocket_Float(clear_i);
    glClearColor(bgInt, bgInt, bgInt, 1.0f);
    mgdl_glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    float pi = Rocket_Float(logo_pentaIntensity);
    float ps = Rocket_Float(logo_pentaScale);

    Palette* defP = Palette_GetDefault();
    Color4f pc = Palette_GetColor4f(defP, 4);


    glPushMatrix();
    glScalef(ps, ps, 1.0f);
    glColor3f(pc.red * pi, pc. green * pi, pc.blue * pi);

    // Draw star borders
    Mesh_DrawStarBorder(Rocket_Float(logo_pentaBorder),
                        Rocket_Float(logo_pentaRadius),
                        Rocket_Float(logo_pentaSharpness),
                        5);

    glPopMatrix();

    // Draw Cat logo

    // Draw text FCCCF
}


