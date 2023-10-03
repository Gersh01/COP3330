//Recitation Program Assignment 2 - Sky Islands
//Alexander Gershfeld
//Arup Guha
//COP3502
//10-3-2023

#include<stdio.h>
#include<stdlib.h>

#define N 900

//Functions for taking input
int** intializeGridRec(int** arr, int islands, int index);
int scanInputRec(int** islands, int iteration, int lowest);

//Functions to determine island connectivity
int travelIslandsRec(int** islands, int* traveled, int index);
int checkIslandRec(int* island, int index);
int checkTraveledRec(int* travelArr, int index, int count, int maxIsland);

//Freedom!
void freeGridRec(int** grid, int index);

int main() {
    int islands, bridges, lowest;
    int i = 0;

    //checks to see if scanf succeeds
    if(scanf("%d %d", &islands, &bridges) == 0) return 0;

    int** grid; 

    //initializes the grid and its indices
    grid = intializeGridRec(grid, islands, i);
    int* traveled = (int*)calloc(N+1, sizeof(int));
    
    //calculates the starting point | the lowest island number
    lowest = scanInputRec(grid, bridges, N+1) - 1;

    //since we start at the lowest island, set its traveled index to 1
    traveled[lowest] = 1;

    //if the travelIslandsRec succeeds, then test to see if all of the islands have been traveled to
    if(travelIslandsRec(grid, traveled, lowest+1) == 1) {
        if(checkTraveledRec(traveled, i, i, islands)) printf("YES");
        else printf("NO");
    }

    free(traveled);
    freeGridRec(grid, N-1);
    free(grid);
    return 0;
}

/*  Allocates memory for pointers
 *  Allocates the memory that the pointers are referenced to
 *  Sets a control value for islands connecting to themselves
 * */
int** intializeGridRec(int** arr, int islands, int index) {
    if(index == 0) arr = (int**)calloc(N, sizeof(int*));
    if(index == N) return arr;

    arr[index] = (int*)calloc(N, sizeof(int));
    arr[index][index] = -1;

    intializeGridRec(arr, islands, index+1);
}

/*  Uses the amount of bridges as iteration to scan input
 *  If either inputs is lower than the max amount of islands, then rewire
 *  Sets part of grid where input is held to 1
 * */
int scanInputRec(int** islands, int iteration, int lowest) {
    int isl1, isl2;
    if(iteration < 1) return lowest;

    if(scanf("%d %d", &isl1, &isl2) == 0) return 0;

    if(isl1 < lowest) lowest = isl1;
    else if(isl2 < lowest) lowest = isl2;

    if(isl2 < lowest) lowest = isl2;
    else if(isl1 < lowest) lowest = isl1;

    islands[isl1 - 1][isl2 - 1] = 1;
    islands[isl2 - 1][isl1 - 1] = 1;

    scanInputRec(islands, iteration - 1, lowest);
}

/*  Checks using a recursive function if the island can be traveled to 
 *  based on previous islands before it
 *  This function repeats until all islands are checked (N)
 * */
int travelIslandsRec(int** islands, int* traveled, int index) {
    if(index == N) return 1;

    if(checkIslandRec(islands[index], 0)) {
        traveled[index] = 1;
        return travelIslandsRec(islands, traveled, index+1);
    }
    return travelIslandsRec(islands, traveled, index+1);

    return 0;
}

/*  Recursivly checks if index has a connection
 *  if island at index is equal to the island itself (-1) return 
 * */
int checkIslandRec(int* island, int index) {
    if(island[index] == -1) return 0;
   
    if(index == N) return 0;

    if(island[index] == 1) return 1;
    
    if(island[index] == 0) return checkIslandRec(island, index+1);
}

/*  Sets a counter, when it has met the max amount of islands provided return
 *  counter increments only if traveled at index is 1
 * */
int checkTraveledRec(int* travelArr, int index, int count, int maxIsland) {
    if(count == maxIsland) return 1;
    if(index == N) return 0;

    if(travelArr[index] == 1) return checkTraveledRec(travelArr, index+1, count+1, maxIsland);
    if(travelArr[index] == 0) return checkTraveledRec(travelArr, index+1, count, maxIsland);
}  
void freeGridRec(int** grid, int index) {
    if(index == -1) return;

    free(grid[index]);
    freeGridRec(grid, index-1);
}
