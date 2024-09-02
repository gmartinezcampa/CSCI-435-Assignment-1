// Name: Gisi Martinez-Campa
// Date: 9/2/2024
//
//
// This file is going to be used to draw the yellow boxes on pictures based on coordinates from parsingXML.c
//
//
#include <stdio.h>
#include "annotatingPics.h"

void drawYellowBox(MagickWand *wand, int x, int y, int width, int height) {
    DrawingWand *drawingWand = NewDrawingWand();
    PixelWand *pixelWand = NewPixelWand();

    // Set the color of pixelWand to yellow
    PixelSetColor(pixelWand, "yellow");


    // Set the border width of the drawingWand
    DrawSetStrokeWidth(drawingWand, 3);
    DrawSetStrokeColor(drawingWand, pixelWand);
    DrawSetFillOpacity(drawingWand, 0); // Transparent fill so that you can actually see the element

    // Draw the rectangle
    DrawRectangle(drawingWand, x, y, x + width, y + height);

    // Apply the drawing to the image
    MagickDrawImage(wand, drawingWand);

    // Cleanup
    DestroyDrawingWand(drawingWand);
    DestroyPixelWand(pixelWand);
}

void annotateScreenshot(const char *inputImage, const char *outputImage, int boxData[][4], int boxCount) {
    MagickWand *wand = NewMagickWand(); //This is used as a holder for the image

    // Load the image
    MagickReadImage(wand, inputImage);

    // Draw boxes based on the parsed data fromXML
    for (int i = 0; i < boxCount; i++) {
        drawYellowBox(wand, boxData[i][0], boxData[i][1], boxData[i][2], boxData[i][3]);
    }

    // Write the image out to a new file
    MagickWriteImage(wand, outputImage);

    // Cleanup!
    DestroyMagickWand(wand);
}



    