// this new solution focuses on utilizing good software engineering practices. Here, the factory design pattern is used to create
// new objects without knowing the details of each object. Since C is not an object-oriented language, function pointers are used to
// achieve the same results (i read about this method in a few articles).


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define HASH_MAP_SIZE 100
int count = 0;

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

Node* parentNodeArray[100]; // Array to store parent nodes

Node* makeChildNodes (int num);
int nodeExists(void* node);
int fibonacci(int n);
Node* sideOperation (void* num1, void* num2, Node* parentNode);
int calculate(Node* node);
Node* (*makeFunc(TypeTag type))(void*, void*);
Node* add(void* num1, void* num2);
Node* subtract(void* num1, void* num2);
Node* multiply(void* num1, void* num2);
Node* fib(void* num1, void* num2);


int main() {
    Node *add = makeFunc(ADD)(10,6);
    Node *mul = makeFunc(MUL)(5,4);
    Node *sub = makeFunc(SUB)(mul, add);
    Node *sub2 = makeFunc(SUB)(10, 5);
    Node *fib = makeFunc(FIB)(sub, NULL);

    printf("%d\n", calculate(add));
    printf("%d\n", calculate(mul));
    printf("%d\n", calculate(sub));
    printf("%d\n", calculate(fib));


    return 0;
}


int nodeExists(void* node){

    int flag = 0;
    int i = 0;
    while(parentNodeArray[i] != 0) {
        if(((Node*)(node)) == parentNodeArray[i]) {
            flag = 1;
            break;
        }
        i++;
    }
    return flag;

}

//fibonacci function using dynamic programming
//Time complexity: O(n) for given n
//Auxiliary space: O(n)
int fibonacci(int n) {
    int fib[n+1];
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i <= n; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }
    return fib[n];
}

Node* sideOperation (void* num1, void* num2, Node* parentNode){

//    equate the left and right nodes of the parent created with these input nodes, if they already exist
    if (nodeExists(num1)){
        parentNode->left = num1;
    }
    else {
        parentNode->left = makeChildNodes((int) num1);
    }

    if (nodeExists(num2)){
        parentNode->right = num2;
    }
    else {
        parentNode->right = makeChildNodes((int) num2);
    }

    return parentNode;
}

// responsible for creating the left and right children for each parent node
Node* makeChildNodes (int num){

    Node* node = (Node*) malloc(sizeof (Node));

    node->type = NUM;

    node->left = NULL;
    node->right = NULL;

    node->value = num;

    return node;
}

Node* add(void* num1, void* num2){
    Node* node = (Node*)malloc(sizeof(Node));

    node->type = ADD;
    node->index = count;

    count++;

    //adding each parent node with its index at this array for future reference
    parentNodeArray[node->index] = node;

    node = sideOperation(num1, num2, node);

//    node->left = makeChildNodes((int) num1);
//    node->right = makeChildNodes((int) num2);
    return node;

}

Node* multiply(void* num1, void* num2){
    Node* node = (Node*)malloc(sizeof(Node));
    node->type = MUL;

    node->index = count;

    count++;

    //adding each parent node with its index at this array for future reference
    parentNodeArray[node->index] = node;

    node = sideOperation(num1, num2, node);

//    node->left = makeChildNodes((int) num1);
//    node->right = makeChildNodes((int) num2);
    return node;
}

Node* subtract(void* num1, void* num2){
    Node* node = (Node*)malloc(sizeof(Node));
    node->type = SUB;

    node->index = count;

    count++;

    //adding each parent node with its index at this array for future reference
    parentNodeArray[node->index] = node;

    node = sideOperation(num1, num2, node);

//    node->left = makeChildNodes((int) num1);
//    node->right = makeChildNodes((int) num2);

    return node;
}

Node* fib(void* num1, void* num2){
    Node* node = (Node*)malloc(sizeof(Node));
    node->type = FIB;

    node->index = count;

    count++;

    //adding each parent node with its index at this array for future reference
    parentNodeArray[node->index] = node;

    node = sideOperation(num1, num2, node);

//    node->left = makeChildNodes((int) num1);
//    node->right = makeChildNodes((int) num2);
    return node;
}

// factory function: allows the user to create objects without having to specify the details of the objects to create
Node* (*makeFunc(TypeTag type))(void*, void*)
{
    switch(type)
    {
        case ADD : return &add; break;
        case MUL : return &multiply; break;
        case SUB : return &subtract; break;
        case FIB : return &fib; break;
    }
}

int calculate(Node* node) {
    int result = 0;

    if (node->type == ADD) {
        result = calculate(node->left) + calculate(node->right);
    }
    else if (node->type == MUL) {
        result =  calculate(node->left) * calculate(node->right);
    }
    else if (node->type == SUB) {
        result =  calculate(node->left) - calculate(node->right);
    }
    else if (node->type == FIB) {
        result =  fibonacci(calculate(node->left));
    }
    else if (node->type == NUM) {
        result = node->value;
    }
    else {
        printf("Invalid node type\n");
    }
    return result;
}

