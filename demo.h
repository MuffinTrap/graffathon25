#pragma once

#include <mgdl.h>

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

};
