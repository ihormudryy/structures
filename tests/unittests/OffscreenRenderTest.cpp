#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#ifdef __linux__

#include <GL/gl.h>
#include <GL/glx.h>

#define WIDTH 300
#define HEIGHT 300

static Bool WaitForNotify(Display *d, XEvent *e, char *arg)
{
    return (e->type == MapNotify) && (e->xmap.window == (Window)arg);
}

void redraw(GLXPbuffer& PBuffer,
            GLXContext& PBufferContext,
            Display* dpy,
            Window& win,
            GLXContext& WinContext)
{
    static Bool bFirstPass=True;

    if(bFirstPass)
    {
        bFirstPass=False;
        glXMakeContextCurrent( dpy, PBuffer, PBuffer, PBufferContext);
        glMatrixMode(GL_MODELVIEW);	/* switch to model matrix stack */
        glLoadIdentity();	/* reset modelview matrix to identity */
        glTranslatef(0.0,0.0,-3.0);	/* move camera back 3 units */
        glClearColor(1.0,0.0,0.0,0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBegin(GL_QUADS);
        {
            glColor3f(0.0,0.7,0.1);
            glVertex3f(-1.0, 1.0, 1.0);
            glVertex3f( 1.0, 1.0, 1.0);
            glVertex3f( 1.0,-1.0, 1.0);
            glVertex3f(-1.0,-1.0, 1.0);
        }
        glEnd();
        glReadBuffer(GL_FRONT);
    }
    glXMakeContextCurrent( dpy, win, PBuffer, WinContext);

    glCopyPixels(0,0,WIDTH,HEIGHT,GL_COLOR);
    glFlush();
}

using namespace std;

TEST(TestOffScreenRendering, TestRenderToOffscreenBuffer)
{
    Display *dpy;
    Window win;
    GLXContext PBufferContext;
    GLXContext WinContext;
    GLXPbuffer PBuffer;
    const int singleBufferAttributess[] =
    {
        GLX_DRAWABLE_TYPE,
        GLX_WINDOW_BIT,
        GLX_RENDER_TYPE,
        GLX_RGBA_BIT,
        GLX_RED_SIZE,      1,
        GLX_GREEN_SIZE,    1,
        GLX_BLUE_SIZE,     1,
        None
    };

    const int doubleBufferAttributes[] =
    {
        GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
        GLX_RENDER_TYPE,   GLX_RGBA_BIT,
        GLX_DOUBLEBUFFER,  1,
        GLX_RED_SIZE,      1,
        GLX_GREEN_SIZE,    1,
        GLX_BLUE_SIZE,     1,
        None
    };

    const int pBufferAttrib[] = {
        GLX_PBUFFER_WIDTH, WIDTH,
        GLX_PBUFFER_HEIGHT, HEIGHT,
        GLX_PRESERVED_CONTENTS, True,
        None
    };

    GLXFBConfig* fbConfigs;
    XVisualInfo* vi = NULL;
    Colormap cmap;
    XSetWindowAttributes swa;
    XEvent event;
    Bool bufferRedraw = False;
    int	dummy;
    int nElements;
    int nval;
    int nCounter;
    dpy = XOpenDisplay(NULL);

    ASSERT_TRUE(dpy != NULL);

    cout << "Info: GLX Extensions: " << glXQueryExtensionsString(dpy, DefaultScreen(dpy)) << endl;

    ASSERT_TRUE(glXQueryExtension(dpy, &dummy, &dummy));

    fbConfigs = glXChooseFBConfig(dpy,
                                 DefaultScreen(dpy),
                                 doubleBufferAttributes,
                                 &nElements);
    if (fbConfigs == NULL) fbConfigs = glXChooseFBConfig(dpy,
                                          DefaultScreen(dpy),
                                          singleBufferAttributess,
                                          &nElements);
    cout << nElements << " configs found " << endl;
    ASSERT_GT(nElements, 0);

    vi = glXGetVisualFromFBConfig(dpy, fbConfigs[0]);

    WinContext = glXCreateContext(dpy, vi, None, True);

    ASSERT_TRUE(WinContext != NULL);

    PBuffer = glXCreatePbuffer(dpy, fbConfigs[0], pBufferAttrib);

    ASSERT_TRUE(PBuffer != NULL);

    PBufferContext = glXCreateNewContext( dpy, fbConfigs[0], GLX_RGBA_TYPE, 0, GL_TRUE);

    ASSERT_TRUE(PBufferContext != NULL);

    cmap = XCreateColormap(dpy, RootWindow(dpy,vi->screen), vi->visual, AllocNone);

    swa.colormap = cmap;
    swa.border_pixel = 0;
    swa.event_mask = ExposureMask | ButtonPressMask | StructureNotifyMask;

    win = XCreateWindow(dpy,
                        RootWindow(dpy,vi->screen), 0, 0,
                        WIDTH, HEIGHT, 0,
                        vi->depth,
                        InputOutput,
                        vi->visual,
                        CWBorderPixel | CWColormap | CWEventMask,
                        &swa);

    glXMakeContextCurrent( dpy, PBuffer, PBuffer, PBufferContext);

    XMapWindow(dpy, win);
    XIfEvent(dpy, &event, WaitForNotify, (char*)win);

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0,1.0,-1.0,1.0,1.0,10.0);
    glViewport(0, 0, event.xconfigure.width, event.xconfigure.height);
    redraw(PBuffer, PBufferContext, dpy, win, WinContext);
    //https://www.opengl.org/discussion_boards/showthread.php/146909-Pbuffers-GLX-linux-nVidia
}

#endif // linux
