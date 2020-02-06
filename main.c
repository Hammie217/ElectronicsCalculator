/*
Adding a new function:
Add value to the bodmas stack Line (remeber these don't have to be visible characters and can be special character codes):   char *bodmasStack={};
Add algorithm to corresponding switch case in the function:   void operatorOnRPNStack(char op){
*/
#define maxEquationLength 100
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


char equationIn[maxEquationLength]="32*8/4-6*10@4\0";
char equationRPN[maxEquationLength]="";
int outPointer=-1;
char equationStack[maxEquationLength];
int stackPointer=-1;
char *bodmasStack={"-+*/sc^@\0"};
long double RPNStack[maxEquationLength]; 
int RPNStackPointer=-1;

void commaSeparate(){
    equationRPN[++outPointer]=',';
}

int getPrecidenceOfTop(){
    for (int i= 0; bodmasStack[i]!='\0'; i++)
    {
        if(equationStack[stackPointer]==bodmasStack[i])
            return i;
    }
    return -1;
}

int getPrecidenceOf(char c){
    for (int i= 0; bodmasStack[i]!='\0'; i++)
    {
        if(c==bodmasStack[i])
            return i;
    }
    return -1;
}

void popFromStackToOut(){
    if(stackPointer>-1){
        equationRPN[++outPointer]=equationStack[stackPointer--];
    }
    else{
        printf("Error popping from empty stack");
    }
}


void copyRemainingStackOntoOutput(){
    for(;stackPointer>=0;){
        commaSeparate();
        popFromStackToOut();

    }
}

void copyRemainingEnclosedStackOntoOutput(){
    for(;equationStack[stackPointer]!='(';){

        popFromStackToOut();

    }
    stackPointer--;
}



void pushToStack(char ch){
    equationStack[++stackPointer] = ch;
}

void onLeftBracket(){
    pushToStack('(');
}

void onRightBracket(){
    copyRemainingEnclosedStackOntoOutput();
}


void calculateRPN(){
//for each char in equation
    for (int i = 0; equationIn[i]!='\0'; i++)
    {
        //printf("RPNStack: %s EP: %d\n",equationRPN,outPointer);

        //if is number
        if(((equationIn[i]>=48)&&(equationIn[i]<=57))||(equationIn[i]==46)){
            
            //push number to out
            equationRPN[++outPointer]=equationIn[i];
        }
        for (int ii= 0; bodmasStack[ii]!='\0'; ii++)
            {   //if is an operator
                if(equationIn[i]==bodmasStack[ii]){
                    commaSeparate();
                    for(int iii=stackPointer;iii>=0;iii--){
                        //if precidence of stack is higher
                        if(getPrecidenceOf(equationIn[i])<getPrecidenceOfTop()){
                            //pop off stac
                            popFromStackToOut();
                            commaSeparate();

                        }
                        //otherwise end loop
                        else{
                            iii=0;
                        }

                    }
                    //put op onto stack
                    pushToStack(equationIn[i]);

                }
            }
        if(equationIn[i]=='('){
            onLeftBracket();
        }
        if(equationIn[i]==')'){
            onRightBracket();
        }
    };
    copyRemainingStackOntoOutput();
}

void pushToRPNStack(long double value){
    RPNStack[++RPNStackPointer] = value;
}

void operatorOnRPNStack(char op){
    switch(op){
        case '@':
        RPNStack[RPNStackPointer-1]= 1/((1/RPNStack[RPNStackPointer-1])+(1/RPNStack[RPNStackPointer]));//in parallel
        RPNStackPointer--;
        break;
        case '^':
        break;
        case 's':
        //RPNStack[RPNStackPointer]= Math.sine(RPNStack[RPNStackPointer]);//sine
        break;
        case 'c':
        //RPNStack[RPNStackPointer]= Math.cos(RPNStack[RPNStackPointer]);//sine
        break;
        case '/':
            RPNStack[RPNStackPointer-1]= RPNStack[RPNStackPointer-1]/RPNStack[RPNStackPointer];
            RPNStackPointer--;
        break;
        case '*':
            RPNStack[RPNStackPointer-1]=RPNStack[RPNStackPointer] * RPNStack[RPNStackPointer-1];
            RPNStackPointer--;
            break;
        case '+':
            RPNStack[RPNStackPointer-1]=RPNStack[RPNStackPointer] + RPNStack[RPNStackPointer-1];
            RPNStackPointer--;
            break;
        case '-':
            RPNStack[RPNStackPointer-1]= RPNStack[RPNStackPointer-1] - RPNStack[RPNStackPointer];
            RPNStackPointer--;        
            break;
        default:
        printf("Error operator not found");
        break;
    }
}

long double computeRPN(){
    long double temp;
    char * token = strtok(equationRPN, ",");
    char * ptr;
    while(token!=NULL){
        //if number
        if(((token[0]>='0')&&(token[0]<='9'))||(token[0]=='.')){
            temp = strtold(token, &ptr);
            RPNStack[++RPNStackPointer]=temp;
            //printf( " %.10Le\n", temp); //printing each token
        }
        else{
            operatorOnRPNStack(*token);
        }
        token = strtok(NULL, ",");
    }
    //printf("RPNStack: %Le EP: %d\n",*RPNStack,RPNStackPointer);
    return *RPNStack;
}


int main(){
    printf("Question: %s\n",equationIn);
    calculateRPN();
    //printf("RPNStack: %s EP: %d\n",equationRPN,outPointer);


    long double answer = computeRPN();
    printf("Answer: %Le\n",*RPNStack);

    return 0;
}