# Bitnine Assessment

## Development environment & Operating system

````
Compiler version: gcc.exe (x86_64-win32-sjlj-rev0, Built by MinGW-W64 project) 8.1.0
Operating system: Windows 10 pro
IDE: Visual studio code
````

## Run The code
- open terminal in the file location (question1)
- compile the code using this command: gcc q1.c (depending on which problem you want to compile)
- Run the executable file (without extension): q1
-  Or, running this code on any IDE where gcc is installed 

### Contents

#### 1) Readme file

#### Note: The structure for both solutions is the same (enum, struct, and calculate)
````
typedef enum {
    ADD, SUB, MUL, FIB, NUM
} TypeTag;


typedef struct Node {
    TypeTag type;

    int value;
    int index;

    struct Node *left;
    struct Node *right;
} Node;
````

#### 2) [Problem 1 folder](https://github.com/Mariam22-hub/bitnine/tree/main/question%201)
*This folder contains 2 solutions for question 1*


#### 3) [Problem 2 folder](https://github.com/Mariam22-hub/bitnine/tree/main/question%202)


