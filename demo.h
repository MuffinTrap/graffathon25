#pragma once

#include <mgdl.h>
enum SceneName
{
    LOGO = 0,
    CUBEMIST = 1,
    QUIT = 99
};

class Demo
{
public:
    void Init();
    void Update();
    void Draw();
    bool WantQuit();


    Music* thxSound;
    Font* debugFont;

    Image* nekoLogo;
    Palette* islandJoyPal;

    Mesh* cubeMesh;

    float* cubePositions;
    float* textPositions;

    SceneName activeScene;

    // Scenes
    void LogoScene();
    void CubeScene();

};
