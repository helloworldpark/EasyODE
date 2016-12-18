//
//  odeHeader.h
//  EasyODE
//
//  Created by Helloworld Park on 2016. 12. 15..
//  Copyright © 2016년 Helloworld Park. All rights reserved.
//

#ifndef odeHeader_h
#define odeHeader_h

#include <stdio.h>
#include "customDatatype.h"

typedef struct _timeHeader {
    double tFrom;
    double tTo;
    unsigned int interval;
} timeHeader;

typedef struct _inputHeader {
    /* Time Range */
    timeHeader time;
    /* Initial Value */
    vec initialValues;
} inputHeader;

typedef struct _outputHeader {
    unsigned int length;
    vec* results;
} outputHeader;

timeHeader timeHeaderMake(double tFrom, double tTo, unsigned int interval);
inputHeader inputHeaderMake(timeHeader time, vec initialValues);
outputHeader outputHeaderAlloc(const inputHeader input);

void freeInputHeader(inputHeader* header);
void freeOutputHeader(outputHeader* header);

#endif /* odeHeader_h */
