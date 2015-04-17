#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

#if defined __linux__ && !defined __ANDROID__

#include <GL/gl.h>
#include <GL/glx.h>

#include <bmp_generator.h>

#define WIDTH 800
#define HEIGHT 600

using namespace std;
using namespace testtools;

typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
typedef Bool (*glXMakeContextCurrentARBProc)(Display*, GLXDrawable, GLXDrawable, GLXContext);
static glXCreateContextAttribsARBProc glXCreateContextAttribsARB = NULL;
static glXMakeContextCurrentARBProc   glXMakeContextCurrentARB   = NULL;

const int singleBufferAttributess[] =
{
    GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
    GLX_RENDER_TYPE, GLX_RGBA_BIT,
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

int context_attribs[] = {
    GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
    GLX_CONTEXT_MINOR_VERSION_ARB, 1,
    GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_DEBUG_BIT_ARB,
    GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
    None
};

void drawCube()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(true);
    glFrontFace(GL_CCW);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_DITHER);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glViewport(0, 0, WIDTH, HEIGHT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushAttrib(GL_TRANSFORM_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum(-1.0,1.0,-1.0,1.0,1.0,100.0);
    glPopAttrib();
    glPushAttrib(GL_TRANSFORM_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.0,0.0,-3);
        glRotatef(45,1.0,0.0,0.0);
        glRotatef(45,0.0,1.0,0.0);
        glRotatef(45,0.0,0.0,1.0);
    glPopAttrib();
    glBegin(GL_TRIANGLES);
        glColor3f(0.0,1.0,0.0);    // Color Blue
        glVertex3f( 1.0, 1.0,-1.0);    // Top Right Of The Quad (Top)
        glVertex3f(-1.0, 1.0,-1.0);    // Top Left Of The Quad (Top)
        glVertex3f(-1.0, 1.0, 1.0);    // Bottom Left Of The Quad (Top)
        glVertex3f( 1.0, 1.0, 1.0);    // Bottom Right Of The Quad (Top)
        glColor3f(1.0,0.5,0.0);    // Color Orange
        glVertex3f( 1.0,-1.0, 1.0);    // Top Right Of The Quad (Bottom)
        glVertex3f(-1.0,-1.0, 1.0);    // Top Left Of The Quad (Bottom)
        glVertex3f(-1.0,-1.0,-1.0);    // Bottom Left Of The Quad (Bottom)
        glVertex3f( 1.0,-1.0,-1.0);    // Bottom Right Of The Quad (Bottom)
        glColor3f(1.0,0.0,0.0);    // Color Red
        glVertex3f( 1.0, 1.0, 1.0);    // Top Right Of The Quad (Front)
        glVertex3f(-1.0, 1.0, 1.0);    // Top Left Of The Quad (Front)
        glVertex3f(-1.0,-1.0, 1.0);    // Bottom Left Of The Quad (Front)
        glVertex3f( 1.0,-1.0, 1.0);    // Bottom Right Of The Quad (Front)
        glColor3f(1.0,1.0,0.0);    // Color Yellow
        glVertex3f( 1.0,-1.0,-1.0);    // Top Right Of The Quad (Back)
        glVertex3f(-1.0,-1.0,-1.0);    // Top Left Of The Quad (Back)
        glVertex3f(-1.0, 1.0,-1.0);    // Bottom Left Of The Quad (Back)
        glVertex3f( 1.0, 1.0,-1.0);    // Bottom Right Of The Quad (Back)
        glColor3f(0.0,0.0,1.0);    // Color Blue
        glVertex3f(-1.0, 1.0, 1.0);    // Top Right Of The Quad (Left)
        glVertex3f(-1.0, 1.0,-1.0);    // Top Left Of The Quad (Left)
        glVertex3f(-1.0,-1.0,-1.0);    // Bottom Left Of The Quad (Left)
        glVertex3f(-1.0,-1.0, 1.0);    // Bottom Right Of The Quad (Left)
        glColor3f(1.0,0.0,1.0);    // Color Violet
        glVertex3f( 1.0, 1.0,-1.0);    // Top Right Of The Quad (Right)
        glVertex3f( 1.0, 1.0, 1.0);    // Top Left Of The Quad (Right)
        glVertex3f( 1.0,-1.0, 1.0);    // Bottom Left Of The Quad (Right)
        glVertex3f( 1.0,-1.0,-1.0);    // Bottom Right Of The Quad (Right)
    glEnd();
    glFlush();
}

void readBufferToFile(char* name)
{
    GLubyte* data = new GLubyte[WIDTH*3*HEIGHT];
    glReadBuffer(GL_FRONT);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ROW_LENGTH, 0);
    glPixelStorei(GL_PACK_SKIP_ROWS, 0);
    glPixelStorei(GL_PACK_SKIP_PIXELS, 0);
    glCopyPixels(0, 0, WIDTH, HEIGHT, GL_COLOR);
    glReadPixels(0, 0, WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, data);

    FILE* filePtr = fopen(name, "wb");
    ASSERT_TRUE(filePtr != NULL);
    BmpGenerator::write_bmp24(filePtr, WIDTH, HEIGHT, data);
    fclose(filePtr);
}

