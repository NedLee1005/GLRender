#include <stdio.h>
#include <stdlib.h>
#include "glRender.h"
#include "glVDK.h"

vdkEGL egl;
glRender showCamera; 

int main(int argc, char* args[]){
    init_egl(&egl);
    showCamera.glInit();
    unsigned char * buf = (unsigned char*)calloc(1920 * 720 * 2, sizeof(unsigned char));
    while (true){
        showCamera.imageRender(1280, 720, buf);
        swap_egl(&egl);
    }
    free(buf);
    finish_egl(&egl);
    return 0;
}