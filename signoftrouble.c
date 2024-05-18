#include<stdio.h>
#include<string.h>

#define SIZE 30

int main() {
    int alphaArr[25] = {0};
    char firstInput[SIZE];
    char secondInput[SIZE];
    int output;

    fgets(firstInput, SIZE, stdin);
    fgets(secondInput, SIZE, stdin);

    int firstLen = sizeof(firstInput)/sizeof(firstInput[0]);
    int secondLen = sizeof(secondInput)/sizeof(secondInput[0]);

    for(int i = 0; i < firstLen; i++) {
        for(int j = 0; j < secondLen; j++) {
            if(firstInput[i] == secondInput[j]) {
                output++;
            }
            
        }
    }
    
    return 0;
}