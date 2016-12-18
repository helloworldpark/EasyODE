//
//  main.c
//  EasyODE
//
//  Created by Helloworld Park on 2016. 12. 15..
//  Copyright © 2016년 Helloworld Park. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "odeSolver.h"

// Example for Predator-Prey model
void example01();
void predatorPrey(double t, vec input, vec* output);
// Example for Simple Pendulum
void example02();
void simplePendulum(double t, vec input, vec* output);
// Example for Lorenz Attractor
void example03();
void lorenzAttractor(double t, vec input, vec* output);

void fileReport(inputHeader input, outputHeader output, char* fileName);

int main(int argc, const char * argv[]) {
    example01();
    example02();
    example03();
    
    return 0;
}

void example01() {
    timeHeader time = timeHeaderMake(0.0, 20.0, 100000);
    vec initialValues = vecAlloc(2);
    initialValues.arr[0] = 8.0;
    initialValues.arr[1] = 20.0;
    inputHeader input = inputHeaderMake(time, initialValues);
    outputHeader output = outputHeaderAlloc(input);
    
    solveODE(input, &output, predatorPrey);
    
    fileReport(input, output, "predatorPrey.txt");
    
    freeInputHeader(&input);
    freeOutputHeader(&output);
}
void predatorPrey(double t, vec input, vec* output) {
    static double a = 1.5;
    static double b = 1.0;
    static double c = 3.0;
    static double d = 1.0;
    output->arr[0] =  a * input.arr[0] - b * input.arr[0] * input.arr[1];
    output->arr[1] = -c * input.arr[1] + d * input.arr[0] * input.arr[1];
}

void example02() {
    const double PI = atan(1.0) * 4.0;
    
    timeHeader time = timeHeaderMake(0.0, 20.0, 100000);
    vec initialValues = vecAlloc(2);
    initialValues.arr[0] = PI * 0.499;
    initialValues.arr[1] = PI * 1.400;
    inputHeader input = inputHeaderMake(time, initialValues);
    outputHeader output = outputHeaderAlloc(input);
    
    solveODE(input, &output, simplePendulum);
    
    fileReport(input, output, "simplePendulum.txt");
    
    freeInputHeader(&input);
    freeOutputHeader(&output);
}
void simplePendulum(double t, vec input, vec* output) {
    static double l = 1.0;
    static double g = 9.8;
    output->arr[0] = input.arr[1];
    output->arr[1] = -(g/l) * sin(input.arr[0]);
}

void example03() {
    timeHeader time = timeHeaderMake(0.0, 100.0, 100000);
    vec initialValues = vecAlloc(3);
    initialValues.arr[0] = 1.0;
    initialValues.arr[1] = 1.0;
    initialValues.arr[2] = 1.0;
    inputHeader input = inputHeaderMake(time, initialValues);
    outputHeader output = outputHeaderAlloc(input);
    
    solveODE(input, &output, lorenzAttractor);
    
    fileReport(input, output, "lorenzAttractor.txt");
    
    freeInputHeader(&input);
    freeOutputHeader(&output);
}
void lorenzAttractor(double t, vec input, vec* output) {
    static double r = 28.0;
    static double s = 10.0;
    static double b = 8.0/3.0;
    output->arr[0] = s * (input.arr[1] - input.arr[0]);
    output->arr[1] = input.arr[0] * (r - input.arr[2]) - input.arr[1];
    output->arr[2] = input.arr[0] * input.arr[1] - b * input.arr[2];
}

void fileReport(inputHeader input, outputHeader output, char* fileName) {
    FILE* f;
    f = fopen(fileName, "w");
    if(f == NULL) {
        return;
    }
    fprintf(f, "t\t");
    for(int i = 0; i < input.initialValues.length-1; i++) {
        fprintf(f, "y[%d]\t", i);
    }
    fprintf(f, "y[%d]\n", input.initialValues.length-1);
    
    for(int i = 0; i < output.length; i++) {
        double t = input.time.tFrom + ((input.time.tTo - input.time.tFrom)/input.time.interval) * i;
        fprintf(f, "%1.6f\t", t);
        for(int j = 0; j < input.initialValues.length-1; j++) {
            fprintf(f, "%1.10f\t", output.results[i].arr[j]);
        }
        fprintf(f, "%1.10f\n", output.results[i].arr[input.initialValues.length-1]);
    }
    fclose(f);
}
