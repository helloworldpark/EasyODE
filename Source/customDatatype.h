//
//  customDatatype.h
//  EasyODE
//
//  Created by Helloworld Park on 2016. 12. 15..
//  Copyright © 2016년 Helloworld Park. All rights reserved.
//

#ifndef customDatatype_h
#define customDatatype_h

#include <stdio.h>

typedef struct _vec {
    unsigned int length;
    unsigned int isAlloc;
    double* arr;
} vec;

vec vecMake(unsigned int length, double* arr);
vec vecAlloc(unsigned int length);
void freeVec(vec* arr);

void      vadd(vec a, vec b, vec* output);
void vsubtract(vec a, vec b, vec* output);
void vmultiply(vec a, vec b, vec* output);
void   vdivide(vec a, vec b, vec* output);

void vaddScalar(vec a, double c, vec* output);
void vsubScalar(vec a, double c, vec* output);
void vmulScalar(vec a, double c, vec* output);
void vdivScalar(vec a, double c, vec* output);

#endif /* customDatatype_h */
