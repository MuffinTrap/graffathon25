#include "demo.h"
#include "drawBox.h"
#define MGDL_ROCKET

#ifdef MGDL_ROCKET
#include <mgdl/mgdl-rocket.h>

#ifdef SYNC_PLAYER
    #include MGDL_ROCKET_FILE_H
    //#include MGDL_ROCKET_FILE_CPP
#else
    static ROCKET_TRACK scene;
    static ROCKET_TRACK clear_i;


    static ROCKET_TRACK logo_pentaBorder;
    static ROCKET_TRACK logo_pentaRadius;
    static ROCKET_TRACK logo_pentaScale;
    static ROCKET_TRACK logo_pentaScaleStep;
    static ROCKET_TRACK logo_pentaRotation;
    static ROCKET_TRACK logo_pentaRotationStep;
    static ROCKET_TRACK logo_pentaIntensity;
    static ROCKET_TRACK logo_pentaSharpness;
    static ROCKET_TRACK logo_pentaAmount;

    static ROCKET_TRACK logo_nekoScale;
    static ROCKET_TRACK logo_nekoY;
    static ROCKET_TRACK logo_nekoColor;

    static ROCKET_TRACK logo_textY;
    static ROCKET_TRACK logo_textColor;
    static ROCKET_TRACK logo_textSize;

    // Cube mist scene
    static ROCKET_TRACK mist_camera_distance;
    static ROCKET_TRACK mist_camera_roll;
    static ROCKET_TRACK mist_cube_scale;
    static ROCKET_TRACK mist_cube_colorLerp;
    static ROCKET_TRACK mist_cube_light;

    static ROCKET_TRACK mist_text_scale;

#endif

#endif


static u32 islandColors[] = {
    0xffffffff, // 0 white
    0x6df7c1ff, // 1 turkoosi
    0x11adc1ff, // 2 skyblue
    0x606c81ff, // 3 grey
    0x393457ff, // 4 darkblue
    0x1e8875ff, // 5 green
    0x5bb361ff, // 6 grass green
    0xa1e55aff, // 7 yellow green
    0xf7e476ff, // 8 yellow
    0xf99252ff, // 9 orange
    0xcb4d68ff, // 10 rose
    0x6a3771ff, // 11 purple
    0xc92464ff, // 12 red
    0xf48cb6ff, // 13 pink
    0xf7b69eff, // 14 peach
    0x9b9c82ff //  15 olive
};

static const int cubeAmount = 40;
static const int textAmount = 4;

static const char* texts[] = {
    "Made by\nmuffintrap",
    "using C++\nand mtek-gdl",
    "audio made\nwith MiniDexed",
    "for Graffathon\n2025"
};

