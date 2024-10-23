#include <stdio.h>
#include <gc_vdk.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2rename.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>

#define EGL_WIDTH 1920
#define EGL_HEIGHT 1080
#define TUTORIAL_NAME "OpenGL ES 2.0 Tutorial 1"

class VDKEGL{
private:
    vdkEGL egl;
    void FinishEGL(void);
public:
    VDKEGL(/* args */);
    void InitEGL(void);
    void SwapEGL(void);
    ~VDKEGL();
};