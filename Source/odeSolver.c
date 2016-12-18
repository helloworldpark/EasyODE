//
//  odeSolver.c
//  EasyODE
//
//  Created by Helloworld Park on 2016. 12. 15..
//  Copyright © 2016년 Helloworld Park. All rights reserved.
//

#include "odeSolver.h"
#include <math.h>

void solveODE(const inputHeader input, outputHeader* output, void (*func)(double t, vec input, vec* output)) {
    // Initialize
    const unsigned int VECLEN = input.initialValues.length;
    
    const double dt = (input.time.tTo - input.time.tFrom) / input.time.interval;

    double tOld;
    
    double oldval[VECLEN];
    double newval[VECLEN];
    
    vec k1 = vecAlloc(VECLEN);
    vec k2 = vecAlloc(VECLEN);
    vec k3 = vecAlloc(VECLEN);
    vec k4 = vecAlloc(VECLEN);
    
    vec fInput = vecMake(VECLEN, oldval);
    vec fTemp = vecAlloc(VECLEN);

    // Save initial data to output
    for(int i = 0; i < VECLEN; i++) {
        output->results[0].arr[i] = input.initialValues.arr[i];
    }
    // New value is set to the initial data at first
    for(int i = 0; i < VECLEN; i++) {
        newval[i] = output->results[0].arr[i];
    }

    // Iterate and calculate by Runge-Kutta 4th order method
    for (int i = 1; i < input.time.interval; i++) {
        // Move new values to old values
        for(int j = 0; j < VECLEN; j++) {
            oldval[j] = newval[j];
        }
        
        tOld = input.time.tFrom + (i-1) * dt;
        
        func(tOld, fInput, &k1);
        vmulScalar(k1, 0.5 * dt, &fTemp);
        vadd(fInput, fTemp, &fTemp);
        func(tOld + 0.5 * dt, fTemp, &k2);
        vmulScalar(k2, 0.5 * dt, &fTemp);
        vadd(fInput, fTemp, &fTemp);
        func(tOld + 0.5 * dt, fTemp, &k3);
        vmulScalar(k3, 1.0 * dt, &fTemp);
        vadd(fInput, fTemp, &fTemp);
        func(tOld + 1.0 * dt, fTemp, &k4);
        
        // Calculate new values
        for(int j = 0; j < VECLEN; j++) {
            newval[j] = oldval[j] + (dt/6.0) * (1.0 * k1.arr[j] + 2.0 * k2.arr[j] + 2.0 * k3.arr[j] + 1.0 * k4.arr[j]);
        }
        
        // Save new values to output
        for(int j = 0; j < VECLEN; j++) {
            output->results[i].arr[j] = newval[j];
        }
    }
    
    // Clean up, and release all the memories used
    freeVec(&k1);
    freeVec(&k2);
    freeVec(&k3);
    freeVec(&k4);
    freeVec(&fInput);
    freeVec(&fTemp);
}
