//Recitation Program Assignment 1 - Mirror
//Alexander Gershfeld
//Arup Guha
//COP3502
//9-12-2023

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct testCase { //holds the information of individual test cases
    char** testRow;
    int rows;
    int maxChar;
} testCase;

testCase* insertInput(int R, int C); //Allocates the memory for strings as well as takes in input
void printMirror(char** charRows, int R, int C); //prints all of the test cases but mirrored
void freeRows(char** charRows, int R); //frees the memory allocated for the strings, then the row

int main() {
    int testTrial = 0; 
    int count = 0; //compared to the amount of trials
    int tmpRow, tmpCharMax; //holds the values based on the count
    
    scanf("%d ", &testTrial);

    testCase** tests = (testCase**)calloc(testTrial, sizeof(testCase*)); //struct allocated for test cases

    while(count != testTrial) {
        scanf("%d %d", &tmpRow, &tmpCharMax); 

        tests[count] = insertInput(tmpRow, tmpCharMax); //
        tests[count]->rows = tmpRow;                    //assigning the values to the struct
        tests[count]->maxChar = tmpCharMax;             //

        count++;
    }
    for(int i = 0; i < count; i++) {
        printf("Test %d\n", (i + 1));
        printMirror(tests[i]->testRow, tests[i]->rows, tests[i]->maxChar);
        freeRows(tests[i]->testRow, tests[i]->rows);
        free(tests[i]);
    }

    free(tests);
    return 0;
}

testCase* insertInput(int R, int C) {
    testCase* tmp = (testCase*)malloc(sizeof(testCase)); //allocates the individual test case
    tmp->testRow = (char**)calloc(R, sizeof(char*)); //allocates the amount of rows to hold strings
    for(int i = 0; i < R; i++) {
        tmp->testRow[i] = (char*)calloc((C + 1), sizeof(char)); //allocates memory for the actual strings themselves
        scanf("%s", tmp->testRow[i]);
    }

    return tmp;
}
void printMirror(char** charRows, int R, int C) {
    for(int i = R - 1; i >= 0; i--) {
        for(int j = C - 1; j >= 0; j--) {
            printf("%c", charRows[i][j]);
        }
        printf("\n");
    }
}
void freeRows(char** charRows, int R) {
    for(int i = 0; i < R; i++) {
        free(charRows[i]);
    }
    free(charRows);
}