void Demo::Init()
{

    thxSound = LoadOgg("assets/graffathon_thx.ogg");

    debugFont = Font_GetDebugFont();


    nekoLogo = LoadImage("assets/neko_logo.png", TextureFilterModes::Nearest);
    islandJoyPal = Palette_Create(islandColors, 16);

#ifdef MGDL_ROCKET
    bool rocketInit = Rocket_Init(thxSound, 120, 4);
    if (rocketInit == false)
    {
        mgdl_DoProgramExit();
    }
#ifndef SYNC_PLAYER
    scene = Rocket_AddTrack("scene");
    clear_i = Rocket_AddTrack("clear_i");

    logo_pentaBorder = Rocket_AddTrack("logo:pentaBorder");
    logo_pentaRadius = Rocket_AddTrack("logo:pentaRadius");
    logo_pentaScale = Rocket_AddTrack("logo:pentaScale");
    logo_pentaScaleStep = Rocket_AddTrack("logo:pentaScaleStep");
    logo_pentaRotation = Rocket_AddTrack("logo:pentaRotation");
    logo_pentaRotationStep = Rocket_AddTrack("logo:pentaRotationStep");
    logo_pentaIntensity = Rocket_AddTrack("logo:pentaIntensity");
    logo_pentaSharpness = Rocket_AddTrack("logo:pentaSharpness");
    logo_pentaAmount = Rocket_AddTrack("logo:pentaAmount");

    logo_nekoScale = Rocket_AddTrack("logo:nekoScale");
    logo_nekoY = Rocket_AddTrack("logo:nekoY");
    logo_nekoColor = Rocket_AddTrack("logo:nekoColor");
    logo_textY = Rocket_AddTrack("logo:textY");
    logo_textColor = Rocket_AddTrack("logo:textColor");
    logo_textSize = Rocket_AddTrack("logo:textSize");


    mist_camera_distance = Rocket_AddTrack("mist:camera_distance");
    mist_camera_roll = Rocket_AddTrack("mist:camera_roll");
    mist_cube_scale = Rocket_AddTrack("mist:cube_scale");
    mist_cube_colorLerp = Rocket_AddTrack("mist:cube_colorLerp");
    mist_cube_light = Rocket_AddTrack("mist:cube_light");

    mist_text_scale = Rocket_AddTrack("mist:text_scale");

#endif
    Rocket_StartSync();
#endif

    // Randomize cube positions
    srand(100);
    float z = 200.0f;
    cubePositions = (float*)malloc(sizeof(float) * cubeAmount * 3);
    float xylimit = 100;
    for (int i = 0; i  < (cubeAmount-1)*3; i += 3)
    {
        cubePositions[i+0] =  gdl::GetRandomFloat(-xylimit, xylimit);
        cubePositions[i+1] =  gdl::GetRandomFloat(-xylimit, xylimit);
        cubePositions[i+2] = z;
        z -= (400.0f/(float)cubeAmount);
    }


    textPositions = (float*)malloc(sizeof(float) * textAmount * 3);
    z= 200.0f;
    for (int i = 0; i  < (textAmount)*3; i += 3)
    {
        textPositions[i+0] =  gdl::GetRandomFloat(-8, 8);
        textPositions[i+1] =  gdl::GetRandomFloat(-12, 12);
        textPositions[i+2] = z;
        z -= (400.0f/(float)textAmount);
    }


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
    activeScene = (SceneName)Rocket_Int(scene);
    switch(activeScene)
    {
        case LOGO:
            LogoScene();

            break;
        case CUBEMIST:
            CubeScene();

            break;

        case QUIT:

            break;
    }

    mgdl_InitOrthoProjection();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

static float fogColor[4] = {0,0,0,0};

void Demo::CubeScene()
{
    mgdl_InitPerspectiveProjection(75.0f, 0.1f, 100.0f);
    mgdl_InitCamera(V3f_Create(0.0f, 0.0f, 1.0f),
                    V3f_Create(0.0f, 0.0f, 0.0f),
                    V3f_Create(0.0f, 1.0f, 0.0f));

    float bgInt= Rocket_Float(clear_i);
    Color4f clearCol = Palette_GetColor4f(islandJoyPal, 4 );
    glClearColor(clearCol.red * bgInt, clearCol.green * bgInt, clearCol.blue * bgInt, 1.0f);
    mgdl_glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE); //  is this needed?

	// This is the other way around on Wii, but
	// hopefully OpenGX handles it
    /*
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    */
    glShadeModel(GL_FLAT);

    fogColor[0] = clearCol.red;
    fogColor[1] = clearCol.green;
    fogColor[2] = clearCol.blue;
    fogColor[3] = clearCol.alpha;


    Color4f cubecol = Palette_GetColor4f(islandJoyPal, 4 );
    Color4f cubecol2 = Palette_GetColor4f(islandJoyPal, 2 );

    glPushMatrix(); // Camera roll

    // float elp = mgdl_GetElapsedSeconds();
    //glRotatef(elp * sceneRotation.x * 10.0f, 1.0f, 0.0f, 0.0f);
    // glRotatef(elp * sceneRotation.y * 10.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(Rocket_Float(mist_camera_roll), 0.0f, 0.0f, 1.0f);
    int lightCube = Rocket_Int(mist_cube_light);

    float cs = Rocket_Float(mist_cube_scale);
    for (int i = 0; i < cubeAmount-1; i++)
    {
    glPushMatrix(); // Cubes
        glScalef(cs, cs, cs);
        float x  = cubePositions[i * 3 + 0];
        float y  = cubePositions[i * 3 + 1];
        float z  = cubePositions[i * 3 + 2];
        z += Rocket_Float(mist_camera_distance);
        glTranslatef(x, y, z);
        glRotatef(x, 1.0f, 0.0f, 0.0f);
        glRotatef(y, 0.0f, 1.0f, 0.0f);
        glRotatef(z, 0.0f, 0.0f, 1.0f);

        if (i == lightCube)
        {
            glColor3f(1.0f, 1.0f, 1.0f);
        }
        else
        {

        float lerp = Rocket_Float(mist_cube_colorLerp);
        float mlerp = (1.0f - lerp);
        glColor3f(mlerp * cubecol.red + lerp *cubecol2.red,
                mlerp * cubecol.green + lerp *cubecol2.green,
                mlerp * cubecol.blue + lerp *cubecol2.green);
        }

        SolidCube(10.0f);

        glPopMatrix(); // Cubes
    }

    glPopMatrix(); // Camera roll

    u32 yellow = Palette_GetColor(islandJoyPal, 8);
    float ts = Rocket_Float(mist_text_scale);

    for (int i = 0; i < textAmount; i++)
    {
        glPushMatrix(); // texts
        glScalef(ts, ts, ts);
        float x  = textPositions[i * 3 + 0];
        float y  = textPositions[i * 3 + 1];
        float z  = textPositions[i * 3 + 2];
        z += Rocket_Float(mist_camera_distance);
        glTranslatef(x, y, z);

        Font_PrintOrigo(debugFont, yellow, 1.0f, Centered, Centered, texts[i]);

        glPopMatrix(); // texts
    }

    glDisable(GL_DEPTH_TEST);
}

