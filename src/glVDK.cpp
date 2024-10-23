#include "glVDK.h"

void VDKEGL::InitEGL(void){
    printf("init egl\n");	
    // egl = _egl;
    EGLint EGLerror = 0;
    EGLint configAttribs[] =
        {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_SAMPLES,      0,
            EGL_BUFFER_SIZE, 24,
            EGL_DEPTH_SIZE, 1,
            EGL_RED_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_ALPHA_SIZE, 8,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL_NONE
        };

    EGLint attribListContext[] =
    {
        // Needs to be set for es2.0 as default client version is es1.1.
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

    if (!vdkSetupEGL(0, 0, EGL_WIDTH, EGL_HEIGHT, configAttribs, NULL, attribListContext, &egl)) //1920 1080
    {
    	printf("EGL Error");
        // return 1;
    }
    vdkSetWindowTitle(egl.window, TUTORIAL_NAME);
    vdkShowWindow(egl.window);
}

void VDKEGL::SwapEGL(void){
    vdkSwapEGL(&egl);
}
void VDKEGL::FinishEGL(void){
    vdkFinishEGL(&egl);
}

VDKEGL::VDKEGL(/* args */){}

VDKEGL::~VDKEGL(){
    FinishEGL();
}
