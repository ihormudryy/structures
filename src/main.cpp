#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

//#define WIDTH 300
//#define HEIGHT 300
/*
static Bool WaitForNotify(Display *d, XEvent *e, char *arg)
{
    return (e->type == MapNotify) && (e->xmap.window == (Window)arg);
}
*/

int main()
{
#ifdef __EMSCRIPTEN__
    EM_ASM( allReady() );
#endif
    std::cout << "HELLO EMSCRIPTEN" << std::endl;
 //   Display *dpy;
//    Window win;
//    GLXContext PBufferCtx;
//    GLXContext WinCtx;
//    GLXPbuffer PBuffer;
//    const int sBufferAttrib[] = {
//        GLX_DOUBLEBUFFER, 0,
//        GLX_RED_SIZE, 1,
//        GLX_GREEN_SIZE, 1,
//        GLX_BLUE_SIZE, 1,
//        GLX_DEPTH_SIZE, 12,
//        None
//    };

//    const int pBufferAttrib[] = {
//        GLX_PBUFFER_WIDTH, WIDTH,
//        GLX_PBUFFER_HEIGHT, HEIGHT,
//        GLX_PRESERVED_CONTENTS, True,
//        None
//    };

//    GLXFBConfig* fbc;
//    XVisualInfo* vi = NULL;
//    Colormap cmap;
//    XSetWindowAttributes swa;
//    XEvent event;
//    Bool bufferRedraw = False;
//    int	dummy;
//    int nElements;
//    int nval;
//    int nCounter;

 //   dpy = XOpenDisplay(NULL);
//    if (dpy != NULL) return -1;
//    //std::cout << "Info:GLX Extensions: " << glXQueryExtensionsString(dpy, DefaultScreen(dpy)) << std::endl;
    return 0;
}
