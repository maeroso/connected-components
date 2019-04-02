//
//  ppm.c
//  Alg2-PPM
//
//  Created by Matheus Aeroso on 27/10/15.
//  Copyright © 2015 Matheus Aeroso. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm.h"
#include "image.h"

Image *openImageFile(const char *fileName) {
    Image *image = malloc(sizeof(Image));

    FILE *filePointer = fopen(fileName, "r");

    if (!filePointer) {
        printf("Erro na leitura do arquivo!");
        exit(EXIT_FAILURE);
    }

    char fileFormat[3];
    fscanf(filePointer, "%s", fileFormat);

    if (strcmp(fileFormat, "P3")) {
        printf("O arquivo nao esta no formato PPM ASCII!");
        exit(EXIT_FAILURE);
    }

    fscanf(filePointer, "%d %d", &(image->size.width), &(image->size.height));
    fscanf(filePointer, "%d", &(image->maxColorRGB));

    int i, j;
    PixelRGB **pixelMatrix = createPixelMatrix(&image->size);

    for (i = 0; i < image->size.height; i++) {
        for (j = 0; j < image->size.width; j++) {
            fscanf(filePointer, "%d %d %d ", &(pixelMatrix[i][j].color.r), &(pixelMatrix[i][j].color.g), &(pixelMatrix[i][j].color.b));
        }
    }

    image->pixelMatrix = pixelMatrix;

    fclose(filePointer);
    return image;
}

void saveImageFile(Image *image, const char *fileName) {
    FILE *filePointer = fopen(fileName, "w");

    if (!filePointer) {
        printf("Erro ao salvar o arquivo!");
        exit(EXIT_FAILURE);
    }

    fprintf(filePointer, "P3\n%d %d\n%d\n", image->size.width, image->size.height, image->maxColorRGB);
    int i, j;
    for (i = 0; i < image->size.height; i++) {
        for (j = 0; j < image->size.width; j++) {
            fprintf(filePointer, "%d %d %d\t", image->pixelMatrix[i][j].color.r, image->pixelMatrix[i][j].color.g,
                    image->pixelMatrix[i][j].color.b);
        }
        fprintf(filePointer, "\n");
    }

    fclose(filePointer);
}