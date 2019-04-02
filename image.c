//
// Created by Matheus Aeroso on 07/11/15.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "image.h"

PixelRGB **createPixelMatrix(Size *size) {
    PixelRGB **pixelMatrix = (PixelRGB **) malloc(sizeof(PixelRGB *) * size->height);

    int i;
    for (i = 0; i < size->height; i++)
        pixelMatrix[i] = (PixelRGB *) malloc(sizeof(PixelRGB) * size->width);

    return pixelMatrix;
}

int comparePixels(PixelRGB *a, PixelRGB *b) {
    //(|P1.r − P2.r|) + (|P1.g − P2.g|) + (|P1.b − P2.b|)
    if (!a || !b)
        return 0;

    int difference = abs(a->color.r - b->color.r) + abs(a->color.g - b->color.g) + abs(a->color.b - b->color.b);

    return difference < PIXEL_MAXIMUM_DIFFERENCE;
}

long minimum(long a, long b) {
    return a < b ? a : b;
}

void scanImageForComponents(Image *image, const int min, const int max) {
    long labelCount = 0;
    long i, j;
    long arraySize = image->size.height * image->size.width;
    long *equivalenceArray = (long int *) malloc(sizeof(long int) * arraySize);

    for (i = 0; i < arraySize; ++i)
        equivalenceArray[i] = i;

    for (i = 0; i < image->size.height; ++i) {
        for (j = 0; j < image->size.width; ++j) {
            PixelRGB *leftPixel = j - 1 >= 0 ? &(image->pixelMatrix[i][j - 1]) : NULL;
            PixelRGB *topPixel = i - 1 >= 0 ? &(image->pixelMatrix[i - 1][j]) : NULL;

            PixelRGB *currentPixel = &image->pixelMatrix[i][j];

            if (!(comparePixels(currentPixel, leftPixel) && comparePixels(currentPixel, topPixel))) {
                currentPixel->label = labelCount;
                labelCount++;
            } else if (comparePixels(currentPixel, leftPixel) && comparePixels(currentPixel, topPixel) &&
                       comparePixels(leftPixel, topPixel) && equivalenceArray[topPixel->label] != equivalenceArray[leftPixel->label]) {
                int k;
                for (k = 0; k <= labelCount; ++k) {
                    if (equivalenceArray[k] == equivalenceArray[leftPixel->label] || equivalenceArray[k] == equivalenceArray[topPixel->label])
                        equivalenceArray[k] = minimum(equivalenceArray[leftPixel->label], equivalenceArray[topPixel->label]);
                }
                currentPixel->label = minimum(equivalenceArray[leftPixel->label], equivalenceArray[topPixel->label]);
            } else if (comparePixels(currentPixel, leftPixel)) {
                currentPixel->label = leftPixel->label;
            } else if (comparePixels(currentPixel, topPixel)) {
                currentPixel->label = topPixel->label;
            }
        }
    }

    srand((unsigned int) time(NULL));
    Color *colors = (Color *) malloc(sizeof(Color) * labelCount);
    for (i = 0; i < labelCount; ++i) {
        colors[i].r = (unsigned int) rand() % 256;
        colors[i].g = (unsigned int) rand() % 256;
        colors[i].b = (unsigned int) rand() % 256;
    }

    for (i = 0; i < image->size.height; ++i) {
        for (j = 0; j < image->size.width; ++j) {
            PixelRGB *current = &image->pixelMatrix[i][j];
            current->label = equivalenceArray[current->label];
            current->color = colors[current->label];
        }
    }
}
