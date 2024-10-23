#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include "glRender.h"
#include "glVDK.h"

// vdkEGL  egl_s;
VDKEGL  egl;
GLRender showCamera; 

int main(int argc, char* args[]){
    FILE * fp;
    unsigned char * buf = (unsigned char*)malloc(1280 * 720 * 2 * sizeof(unsigned char));
    fp = fopen("output3_2.yuv", "rb");
    fread(buf, sizeof(unsigned char), 1280 * 720 * 2, fp);
    egl.InitEGL();
    showCamera.Init();
    while (true){
        showCamera.ImageRender(1280, 720, buf);
        egl.SwapEGL();
    }
    free(buf);
    fclose(fp);
    return 0;
}