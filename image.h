//
// Created by Matheus Aeroso on 07/11/15.
//

#ifndef ALG2_PPM_IMAGE_H
#define ALG2_PPM_IMAGE_H

#define PIXEL_MAXIMUM_DIFFERENCE 30

typedef struct {
    int width, height;
} Size;

typedef struct {
    int r, g, b;
} Color;

typedef struct {
    Color color;
    long label;
} PixelRGB;

typedef struct {
    PixelRGB **pixelMatrix;
    Size size;
    int maxColorRGB;
} Image;

PixelRGB **createPixelMatrix(Size *size);

int comparePixels(PixelRGB *a, PixelRGB *b);

void scanImageForComponents(Image *image, const int min, const int max);

#endif //ALG2_PPM_IMAGE_H