TEST(TestOffScreenRendering, TestWindowLessContext)
{
    int nElements;
    glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc) glXGetProcAddressARB
                                 ((const GLubyte*) "glXCreateContextAttribsARB");
    glXMakeContextCurrentARB   = (glXMakeContextCurrentARBProc) glXGetProcAddressARB
                                 ((const GLubyte*) "glXMakeContextCurrent");
    ASSERT_TRUE(glXGetProcAddressARB != NULL);
    ASSERT_TRUE(glXMakeContextCurrentARB != NULL);

    Display* dpy;
    dpy = XOpenDisplay( NULL );

    ASSERT_TRUE(dpy != NULL);

    GLXFBConfig* fbConfigs = glXChooseFBConfig(dpy,
                                               DefaultScreen(dpy),
                                               doubleBufferAttributes,
                                               &nElements);
    if (fbConfigs == NULL) fbConfigs = glXChooseFBConfig(dpy,
                                                DefaultScreen(dpy),
                                                singleBufferAttributess,
                                                &nElements);
/*
    GLXContext openGLContext = glXCreateContextAttribsARB(dpy,
                                                          fbConfigs[0],
                                                          0,
                                                          True,
                                                          context_attribs);

    ASSERT_TRUE(openGLContext != NULL);

    GLXPbuffer pbuffer = glXCreatePbuffer(dpy, fbConfigs[0], pBufferAttrib);
    XFree(fbConfigs);
    XSync(dpy, False);

    glXMakeContextCurrent(dpy, pbuffer, pbuffer, openGLContext);

    drawCube();
    glXSwapBuffers(dpy, pbuffer);
    readBufferToFile("test_image_PBuffer_No_Window.bmp");

    glXMakeCurrent(dpy, None, NULL);
    glXDestroyContext(dpy, openGLContext);*/
    XCloseDisplay(dpy);
}

TEST(TestOffScreenRendering, TestRenderToOffscreenBuffer)
{
    Display *dpy;
    Window xWin;
    GLXWindow glxWin;
    GLXContext PBufferContext;
    GLXContext context;
    GLXPbuffer PBuffer;
    GLXFBConfig* fbConfigs;
    XVisualInfo* vi = NULL;
    Colormap cmap;
    XSetWindowAttributes swa;
    int	dummy;
    int nElements;

    dpy = XOpenDisplay(NULL);

    ASSERT_TRUE(dpy != NULL);

    ASSERT_TRUE(glXQueryExtension(dpy, &dummy, &dummy));

    fbConfigs = glXChooseFBConfig(dpy,
                                  DefaultScreen(dpy),
                                  doubleBufferAttributes,
                                  &nElements);
    if (fbConfigs == NULL) fbConfigs = glXChooseFBConfig(dpy,
                                  DefaultScreen(dpy),
                                  singleBufferAttributess,
                                  &nElements);

    ASSERT_GT(nElements, 0);

    vi = glXGetVisualFromFBConfig(dpy, fbConfigs[0]);

    context = glXCreateContext(dpy, vi, None, True);

    ASSERT_TRUE(context != NULL);

    PBuffer = glXCreatePbuffer(dpy, fbConfigs[0], pBufferAttrib);

    ASSERT_TRUE(PBuffer != NULL);

    PBufferContext = glXCreateNewContext(dpy, fbConfigs[0], GLX_RGBA_TYPE, 0, GL_TRUE);

    ASSERT_TRUE(PBufferContext != NULL);

    cmap = XCreateColormap(dpy, RootWindow(dpy,vi->screen), vi->visual, AllocNone);

    swa.colormap = cmap;
    swa.border_pixel = 0;
    swa.event_mask = ExposureMask | ButtonPressMask | StructureNotifyMask;

    xWin = XCreateWindow(dpy,
                         RootWindow(dpy,vi->screen), 0, 0,
                         WIDTH, HEIGHT, 0,
                         vi->depth,
                         InputOutput,
                         vi->visual,
                         CWBorderPixel | CWColormap | CWEventMask,
                         &swa);
    glxWin = glXCreateWindow(dpy, fbConfigs[0], xWin, NULL);

    //XMapWindow(dpy, xWin);
    XStoreName(dpy, xWin, "TestRenderToOffscreenBuffer");
    glXMakeContextCurrent( dpy, PBuffer, PBuffer, PBufferContext);

    drawCube();
    glXSwapBuffers(dpy, PBuffer);
    readBufferToFile("test_image_PBuffer.bmp");
    glXMakeCurrent(dpy, None, NULL);
    XDestroyWindow(dpy, xWin);
    XCloseDisplay(dpy);
}

