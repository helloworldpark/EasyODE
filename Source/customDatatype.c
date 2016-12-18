//
//  customDatatype.c
//  EasyODE
//
//  Created by Helloworld Park on 2016. 12. 15..
//  Copyright © 2016년 Helloworld Park. All rights reserved.
//

#include "customDatatype.h"
#include <stdlib.h>
#include <assert.h>

vec vecMake(unsigned int length, double* arr) {
    vec vecay;
    vecay.length = length;
    vecay.isAlloc = 0;
    vecay.arr = arr;
    return vecay;
}

vec vecAlloc(unsigned int length) {
    vec vecay;
    vecay.length = length;
    vecay.isAlloc = 1;
    vecay.arr = (double*)malloc(sizeof(double) * length);
    return vecay;
}

void freeVec(vec* arr) {
    if(arr->isAlloc == 1) {
        free(arr->arr);
    }
}

void vadd(vec a, vec b, vec* output) {
    assert(a.length == b.length);
    output->length = a.length;
    for (int i = 0; i < a.length; i++) {
        output->arr[i] = a.arr[i] + b.arr[i];
    }
}

void vsubtract(vec a, vec b, vec* output) {
    assert(a.length == b.length);
    output->length = a.length;
    for (int i = 0; i < a.length; i++) {
        output->arr[i] = a.arr[i] - b.arr[i];
    }
}

void vmultiply(vec a, vec b, vec* output) {
    assert(a.length == b.length);
    output->length = a.length;
    for (int i = 0; i < a.length; i++) {
        output->arr[i] = a.arr[i] * b.arr[i];
    }
}

void vdivide(vec a, vec b, vec* output) {
    assert(a.length == b.length);
    output->length = a.length;
    for (int i = 0; i < a.length; i++) {
        output->arr[i] = a.arr[i] / b.arr[i];
    }
}

void vaddScalar(vec a, double c, vec* output) {
    output->length = a.length;
    for (int i = 0; i < a.length; i++) {
        output->arr[i] = a.arr[i] + c;
    }
}

void vsubScalar(vec a, double c, vec* output) {
    output->length = a.length;
    for (int i = 0; i < a.length; i++) {
        output->arr[i] = a.arr[i] - c;
    }
}

void vmulScalar(vec a, double c, vec* output) {
    output->length = a.length;
    for (int i = 0; i < a.length; i++) {
        output->arr[i] = a.arr[i] * c;
    }
}

void vdivScalar(vec a, double c, vec* output) {
    output->length = a.length;
    for (int i = 0; i < a.length; i++) {
        output->arr[i] = a.arr[i] / c;
    }
}
