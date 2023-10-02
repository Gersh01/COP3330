//Recitation Program Assignment 2 - Sky Islands
//Alexander Gershfeld
//Arup Guha
//COP3502
//10-3-2023

#include<stdio.h>
#include<stdlib.h>

#define N 900

int** intializeGridRec(int** arr, int islands, int index);
void scanInputRec(int** islands, int iteration);
int travelIslandsRec(int** islands, int* traveled, int index, int off);
int checkIslandRec(int* island, int index, int off);
int checkTraveledRec(int* travelArr, int index, int count, int maxIsland);
void freeGridRec(int** grid, int index);

int garbage;

int main() {
    int islands, bridges;
    int i = 0;

    garbage = scanf("%d %d", &islands, &bridges);

    int** grid; 
    grid = intializeGridRec(grid, islands, i);
    int* traveled = (int*)calloc(N+1, sizeof(int));
    

    scanInputRec(grid, bridges);

    if(travelIslandsRec(grid, traveled, 0, 0) == 1) {
        if(checkTraveledRec(traveled, i, i, islands)) printf("YES\n");
        else printf("NO\n");
    }

    free(traveled);
    freeGridRec(grid, N-1);
    free(grid);
    return 0;
}
int** intializeGridRec(int** arr, int islands, int index) {
    if(index == 0) arr = (int**)calloc(N, sizeof(int*));
    if(index == N) return arr;

    arr[index] = (int*)calloc(N, sizeof(int));
    arr[index][index] = -1;

    intializeGridRec(arr, islands, index+1);
}
void scanInputRec(int** islands, int iteration) {
    int isl1, isl2;
    if(iteration < 1) return;

    garbage = scanf("%d %d", &isl1, &isl2);
    islands[isl1 - 1][isl2 - 1] = 1;
    islands[isl2 - 1][isl1 - 1] = 1;

    scanInputRec(islands, iteration - 1);
}
int travelIslandsRec(int** islands, int* traveled, int index, int off) {

    if(index == N) return 1;

    //if(islands[0][index] == 1) traveled[0] = 1;

    if(checkIslandRec(islands[index], 0, off)) {
        traveled[index] = 1;
        return travelIslandsRec(islands, traveled, index+1, 1);
    }
    //traveled[index] = checkIslandRec(islands[index], 0, off);
    return travelIslandsRec(islands, traveled, index+1, off);
    
}
int checkIslandRec(int* island, int index, int off) {
    if(off == 1) {
        if(island[index] == -1) return 0;
    }
   
    if(index == N) return 0;

    if(island[index] == 1) return 1;
    
    if(island[index] == 0) return checkIslandRec(island, index+1, off);
}
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
