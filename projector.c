//Program Assignment 4 - Projector Problems
//Alexander Gershfeld
//Arup Guha
//COP3502
//10-29-2023

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define PI 3.14159265358979323

typedef struct group {
    int xaxis;
    int yaxis;
    int people;
    double angle;
} group;

//creates an array of customers with their own structs
group* populateCustomers();

//utilizes mergesort to sort the customers
void mergeSort(group* list, int low, int high);
void merge(group* list, int low, int mid, int high);

//sweeps through sorted array to find the second main goal
double angleSweep(group* list);

//sweeps through every possible given angle to find first main goal
int leastInProjector(group* list);

//first two inputs
int N, A;

int main() {
    group* customers;
    double idealAngle;

    //scan input of first line
    scanf("%d %d", &N, &A);

    //return an array that places all the groups into a double sized array
    customers = populateCustomers();
    
    //perform the merge sort
    mergeSort(customers, 0, (N*2)-1);

    //returns the double of the ideal angle
    idealAngle = angleSweep(customers);

    //if that angle is greater than given, it can be ascertained 
    //that there would be no one in the given angle
    if(idealAngle > A) printf("0\n");
    
    //else find that minimum amount of people, then immediately print it out
    else printf("%d\n", leastInProjector(customers));

    //now pring the angle
    printf("%.4lf\n", idealAngle);

    free(customers);

    return 0;
}
group* populateCustomers() {
    //allocate twice the size of the input
    group* tmp = (group*)calloc(N*2, sizeof(group));
     
    for(int i = 0; i < N; i++) {
        //scan in each N
        scanf("%d %d %d", &(tmp + i)->xaxis, &(tmp + i)->yaxis, &(tmp + i)->people);

        //calculate the angle for each group
        (tmp + i)->angle = (atan2((tmp + i)->yaxis, (tmp + i)->xaxis));
        
        //duplicate contents across the array
        tmp[i + N] = tmp[i];

        //update the new angles of the duplicated entries
        (tmp + (i + N))->angle = ((tmp + i)->angle) + (2 * PI);
    }

    return tmp;
}
void mergeSort(group* list, int low, int high) {
    if(low < high) {
        //calculate the mid point of each side
        int mid = (low + high)/2;

        //recursively find the one index sorted array for left
        mergeSort(list, low, mid);

        //recursively find the one index sorted array for right
        mergeSort(list, mid + 1, high);
        
        //once one of the recursive calls breaks merge, since the break means that one index merges, 
        //then two, then four etc.. until there is no more returns in the original recursive call.
        merge(list, low, mid + 1, high);
    }
}
void merge(group* list, int low, int mid, int high) {
    //initialize the boundaries of the array passed through
    int len = (high - low) + 1;
    int index1 = low, index2 = mid, cur = 0;
    
    //allocate memory for array to copy from list onto tmp
    group* tmp = (group*)calloc(len, sizeof(group));

    while(index1 < mid || index2 <= high) {
        //if the indices are in bounds, and the angle to the left is less than the right then
        //place the left entry in the current size of the tmp array, index1 increases
        if(index2 > high || (index1 < mid && (list + index1)->angle < (list + index2)->angle)) {
            tmp[cur] = list[index1];
            index1++;
        }
        //else the entry in index2 is placed in the current size of tmp, increase index2
        else {
            tmp[cur] = list[index2];
            index2++;
        }

        //if or else must have occured, now increase the size of tmp array
        cur++;
    }

    //after the tmp array has been filled, copy over the result to the original list
    for( int i = low; i <= high; i++) 
        list[i] = tmp[i - low];

    //sayonara tmp array
    free(tmp);
}
double angleSweep(group* list) {
    //initialize the starting values, and conver the given angle to radians
    int j = 1, i = 0;
    double givenAngle = A * (PI/180);

    //declare the difference in angles, and initialize a minimum ideal angle
    double angleDiff, endAngle = 0; 

    while(j < N*2) {
        //calculate the difference in angles
        angleDiff = list[j].angle - list[i].angle;

        //if greater than the angle given to the program, then the question has been answered for this iteration
        if(angleDiff > givenAngle) {
            endAngle = angleDiff;
            i++;
            j++;
        }
        //otherwise update the angle still if the difference is greater then the previously saved angle
        else {
            if(angleDiff > endAngle) endAngle = angleDiff;

            i++;
            j++;
        }
       
    }

    //returns back into degrees
    return endAngle * (180/PI);
}
int leastInProjector(group* list) {
    //least is set at the maximum amount of people that can ever be in ray
    int calc, least = 1000 * 1000;
    int i = 0, j = 1;
    double angle = A * (PI/180);

    while(j < N*2) {
        //resets the calculated number each iteration
        calc = 0;

        //if the angle is less than the given angle, increase the ray vision
        if((list[j].angle - list[i].angle) <= angle) j++;
        
        //if the ray is now greater than the given angle, calculate the people inside of it
        //and compare to the least number.
        else if((list[j].angle - list[i].angle) > angle) {
            for(int k = i + 1; k < j; k++) {
                calc += list[k].people;

                //in order to save runtime
                if(calc >= least) break;
            }
            
            //save the calculated number, if it is less than the least
            if(calc < least) least = calc;

            i++;
        }
    }

    return least;
}

