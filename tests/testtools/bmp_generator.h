#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

#if defined __linux__ && !defined __ANDROID__

#include <GL/gl.h>
#include <GL/glx.h>

#pragma once

#ifndef BMP_GENERATOR_H
#define BMP_GENERATOR_H

namespace testtools
{
class BmpGenerator
{
public:
    static void write_bmp24(FILE*, int, int, GLubyte*);
    static void write_bmpheader(FILE *fp, int width, int height, int& pad, int& rasterwidth);
    static void write_bmpimage(FILE *fp, int width, int height, GLubyte* pixels, int& pad, int& rasterwidth);
    static unsigned char *int2word(int number);
    static unsigned char *int2long(unsigned char *longnum, int number);
    static void checkvalues(int width, int height, GLubyte* pixels);
    static void write_u_long_int(unsigned long int u_long_int_val, FILE* fp);
    static void write_u_short_int(unsigned short int u_short_int_val, FILE* fp);
    struct template_bmpheader{
        int reserved[2];
        int headersize;
        int bfsize;
    };
    struct template_bmpfile{
        unsigned long bmpsize;
        unsigned long bmpwidth;
        unsigned long bmpheight;
        unsigned short int biplanes;
        unsigned short int bitcount;
        unsigned long bicompression;
        unsigned long bisizeimage;
        unsigned long bixpelspermeter;
        unsigned long biypelspermeter;
        unsigned long biclrused;
        unsigned long biclrimportant;
    };
    //static int pad;
    //static int rasterwidth;
};

} // namespace testtols

#endif // BMP_GENERATOR_H
#endif // LINUX
