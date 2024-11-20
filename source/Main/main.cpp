#include "../World/World.hpp"
#include <windows.h>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    srand((unsigned)time(NULL));
    World w;
    w.build();
    debug_print("Build finished.\n");
    if(w.tracer_ptr == NULL){
        printf("Tracer null. Aborting.\n");
        return 1;
    }
    if(w.camera == NULL){
        printf("Camera null. Aborting.\n");
        return 1;
    }
    w.camera->render_scene(w);
    printf("Main thread terminated.\n");
    return 0;
}