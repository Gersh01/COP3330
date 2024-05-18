//Program Assignment 3a - Where to Sit
//Alexander Gershfeld
//Resources provided by TA Aneesha
//Arup Guha
//COP3502
//10-8-2023

#include<stdio.h>
#include<string.h>

#define MAXPERSON 10
#define MAXCHAR 20

//finds the index of the name given
int findIndex(char person[]);

//calculates all possible permutations
int permRec(int* perm, int* used, int k, int n);

//checks to see if those permutations created by permRec are satisfied
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
 * Calculating the correct number of permutations based on given conditions
 */
    int used[MAXPERSON] = {0};
    int perm[MAXPERSON] = {0};
    int result = 0;
    
    //returns the accumulation of satisfied conditions
    result = permRec(perm, used, 0, numberOfPersons);

    printf("%d\n", result);

    return 0;
}
int findIndex(char person[]) {
    for(int i = 0; i < numberOfPersons; i++)
        if(strcmp(nameOfGuests[i], person) == 0) return i;
    
    return -1;
}
//Function that creates the permutation
int permRec(int* perm, int* used, int k, int n) {
    if (k == n) {
        //returns either 1 or 0
        return checkConditions(perm, n); 
    }
    int res = 0;
    for(int i = 0; i < n; i++) {
        if(used[i]) continue;
        used[i] = 1; 
        perm[k] = i;

        //accumulates result based on perm return value
        res += permRec(perm, used, k+1, n);
        used[i] = 0;
    }

    return res;
}
/* parameters: perm, numberOfPersons
 * calls: isTherePopcorn() and isTherePair() 
 * 
 * */
int checkConditions(int* perm, int n) {
    if(isTherePopcorn(perm, n, 0) && isTherePair(perm, 0, n - 1)) return 1;
    return 0;
}
int isTherePopcorn(int* perm, int n, int count) { 
    int prev, next;
    
    for(int i = 0; i < n; i++) {
        //boundaries for i
        prev = i - 1;
        next = i + 1;

        //has popcorn
        if(popcornHolders[perm[i]]) continue; 
        
        //next has popcorn
        if(next < n)
            if(popcornHolders[perm[next]]) continue;
        
        //previous has popcorn
        if(prev >= 0)
            if(popcornHolders[perm[prev]]) continue; 
      
        //no popcorn can be accessed
        return 0;
    }
    
    //everyone in permutation has access to popcorn
    return 1;
}
int isTherePair(int* perm, int k, int n) {
    if(k == n) return 1;
    
    //returns 0 when pair (k, k+1) has a flagged value in seatBuddies
    if(!seatBuddies[perm[k]][perm[k+1]]) return 0;

    //checks next pair
    isTherePair(perm, k+1, n);
}
