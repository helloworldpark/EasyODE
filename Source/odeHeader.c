//
//  odeHeader.c
//  EasyODE
//
//  Created by Helloworld Park on 2016. 12. 15..
//  Copyright © 2016년 Helloworld Park. All rights reserved.
//

#include "odeHeader.h"
#include <stdlib.h>

timeHeader timeHeaderMake(double tFrom, double tTo, unsigned int interval) {
    timeHeader header;
    header.interval = interval;
    header.tFrom = tFrom;
    header.tTo = tTo;
    return header;
}

inputHeader inputHeaderMake(timeHeader time, vec initialValues) {
    inputHeader header;
    header.time = time;
    header.initialValues = initialValues;
    return header;
}

outputHeader outputHeaderAlloc(const inputHeader input) {
    outputHeader header;
    header.length = input.time.interval;
    header.results = (vec*)malloc(sizeof(vec) * header.length);
    for (int i = 0; i < header.length; i++) {
        header.results[i] = vecAlloc(input.initialValues.length);
    }
    return header;
}

void freeInputHeader(inputHeader* header) {
    freeVec(&header->initialValues);
}

void freeOutputHeader(outputHeader* header) {
    for (int i = 0; i < header->length; i++) {
        freeVec(header->results+i);
    }
    free(header->results);
}
