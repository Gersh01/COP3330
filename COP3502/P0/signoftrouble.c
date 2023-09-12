#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE 100002 //constant variable

char* allocateFirstInput();
char* allocateSecondInput();

int main() {
	int freq[25] ={0}; //frequency array
	char* firstInput = allocateFirstInput(); //the first word to be compared
	char* secondInput = allocateSecondInput(); //the second word to be compared
	int firstInputLen = strlen(firstInput);
	int secondInputLen = strlen(secondInput);
	int buy = 0;

	//counts the frequency of each letter in the first input
	for(int i = 0; i < firstInputLen + 1; i++) {
		//65 is the ascii for space, just to make sure that the for loop isnt counting the space
		if(('A' - firstInput[i]) == 65) {
			continue;
		}
		else {
			freq[firstInput[i] - 'A']++;
		}
	}

	// using the values stored, decides whether a letter should be bought or used for new word
	for(int i = 0; i < secondInputLen + 1; i++) {
		if(freq[secondInput[i] - 'A'] == 0) { 
			buy++; //tracks the amount of letters needed for new input
		}
		else if(('A' - secondInput[i]) == 65) {
			continue;
		}
		else {
			freq[secondInput[i] - 'A'] -= 1; // takes a word from the first input
		}
	}
	
	/*
	//print out the contents of the freq array
	for(int i = 0; i < 26; i++) {
		printf("the index freq[%d] is equal to %d\n", i, freq[i]);
	}
	*/

	//The moment of truth!
	printf("%d\n", buy);
	
	free(firstInput);
	free(secondInput);

	return 0;
}

char* allocateFirstInput() {
	char* temp; 
	temp = (char*)malloc(sizeof(char) * SIZE);

	fgets(temp, 100001, stdin);
	
	return temp;
}
char* allocateSecondInput() {
	char* temp;
	temp = (char*)malloc(sizeof(char) * SIZE);

	fgets(temp, 100001, stdin);

	return temp;
}
