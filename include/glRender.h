#ifndef GLRENDER_HPP
#define GLRENDER_HPP

#ifdef __cplusplus
extern "C"{
#endif
    #include "shader_c/fragShader.c"
    #include "shader_c/vertexShader.c"
#ifdef __cplusplus
}
#endif

#include "glShader.h"
#include <gc_vdk.h>
#include <stdio.h>
#include <string.h>

extern int screenWidth;
extern int screenHeight;

class glRender{
private:
    typedef enum class _glTextUnit : GLenum{
        RGB = 0,
        YUY2
    }glTextUnit;
    GLuint VAO;
    GLuint VBO[2];
    GLuint attrIndex[2];
    GLuint textUnit_YUY2, textUnit_RGB;

    glProgramObjectFromC programe;

    void glAttribInit(void);

public:
    glRender(/* args */);
    ~glRender();
    void glInit(void);
    void imageRender(int width, int height, const unsigned char * const buf);

};

#endif