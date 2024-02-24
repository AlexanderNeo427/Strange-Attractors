#include <raylib-cpp.hpp>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#undef RAYGUI_IMPLEMENTATION

// Include all scenes here
#include "Scenes/SceneAttractors3D.h"
#include "Scenes/SceneAttractors2D/SceneAttractors2D.h"

#include "Application.h"

int main()
{
    auto* app = new Application();
    app->Init();

    while (!app->ShouldClose())
    {
        app->Run(GetFrameTime());
    }

    delete app;
    return 0;
}

