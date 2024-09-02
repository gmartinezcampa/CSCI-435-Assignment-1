#ifndef ANNOTATINGPICS_H
#define ANNOTATINGPICS_H

#include <MagickWand/MagickWand.h>

void drawYellowBox(MagickWand *wand, int x, int y, int width, int height);
void annotateScreenshot(const char *inputImage, const char *outputImage, int boxData[][4], int boxCount);

#endif