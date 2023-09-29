//Recitation Program Assignment 2 - Sky Islands
//Alexander Gershfeld
//Arup Guha
//COP3502
//10-3-2023


#include<stdio.h>
#include<stdlib.h>

#define N 900

int checkIslands(int** islands, int* traveled, int i, int j, int finalIsland);

int main() {
    int islands, bridges;
    int** grid = (int**)calloc(N, sizeof(int*));
    int isl1, isl2, res;

    
    scanf("%d %d", &islands, &bridges);

    int* traveled = (int*)calloc(isl2, sizeof(int));

    for(int i = 0; i < N; i++) {
        grid[i] = (int*)calloc(N, sizeof(int));
        grid[i][i] = -1;
    }

    while(bridges > 0) {
        scanf("%d %d", &isl1, &isl2);

        grid[isl1 - 1][isl2 - 1] = 1;
        grid[isl2 - 1][isl1 - 1] = 1;
        
        bridges--;
    }

    res = checkIslands(grid, traveled, 0, 0, isl2);



    free(traveled);
    for(int i = 0; i < N; i++) free(grid[i]);
    free(grid);
    return 0;
}
int checkIslands(int** islands, int* traveled, int i, int j, int finalIsland) {
    //fail case
    if(i == 900 && j == 900) return 0;
    
    //base case
    if(traveled[finalIsland - 1] == 1) return 1;

    //island is the same as itself
    if(islands[i][j] == -1) checkIslands(islands, traveled, i, j+1, finalIsland);

    //island has a connection
    if(islands[i][j] == 1) {
        traveled[i] = 1; 
        checkIslands(islands, traveled, j, i+1, finalIsland);
    }
}
