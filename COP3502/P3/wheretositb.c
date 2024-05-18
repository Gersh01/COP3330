//Program Assignment 3b - Where to Sit
//Alexander Gershfeld
//Resources provided by TA Aneesha
//Arup Guha
//COP3502
//10-8-2023

#include<stdio.h>
#include<string.h>

#define MAXPERSON 10
#define MAXCHAR 20

//function to find the index given a name
int findIndex(char person[]);

//calculates all of the permutations for a given n and array
void permRec(int* outputPerm, int* perm, int* used, int k, int n);

//prints the contents of the permutation array
void print(int perm[], int n);

//functions for checking conditions
int checkConditions(int* perm, int n);
int isTherePopcorn(int* perm, int n, int count);
int isTherePair(int* perm, int k, int n);

//Globals
int numberOfPersons;
char nameOfGuests[MAXPERSON][MAXCHAR];
int popcornHolders[MAXPERSON];
int seatBuddies[MAXPERSON][MAXPERSON];

int main() {
/*
 * Collecting input and configuring conditions
 */
    int unpaired, res, p1Index, p2Index;

    //strings holding pairs not be matched up
    char personOne[MAXCHAR];
    char personTwo[MAXCHAR];

    //Read in first input
    scanf("%d %d", &numberOfPersons, &unpaired);
    
    //Read in names and popcorn
    for(int i = 0; i < numberOfPersons; i++) {
        scanf("%s %d", nameOfGuests[i], &popcornHolders[i]);
        for(int j = 0; j < numberOfPersons; j++)
            //sets everyone to be able to sit together
            seatBuddies[i][j] = 1;
    }

    for(int i = 0; i < unpaired; i++) {
        scanf("%s %s", personOne, personTwo);

        //find the index of the two selected persons
        p1Index = findIndex(personOne);
        p2Index = findIndex(personTwo);

        //update the pairs array to make the pair not sit together
        seatBuddies[p1Index][p2Index] = 0;
        seatBuddies[p2Index][p1Index] = 0;
    }

/*
 * the permutations are ran backwards in order to record the last permutation that satisifes the conditions.
 * Since the perms are reversed, that means outputPerm records the first permutation that satisfies conditions.
 */
    int used[MAXPERSON] = {0};
    int perm[MAXPERSON] = {0};
    int outputPerm[MAXPERSON];
    
    permRec(outputPerm, perm, used, 0, numberOfPersons);

    //prints out the first perm to satisfy conditions
    print(outputPerm, 0);

    return 0;
}
int findIndex(char person[]) {
    for(int i = 0; i < numberOfPersons; i++)
        if(strcmp(nameOfGuests[i], person) == 0) return i;
    
    return -1;
}
void permRec(int* outputPerm, int* perm, int* used, int k, int n) {
    //start of call
    if (k == n) {
        //conditions are true, record the qualified perm to outputPerm
        if(checkConditions(perm, n)) 
            for(int i = 0; i < n; i++)
                outputPerm[i] = perm[i];
    }
    
    //creates the permutation then tests conditions, then creates another
    for(int i = n - 1; i >= 0; i--) {
        if(used[i]) continue;
        used[i] = 1; 
        perm[k] = i;
        permRec(outputPerm, perm, used, k+1, n); //calls here
        used[i] = 0; //returns here
    }

    //end of first call
}
int checkConditions(int* perm, int n) {
    if(isTherePopcorn(perm, n, 0) && isTherePair(perm, 0, n - 1)) return 1;
    return 0;
}
int isTherePopcorn(int* perm, int n, int count) { 
    //records neighbors of n
    int prev, next;
    
    for(int i = 0; i < n; i++) {
        prev = i - 1;
        next = i + 1;

        //has popcorn
        if(popcornHolders[perm[i]]) continue; 
        
        //next person has popcorn -- staying in bounds
        if(next < n)
            if(popcornHolders[perm[next]]) continue;
        
        //previous person has popcorn -- staying in bounds
        if(prev >= 0)
            if(popcornHolders[perm[prev]]) continue; 
      
        //person at index i does not have access to popcorn
        return 0;
    }
    
    //all conditions satisfied across perm[] 
    return 1;
}
int isTherePair(int* perm, int k, int n) {
    //base case - no conflict, return satisfied
    if(k == n) return 1;
    
    //the pair in perm corresponds to a false value in seatBuddies
    if(!seatBuddies[perm[k]][perm[k+1]]) return 0;

    //check next pair
    isTherePair(perm, k+1, n);
}
void print(int perm[], int n) {
    if(n == numberOfPersons) return;

    int index = perm[n];
    printf("%s\n", nameOfGuests[index]);

    print(perm, n+1);
}
