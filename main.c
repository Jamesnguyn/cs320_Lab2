/*
 * JAMES NGUYEN
 * 820268781
 * CS320 Lab 2
 * 2pm - 3:15pm
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Create a program in the C programming language that accepts standard input and produces standard output x
// Implement a classic algorithm using a new programming language x
// Develop a simple stack implementation x
// Make use of functions to simplify code x
// Use function parameters effectively to eliminate the need for global variables (state) x

// The program shall request a line of input from the user in reverse polish notation. x
// Using the characters supplied at run-time, the program shall then calculate the mathematical result and display the value to the user. x
// The program shall then display a brief message indicating it has finished and terminate. x
// In the event of erroneous input, the program shall display an error message with a description of the problem and exit.

int evaluateReversePolish(char expression[8]);

int main() {
//    char exp[] = "231*+9-";
//    printf("Value of %s is %d.",exp, evaluatePostfix(exp));

    char expression[100];

    printf("Enter expression:\n");
    scanf("%s",expression);
    printf("Value of %s is: %d.", expression, evaluateReversePolish(expression));

    return 0;
}

struct Stack { //stack type
    int top; //stores eliminated of the top of the stack
    unsigned size; //capacity
    int* array; //stack of type int
};

struct Stack* createStack(unsigned size){ //create stack
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack)); //create stack, locate memory

    if(!stack){
        return NULL; // no located memory
    }

    stack->top = -1;//initialize -1 because stack is empty
    stack->size = size;
    stack->array = (int*) malloc(stack->size * sizeof(int));//locate memory into array of the size of capacity

    if (!stack->array){
        return NULL;//not allocated memory, return null
    }
    return stack;
}

int isEmpty(struct Stack* stack){//returns -1 if stack is empty
    return stack->top == -1;
}

char pop(struct Stack* stack){//pops and eliminates from stack
    if(!isEmpty(stack)){//checks stack if its not empty
        return stack->array[stack->top--];//removes from stack
        return '$';//if empty returns '$' which means element cannot be popped
    }
}

void push(struct Stack* stack, char operator){//pushes element onto stack
    stack->array[++stack->top] = operator;
}

int evaluateReversePolish(char* expression){
    struct Stack* stack = createStack(strlen(expression));//pass in capacity of the length of the expression

    if (!stack){//stack is empty
        return -1;
    }

    for (int i = 0; expression[i]; i++){//loops through the expression
        if(expression[i] == ' '){
            continue;
        }
        else if(isdigit(expression[i])){//returns true if a digit
            push(stack,expression[i]- '0');//push data onto stack, remove '0' so you dont have to convert it back into the correct value
        }

        else{//if loop finds operator, pop two elements from stack and apply operator
            int valueOne = pop(stack);
            int valueTwo = pop(stack);

            switch (expression[i]){//i is operator
                case '+': push(stack,valueTwo + valueOne);
                    break;
                case '-': push(stack,valueTwo - valueOne);
                    break;
                case '*': push(stack,valueTwo * valueOne);
                    break;
                case '/': push(stack,valueTwo / valueOne);
                    break;
            }
        }
    }
    return pop(stack);//one element left, return top element by popping
}

void expressionError(char error, char str[]){
    switch(error){
        case 'a':
            printf("Error = %s \n", str);
            printf("Input must be a number.");
            exit(0);
        case 'b':
            printf("Error = %s \n", str);
            printf("Invalid number.");
            exit(0);
        case 'c':
            printf("Error = %s \n", str);
            printf("Invalid operator.");
            exit(0);
        case 'd':
            printf("Error = %s \n", str);
            printf("Too few operators.");
            exit(0);
        case 'e':
            printf("Error = %s \n", str);
            printf("Too many operators.");
            exit(0);
    }
}