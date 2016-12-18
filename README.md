# EasyODE
This project aims to solve ordinary differential equations(ODE) numerically using [4th-Order Runge-Kutta](https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods) **without having to write boilerplate codes**. You only have to write simple functions and give the proper initial values. The codes are written in C.

## Installation
1. Clone, or download the zip file of the project.
2. Compile with your C compiler.

## How to use
##### 1. Write your equation in a given form.
```C
// You should keep the prototype of the function as following
void predatorPrey(double t, vec input, vec* output) {
    output->arr[0] =  1.5 * input.arr[0] - 1.0 * input.arr[0] * input.arr[1];
    output->arr[1] = -3.0 * input.arr[1] + 1.0 * input.arr[0] * input.arr[1];
}
```
##### 2. Define the range of time you would like to solve.
```C
timeHeader time = timeHeaderMake(0.0, 20.0, 100000);
```
##### 3. Initialize the initial values for your equation
```C
vec initialValues = vecAlloc(2);
initialValues.arr[0] = 8.0;
initialValues.arr[1] = 20.0;
```
##### 4. Define ```inputHeader``` and ```outputHeader```
```C
inputHeader input = inputHeaderMake(time, initialValues);
outputHeader output = outputHeaderAlloc(input);
```
##### 5. Solve, and write on your file.
```C
solveODE(input, &output, predatorPrey);
fileReport(input, output, "predatorPrey");
```
##### 6. Don't forget to release your precious resources.
```C
freeInputHeader(&input);
freeOutputHeader(&output);
```
##### 7. You can visualize the results.
![Predator-Prey](https://github.com/helloworldpark/helloworldpark.github.com/blob/master/images/20161216_graph03.png)

## Explanation
This project aims to solve all kinds of ODEs, so it **could** be slower than other codes. In other words, it is not for any practical use, rather for hobby.
Every ODE can be expressed in a form of vector. It may or may not involve matrices, but at least it has the form *Y' = f(t, Y)*, where *Y* stands for a vector of *n* components. From this point of view, the ODE solver of this project uses vectors, which are in fact an array of ```double```. It is defined as the structure ```vec```.
```C
typedef struct _vec {
    unsigned int length;
    unsigned int isAlloc;
    double* arr;
} vec;
```
ODE needs *time*, which is the domain of the equation. It also needs *initial values* to be solved numerically. And there is the *results*. The headers for these information are defined as following:
```C
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
```
It is strongly recommended to use factory functions to use the structures. The functions are as following:
```C
// customDatatype.h
vec vecMake(unsigned int length, double* arr);
vec vecAlloc(unsigned int length);

// odeHeader.h
timeHeader timeHeaderMake(double tFrom, double tTo, unsigned int interval);
inputHeader inputHeaderMake(timeHeader time, vec initialValues);
outputHeader outputHeaderAlloc(const inputHeader input);
```
You may see that there some rules on the names of the functions: functions that end with *~Make*, need not be freed after its use. It is your responsibility to free the dynamically allocated arrays or not. With *~Alloc*, however, the variable **must be freed** after its use, since it uses ```malloc``` internally. You can use the following functions for releasing the structures.
```C
// customDatatype.h
void freeVec(vec* arr);

// odeHeader.h
void freeInputHeader(inputHeader* header);
void freeOutputHeader(outputHeader* header);
```

Since C does not support vector operations, it is implemented in a weird way. As an example, the addition of vectors are as following:
```C
void vadd(vec a, vec b, vec* output) {
    assert(a.length == b.length);
    output->length = a.length;
    for (int i = 0; i < a.length; i++) {
        output->arr[i] = a.arr[i] + b.arr[i];
    }
}
```
You may see that ```vadd(vec a, vec b, vec* output)``` requires a pointer for its output. Other operations, such as subtraction, multiplication, division and scalar multiplication are similar to the addition.

Make sure to write your equation in the given form: ```void f(double t, vec input, vec* output)```. It is because, by writing your custom equation in the given form, the function pointer can be passed to the ```solveODE``` function.

The main part, ```solveODE(vec input, vec* output, void (*f)(double t, vec i, vec* o))``` uses explicit [4th-Order Runge-Kutta](https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods) method. With the input, output, and the function pointer, the result will be saved in the ```output``` variable. Using ```fileReport(vec input, vec output, char* fileName)``` function, you can write on your file. The file is saved on the same path with the execution file(mostly, ```a.out``` if using gcc).
