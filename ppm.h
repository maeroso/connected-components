//
//  ppm.h
//  Alg2-PPM
//
//  Created by Matheus Aeroso on 27/10/15.
//  Copyright © 2015 Matheus Aeroso. All rights reserved.
//

#ifndef ALG2_PPM_PPM_H
#define ALG2_PPM_PPM_H

#include <stdio.h>
#include "image.h"

Image *openImageFile(const char *fileName);

void saveImageFile(Image *image, const char *fileName);

#endif //ALG2_PPM_PPM_H
