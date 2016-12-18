//
//  odeSolver.h
//  EasyODE
//
//  Created by Helloworld Park on 2016. 12. 15..
//  Copyright © 2016년 Helloworld Park. All rights reserved.
//

#ifndef odeSolver_h
#define odeSolver_h

#include <stdio.h>
#include "odeHeader.h"
#include "customDatatype.h"

void solveODE(const inputHeader input, outputHeader* output, void (*func)(double t, vec input, vec* output));

#endif /* odeSolver_h */
