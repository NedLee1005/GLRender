#define vertShader(...) #__VA_ARGS__
static const char IMG_VERTEX_SHADER[] = vertShader(#version 330 core\n
    precision highp float;

    attribute vec3 inVImgPositionCoor;
    attribute vec3 inVImgColorCoor;
    attribute vec2 inVImgTextureCoor;

    varying vec3 vImgColor;
    varying vec2 vImgTexCoor;

    uniform mat4 transform;
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 proJ;

    void main(){
        // proJ * view * model *
        gl_Position = proJ * view * model * vec4(inVImgPositionCoor, 1.0);
        // gl_Position = transform * vec4(inVImgPositionCoor, 1.0);
        vImgColor = inVImgColorCoor;
        vImgTexCoor = inVImgTextureCoor;
    }
);
static const char IMG_VERTEX_SHADER1[] = vertShader(#version 330 core\n
    layout (location = 0) in vec3 position;
    layout (location = 1) in vec3 color;
    layout (location = 2) in vec2 texCoord;

    out vec3 ourColor;
    out vec2 TexCoord;

    void main()
    {
        gl_Position = vec4(position, 1.0f);
        ourColor = color;
        TexCoord = texCoord;
}
);
static const char IMG_BASIC_VERTEX_SHADER[] = vertShader(#version 100\n
    precision highp float;
    attribute vec3 vPosition;
    attribute vec2 a_texCoord;
    varying vec2 tc;
    void main()
    {
        gl_Position = vec4(vPosition, 1.0);
        tc = a_texCoord;
    }
);
static const char IMG_NV12_VERTEX_SHADER[] = vertShader(#version 100\n
    precision highp float;
    attribute vec3 vPosition;  // attribute
    attribute vec2 a_texCoord;
    varying vec2 tc;        // varying
    void main()
    {
        gl_Position = vec4(vPosition, 1.0);
        tc = a_texCoord;
    }
);