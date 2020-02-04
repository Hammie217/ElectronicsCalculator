#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char equationIn[100]="(39+3)/(3*3)\0";
char equationOut[100]="";
char equationStack[100];
int outPointer=-1;
int stackPointer=-1;
char bodmasStack[100]={"-+*/^\0"};

void commaSeparate(){
    equationOut[++outPointer]=',';
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
        commaSeparate();
        equationOut[++outPointer]=equationStack[stackPointer--];
    }
    else{
        printf("Error popping from empty stack");
    }
}


void copyRemainingStackOntoOutput(){
    for(;stackPointer>=0;){
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

void calculateEquation(){
//for each char in equation
    for (int i = 0; equationIn[i]!='\0'; i++)
    {
        //if is number
        if((equationIn[i]>48)&&(equationIn[i]<=57)){
            //push number to out
            equationOut[++outPointer]=equationIn[i];
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

int main(){

    calculateEquation();
    

    equationOut[++outPointer]='\0';
    printf("Equation out: %s EP: %d\n",equationOut,outPointer);
    equationStack[++stackPointer]='\0';
    printf("Stack: %s, SP: %d\n",equationStack, stackPointer);
    return 0;
}