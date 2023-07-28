#include <stdio.h>
#include <stdlib.h>

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
TypeTag globalType; // Global variable to store the type
int count = 0;



//function prototypes
Node* (*makeFunc(TypeTag type)) (void*, void*);
Node* makeParentNode (void*, void*);
Node* makeChildNodes (int num);
int nodeExists(void* node);
int fibonacci(int n);
int calculate(Node* node);


int main() {
    Node *add = makeFunc(ADD)(10,6);
    Node *mul = makeFunc(MUL)(5,4);
    Node *sub = makeFunc(SUB)(mul, add);
    Node *fib = makeFunc(FIB)(sub, NULL);

    printf("add : %d\n", calculate(add));
    printf("multiply : %d\n", calculate(mul));
    printf("subtraction : %d\n", calculate(sub));
    printf("fib : %d\n", calculate(fib));


    return 0;
}

// Since we store each parent node in the parentNodeArray, this function searches for a node in this array
// if it exists, then the input node have already been created, hence there's no need to create new nodes
// Therefore, we equate the left and right nodes of the parent created with this input nodes
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

// a function responsible for making parent nodes (such as add, mul and sub). It also calls the make child nodes function
Node* makeParentNode (void* num1, void* num2){

    Node* node = (Node*)malloc(sizeof(Node));

    node->index = count;
    count++;

    //adding each parent node with its index at this array for future reference
    parentNodeArray[node->index] = node;

    node->type = globalType;

//    equate the left and right nodes of the parent created with these input nodes, if they already exist
    if (nodeExists(num1)){
        node->left = num1;
    }
    else {
        node->left = makeChildNodes((int) num1);
    }

    if (nodeExists(num2)){
        node->right = num2;
    }
    else {
        node->right = makeChildNodes((int) num2);
    }

    return node;
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

// an intermediate pointer to function which sets the type of each parent node (using the global type variable)
// and points to the make parent node function
Node* (*makeFunc(TypeTag type)) (void*, void*){
    globalType = type;
    return &makeParentNode;
}

//a fibonacci function using dynamic programming
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