TEST(TestOffScreenRendering, TextRenderToWindowContextWithoutMapping)
{
    Display* dpy;
    Window xWin;
    XVisualInfo* vInfo;
    XSetWindowAttributes swa;
    GLXFBConfig *fbConfigs;
    GLXContext winCtx;
    GLXWindow glxWin;
    int swaMask;
    int numReturned;
    XEvent xev;
    XWindowAttributes gwa;
    Colormap cmap;
    dpy = XOpenDisplay(NULL);

    if (dpy == NULL)
    {
        printf( "Unable to open a connection to the X server\n" );
        exit(EXIT_FAILURE);
    }

    fbConfigs = glXChooseFBConfig(dpy,
                                  DefaultScreen(dpy),
                                  doubleBufferAttributes,
                                  &numReturned);

    if (fbConfigs == NULL)
    {
        fbConfigs = glXChooseFBConfig(dpy,
                                      DefaultScreen(dpy),
                                      singleBufferAttributess,
                                      &numReturned);
    }

    vInfo = glXGetVisualFromFBConfig(dpy, fbConfigs[0]);

    ASSERT_TRUE(vInfo != NULL);

    swa.border_pixel = 0;
    swa.event_mask = StructureNotifyMask;
    cmap = XCreateColormap(dpy, RootWindow(dpy, vInfo->screen), vInfo->visual, AllocNone);
    swa.colormap = cmap;

    swaMask = CWBorderPixel | CWColormap | CWEventMask;
    swa.event_mask = ExposureMask | KeyPressMask;

    xWin = XCreateWindow( dpy, RootWindow(dpy, vInfo->screen), 0, 0, WIDTH, HEIGHT,
                              0, vInfo->depth, InputOutput, vInfo->visual,
                              swaMask, &swa );

    winCtx = glXCreateNewContext(dpy, fbConfigs[0], GLX_RGBA_TYPE, NULL, True);
    glxWin = glXCreateWindow(dpy, fbConfigs[0], xWin, NULL);

    //XMapWindow(dpy, xWin);
    glXMakeContextCurrent(dpy, glxWin, glxWin, winCtx);

    drawCube();
    glXSwapBuffers(dpy, glxWin);
    readBufferToFile("test_image2.bmp");
    //sleep(2);
    glXMakeCurrent(dpy, None, NULL);
    glXDestroyContext(dpy, winCtx);
    XDestroyWindow(dpy, xWin);
    XCloseDisplay(dpy);
}

TEST(TestOffScreenRendering, TextRenderToWindow)
{
    Display              *dpy;
    Window                xWin;
    XEvent                event;
    XVisualInfo          *vInfo;
    XSetWindowAttributes  swa;
    GLXFBConfig          *fbConfigs;
    GLXContext            context;
    GLXWindow             glxWin;
    int                   swaMask;
    int                   numReturned;
    int                   swapFlag = True;

    /* Open a connection to the X server */
    dpy = XOpenDisplay( NULL );
    fbConfigs = glXChooseFBConfig( dpy, DefaultScreen(dpy),
                                   doubleBufferAttributes, &numReturned );

    if ( fbConfigs == NULL ) {
      fbConfigs = glXChooseFBConfig( dpy, DefaultScreen(dpy),
                                     singleBufferAttributess, &numReturned );
      swapFlag = False;
    }

    vInfo = glXGetVisualFromFBConfig( dpy, fbConfigs[0] );

    swa.border_pixel = 0;
    swa.event_mask = StructureNotifyMask;
    swa.colormap = XCreateColormap( dpy, RootWindow(dpy, vInfo->screen),
                                    vInfo->visual, AllocNone );

    swaMask = CWBorderPixel | CWColormap | CWEventMask;

    xWin = XCreateWindow( dpy, RootWindow(dpy, vInfo->screen), 0, 0, WIDTH, HEIGHT,
                          0, vInfo->depth, InputOutput, vInfo->visual,
                          swaMask, &swa );

    //* Create a GLX context for OpenGL rendering */
    context = glXCreateNewContext( dpy, fbConfigs[0], GLX_RGBA_TYPE,
                 NULL, True );

    /* Create a GLX window to associate the frame buffer configuration
    ** with the created X window */
    glxWin = glXCreateWindow( dpy, fbConfigs[0], xWin, NULL );

    /* Map the window to the screen, and wait for it to appear */
    //XMapWindow( dpy, xWin );
    //XIfEvent( dpy, &event, WaitForNotify, (XPointer) xWin );

    /* Bind the GLX context to the Window */
    glXMakeContextCurrent( dpy, glxWin, glxWin, context );

    /* OpenGL rendering ... */
    glClearColor( 1.0, 1.0, 0.0, 1.0 );
    glClear( GL_COLOR_BUFFER_BIT );
    drawCube();
    if ( swapFlag )
        glXSwapBuffers( dpy, glxWin );
    //readBufferToFile("test_image3.bmp");
    glXMakeCurrent(dpy, None, NULL);
    glXDestroyContext(dpy, context);
    //XDestroyWindow(dpy, glxWin);
    XCloseDisplay(dpy);
}

#endif // linux && !android
