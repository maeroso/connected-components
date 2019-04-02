//
//  main.c
//  Alg2-PPM
//
//  Created by Matheus Aeroso on 27/10/15.
//  Copyright © 2015 Matheus Aeroso. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "ppm.h"

int main(int argc, const char *argv[]) {
    // insert code here...
    printf("PPM: Componentes Conexos\n");

    if (argc == 1) {
        printf("Usage: %s input_file.ppm output_file.ppm MIN MAX\n", argv[0]);
        exit(EXIT_SUCCESS);
    }

    const int MIN = atoi(argv[3]);
    const int MAX = atoi(argv[4]);

    Image *imagePointer = openImageFile(argv[1]);
    scanImageForComponents(imagePointer, 0, 0);
    saveImageFile(imagePointer, argv[2]);

    return 0;
}
