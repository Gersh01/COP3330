//Recitation Program Assignment 2 - Sky Islands
//Alexander Gershfeld
//Arup Guha
//COP3502
//10-3-2023

#include<stdio.h>
#include<stdlib.h>

int** intializeGridRec(int** arr, int islands, int index);
void scanInputRec(int** islands, int iteration);
int travelIslandsRec(int** islands, int* traveled, int index);
int checkIslandRec(int* island, int index);
int checkTraveledRec(int* travelArr, int index);
void freeGridRec(int** grid, int index);

int garbage;

int main() {
    int islands, bridges;
    int i = 0;

    garbage = scanf("%d %d", &islands, &bridges);

    int** grid; 
    grid = intializeGridRec(grid, islands, i);
    int* traveled = (int*)calloc(islands, sizeof(int));
    traveled[0] = 1;

    scanInputRec(grid, bridges);

    if(travelIslandsRec(grid, traveled, 1) == 1) printf("YES\n");
    else printf("NO\n");

    free(traveled);
    freeGridRec(grid, islands-1);
    free(grid);
    return 0;
}
int** intializeGridRec(int** arr, int islands, int index) {
    if(index == 0) arr = (int**)calloc(islands, sizeof(int*));
    if(index >= islands) return arr;

    arr[index] = (int*)calloc(islands, sizeof(int));
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
int travelIslandsRec(int** islands, int* traveled, int index) {
    if(checkTraveledRec(traveled, 0)) return 1;

    traveled[index] = checkIslandRec(islands[index], 0);

    if(traveled[index] == 0) return 0;

    return travelIslandsRec(islands, traveled, index+1);
}
int checkIslandRec(int* island, int index) {
    if(island[index] == -1) return 0;

    if(island[index] == 1) {
        return 1;
    }
    if(island[index] == 0) return checkIslandRec(island, index+1);
    
    
    
}
int checkTraveledRec(int* travelArr, int index) {
    if(travelArr[index] == 1) return checkTraveledRec(travelArr, index+1);
    if(travelArr[index] == 0) return 0;

    return 1;
}  
void freeGridRec(int** grid, int index) {
    if(index == -1) return;

    free(grid[index]);
    freeGridRec(grid, index-1);
}
