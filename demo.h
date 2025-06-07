#pragma once

#include <mgdl.h>
enum SceneName
{
    LOGO = 0,
    CUBEMIST = 1,
    MENU = 2
};

class Demo
{
public:
    void Init();
    void Update();
    void Draw();

    void DrawCube();

    Music* thxSound;
    Mesh* icosaMesh;
    Scene* icosaScene;
    Font* debugFont;


    SceneName activeScene;

    // Scenes
    void LogoScene();

};
