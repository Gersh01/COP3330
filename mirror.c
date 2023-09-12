#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct mirror {
    char** testArr;
    int rows;
    int maxChar;
} mirror;

mirror* insertInput(int R, int C);
void printMirror(char** charArr, int R, int C);
void freeArr(char** charArr, int R);

int main() {
    int testCases = 0;
    int count = 0;
    int tmpRow;
    int tmpCharMax;
    
    scanf("%d ", &testCases);

    mirror** test = (mirror**)calloc(testCases, sizeof(mirror*)); //struct allocated for test cases

    while(count != testCases) {
        char input[10];
        fgets(input, 10, stdin);
        input[strcspn(input, "\n")] = 0;
        
        tmpRow = atoi(strtok(input, " "));
        tmpCharMax = atoi(strtok(NULL, " "));

        test[count] = insertInput(tmpRow, tmpCharMax);
        test[count]->rows = tmpRow;
        test[count]->maxChar = tmpCharMax;

        count++;
    }
    for(int i = 0; i < count; i++) {
        printf("Test %d\n", (i + 1));
        printMirror(test[i]->testArr, test[i]->rows, test[i]->maxChar);
    }
     

    return 0;
}
mirror* insertInput(int R, int C) {
    mirror* tmp = (mirror*)malloc(sizeof(mirror));
    tmp->testArr = (char**)calloc(R, sizeof(char*));
    for(int i = 0; i < R; i++) {
        tmp->testArr[i] = (char*)calloc((C + 1), sizeof(char));
        scanf("%s", tmp->testArr[i]);
    }

    return tmp;
}


void printMirror(char** charArr, int R, int C) {
    for(int i = R - 1; i >= 0; i--) {
        for(int j = C - 1; j >= 0; j--) {
            printf("%c", charArr[i][j]);
        }
        printf("\n");
    }

}
void freeArr(char** charArr, int R) {
    
}