void Demo::LogoScene()
{
    mgdl_InitOrthoProjection();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float bgInt= Rocket_Float(clear_i);
    glClearColor(bgInt, bgInt, bgInt, 1.0f);
    mgdl_glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    float pi = Rocket_Float(logo_pentaIntensity);
    float ps = Rocket_Float(logo_pentaScale);
    float ss = Rocket_Float(logo_pentaScaleStep);
    float pr = Rocket_Float(logo_pentaRotation);
    float rs = Rocket_Float(logo_pentaRotationStep);
    float border = Rocket_Float(logo_pentaBorder);
    float radius = Rocket_Float(logo_pentaRadius);
    float sharp = Rocket_Float(logo_pentaSharpness);

    static u8 colors[] = {2, 1, 8, 12};

    glPushMatrix();
    glTranslatef(mgdl_GetScreenWidth()/2, mgdl_GetScreenHeight()/2, 0.0f);

    // Palette* defP = Palette_GetDefault();
    int pa = Rocket_Int(logo_pentaAmount);

    for (int i = 0; i < pa; i++)
    {
        Color4f pc = Palette_GetColor4f(islandJoyPal, colors[i % 4]);


        glPushMatrix();
        glScalef(ps + ss * i, ps + ss * i, 1.0f);
        glRotatef(pr + rs * i, 0.0f, 0.0f, 1.0f);
        glColor3f(pc.red * pi, pc. green * pi, pc.blue * pi);

        // Draw star borders
        Mesh_DrawStarBorder(border,
                            radius,
                            sharp,
                            5);

        glPopMatrix();
    }
    glPopMatrix();

    mgdl_glSetTransparency(true);
    // Draw Cat logo
    Color4f catColor = Palette_GetColor4f(islandJoyPal, Rocket_Int(logo_nekoColor));
    Image_SetTint(nekoLogo, catColor.red, catColor.green, catColor.blue);
    Image_Draw2DAligned(nekoLogo, mgdl_GetScreenWidth()/2, Rocket_Int(logo_nekoY), Rocket_Float(logo_nekoScale), Centered, Centered);

    mgdl_glSetTransparency(false);
    // Draw text FCCCF

    u32 textColor = Palette_GetColor(islandJoyPal, Rocket_Int(logo_textColor));
    Font_PrintAligned(debugFont, textColor,
                      mgdl_GetScreenWidth()/2,
                      Rocket_Int(logo_textY),
                      Rocket_Int(logo_textSize),
                      Centered, Centered, "STATION");
}

bool Demo::WantQuit()
{
    return activeScene == QUIT;
}



