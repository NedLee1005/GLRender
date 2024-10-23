#define fragShader(...) #__VA_ARGS__
static const char IMG_FRAG_SHADER[] = fragShader(#version 330 core\n
    precision highp float;

    uniform sampler2D ourTexture;
    uniform sampler2D ourTexture1;

    varying vec3 vImgColor;
    varying vec2 vImgTexCoor;

    uniform int change;

    void main(){
        if (change == 0){
            gl_FragColor = texture(ourTexture, vImgTexCoor) * vec4(vImgColor, 1.0f);
        }
        else if(change == 1){
            gl_FragColor = texture(ourTexture1, vImgTexCoor);
        }
        else{
            gl_FragColor = mix(texture(ourTexture, vImgTexCoor), texture(ourTexture1, vImgTexCoor), 0.5);
        }
        
        // gl_FragColor = texture(ourTexture1, vImgTexCoor);
    }
);
static const char IMG_FRAG_SHADER1[] = fragShader(#version 330 core\n
    in vec3 ourColor;
    in vec2 TexCoord;

    out vec4 color;

    uniform sampler2D ourTexture1;
    uniform sampler2D ourTexture2;

    uniform int change = 0;
    void main()
    {
        if (change == 0){
            color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.5);
        }
        else{
            color = texture(ourTexture1, TexCoord);
        }
    }
);

static const char IMG_BASIC_FRAG_SHADER[] = fragShader(\n
    precision highp float;
    varying highp vec2 tc;
    uniform sampler2D u_image;
    void main(void)
    {
        vec4 image = texture2D(u_image, tc);
        gl_FragColor = vec4(image.bgr, 1.0);
        //gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);
    }
);

static const char IMG_NV12_FRAG_SHADER[] = fragShader(#version 100\n
    precision highp float;
    varying highp vec2 tc;

    uniform sampler2D text_y;
    uniform sampler2D text_uv;
    float test; // test
    void main(void)
    {
        float test;
        test = mod(test, 2.0);    // test
        vec3 yuv;
        vec3 rgb;
        yuv.x = texture2D(text_y, tc).r;    // y
        yuv.y = texture2D(text_uv, tc).r - 0.5; // u
        yuv.z = texture2D(text_uv, tc).a - 0.5; // v

        rgb = mat3(1,         1,        1, //BT.601
                   0,   -0.3455,    1.779,    
              1.4075,   -0.7169,        0) * yuv;
        gl_FragColor = vec4(clamp(rgb, 0.0, 1.0), 1.0);
        //gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);
    }
);

static const char IMG_YUY2_FRAG_SHADER[] = fragShader(#version 100\n
    precision highp float;
    varying highp vec2 tc;

    uniform sampler2D text_YUYV;
    uniform ivec2 text_YUYV_size;

    void main(void)
    {

        float pixelCoords_x = tc.x * float(text_YUYV_size.x) * 2.0; // pixel coordinates, width : 0. ~ 1280., height : 0. ~ 720.
        
        vec4 yuyv = texture2D(text_YUYV, tc).rgba;

        vec3 yuv;
        vec3 rgb;
        float rb = mod(pixelCoords_x, 2.0);
        if (rb == 1.0)    yuv.x = yuyv.r;
        else yuv.x = yuyv.b;
        yuv.y = yuyv.g - 0.5;
        yuv.z = yuyv.a - 0.5;

        rgb = mat3(1,         1,        1, //BT.601
                   0,   -0.3455,    1.779,    
              1.4075,   -0.7169,        0) * yuv;

        gl_FragColor = vec4(clamp(rgb, 0.0, 1.0), 1.0);
        // gl_FragColor = vec4(yuyv.rgb, 1.0);
        // gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);
    }
);