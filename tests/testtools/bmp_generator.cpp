#include <bmp_generator.h>

#if defined __linux__ && !defined __ANDROID__

namespace testtools
{

void BmpGenerator::write_bmp24(FILE* fp, int width, int height, GLubyte* pixels)
{
    int rasterwidth;
    int pad;
    write_bmpheader(fp, width, height, pad, rasterwidth);
    write_bmpimage(fp, width, height, pixels, pad, rasterwidth);
}

void BmpGenerator::write_bmpheader(FILE* fp, int width, int height, int& pad, int& rasterwidth)
{
    template_bmpheader bmpheader;
    template_bmpfile bmpfile;
    int filesize, bfsize;
    int bytesperline, bmpnumbytes;
    bmpheader.reserved[0] = 0;
    bmpheader.reserved[1] = 0;
    bmpheader.headersize = 54;
    pad = ((width % 4) == 0) ? 0 : 4 - (width % 4);
    rasterwidth = width + pad;
    bmpnumbytes = 3 * rasterwidth * height;
    bmpheader.bfsize = sizeof(struct template_bmpheader) + sizeof(struct template_bmpfile) + bmpnumbytes;
    fputc('B', fp);
    fputc('M', fp);
    write_u_long_int(bmpheader.bfsize, fp);
    write_u_short_int(bmpheader.reserved[0], fp);
    write_u_short_int(bmpheader.reserved[1], fp);
    write_u_long_int(bmpheader.headersize, fp);
    bmpfile.bmpsize = 40;
    bmpfile.bmpwidth = rasterwidth;
    bmpfile.bmpheight = height;
    bmpfile.biplanes = 1;
    bmpfile.bitcount = 24;
    bmpfile.bicompression = 0;
    bmpfile.bisizeimage = 0;
    bmpfile.bixpelspermeter = 0;
    bmpfile.biypelspermeter = 0;
    bmpfile.biclrused = 0;
    bmpfile.biclrimportant = 0;
    write_u_long_int(bmpfile.bmpsize, fp);
    write_u_long_int(bmpfile.bmpwidth, fp);
    write_u_long_int(bmpfile.bmpheight, fp);
    write_u_short_int(bmpfile.biplanes, fp);
    write_u_short_int(bmpfile.bitcount, fp);
    write_u_long_int(bmpfile.bicompression, fp);
    write_u_long_int(bmpfile.bisizeimage, fp);
    write_u_long_int(bmpfile.bixpelspermeter, fp);
    write_u_long_int(bmpfile.biypelspermeter, fp);
    write_u_long_int(bmpfile.biclrused, fp);
    write_u_long_int(bmpfile.biclrimportant, fp);
}

void BmpGenerator::write_bmpimage (FILE* fp, int width, int height, GLubyte* pixels, int& pad, int& rasterwidth)
{

    int i, j, k, m, n;
    unsigned char zero = 0;
    unsigned char *curpix;
    curpix = (unsigned char *) pixels;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
            for (k = 0; k < 3; k++)
                fwrite(curpix++, 1, 1, fp);

        if (pad > 0)
        for (m = 0; m < pad; m++)
            for (n = 0; n < 3; n++)
                fwrite(&zero, 1, 1, fp);
    }
}

unsigned char* BmpGenerator::int2word(int number)
{
    unsigned char wordnum[2];

    wordnum[0] = (number & 0x00FF);
    wordnum[1] = ((number >> 8) & 0x00FF);

    return wordnum;
}

unsigned char* BmpGenerator::int2long(unsigned char *longnum, int number)
{
    longnum[0] = (number & 0x00FF);
    longnum[1] = ((number >> 8) & 0x000000FF);
    longnum[2] = ((number >> 16) & 0x000000FF);
    longnum[3] = ((number >> 24) & 0x000000FF);

    return longnum;
}

void BmpGenerator::write_u_long_int(unsigned long int value, FILE *fp)
{
    unsigned short int value_hi;
    unsigned short int value_lo;

    value_hi = (unsigned short) (value / 65536);
    value_lo = (unsigned short) (value % 65536);

    write_u_short_int(value_lo, fp);
    write_u_short_int(value_hi, fp);
}

void BmpGenerator::write_u_short_int(unsigned short int value, FILE *fp)
{
    unsigned char chi;
    unsigned char clo;

    chi = (unsigned char) (value / 256);
    clo = (unsigned char) (value % 256);

    fputc(clo, fp);
    fputc(chi, fp);
}

}

#endif // LINUX
