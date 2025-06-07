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


    Music* thxSound;
    Font* debugFont;

    Image* nekoLogo;
    Palette* islandJoyPal;


    SceneName activeScene;

    // Scenes
    void LogoScene();
    void CubeScene();

};
