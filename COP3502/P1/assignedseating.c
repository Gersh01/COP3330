//Program Assignment 1 - Assigned Seating
//Alexander Gershfeld
//Arup Guha
//COP3502
//9-10-2023

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define INITSIZE 10
#define MAXLEN 50
#define MAXROWS 100000 //one hundred thousand

//where the order details are stored
typedef struct order {
    int s_seat;
    int e_seat;
    char* name;
} order;

//this manages a single row ; in each theater row contains a set of orders
typedef struct theaterrow {
    //pointer pointing to other orders within a single row
    order** list_orders;
    int max_size;
    int cur_size;
} theaterrow;

//takes in the input to purchase an order; array for name DMA; then strcpyd onto struct
order* make_order(int start, int end, char* this_name);
//allocate memory for the row while setting a limit as well as the size to 0
theaterrow* make_empty_row();
//returns a value based on whether the orders inputted, from the same row, are conflicting
int conflict(order* order1, order* order2);
//returns a 0 or 1 on whether the seats within the order are taken or not
int can_add_order(theaterrow* this_row, order* this_order);
//will adds this order to this row, if success then 1, if no then 0. adjusts memory if needed.
int add_order(theaterrow* this_row, order* this_order);
//if a seat in a row is owned, return the name, otherwise NULL
char* get_owner(theaterrow** theater, int row, int seat_num);
//does the same thing as the previous function but for the selected row and seat number
char* get_row_owner(theaterrow* this_row, int seat_num);
//returns 1 if the seat number compared is contained in the range of seats under myorder
int contains(order* myorder, int seat_no);
void free_order(order* this_order);
void free_row(theaterrow* this_row);

int main() {
    theaterrow** regal = calloc(MAXROWS+1, sizeof(theaterrow*)); //where all rows then orders are located

    char input[MAXLEN * 2]; //allocates enough space for name and seating   
    char *option, *tmpName;
    int tmpRow, tmpSeatStart, tmpSeatEnd;
    int onSwitch = 1;
    
    //sentinel driven loop
    while(onSwitch) {
        int result; //variable that tracks success or failure with adding orders
        fgets(input, MAXLEN + 10, stdin);
        input[strcspn(input, "\n")] = 0; //gets rid of return value in input
        option = strtok(input, " "); //breaks down first word; used to direct the loop

        //buy command menu
        if(strcmp("BUY", option) == 0) {
            //variables of input further broken down
            tmpRow = (atoi(strtok(NULL, " "))) - 1;     //
            tmpSeatStart = atoi(strtok(NULL, " "));     // Converts string token to an integer
            tmpSeatEnd = atoi(strtok(NULL, " "));       //
            tmpName = strtok(NULL, " ");

            //creation of the order as well as any necessary rows
            order* tmpOrder = make_order(tmpSeatStart, tmpSeatEnd, tmpName);
            if(regal[tmpRow] == NULL) {
                regal[tmpRow] = make_empty_row();
            }

            //adding the order to the main list only if it acceptable, then printed whether it is or not
            result = add_order(regal[tmpRow], tmpOrder); //all changes in this function will be applied to the row of user choice
            if(result == 0) {
                printf("Failure\n");
            }
            else if(result == 1) {
                printf("Success\n");
            }
        }
        else if(strcmp("LOOKUP", option) == 0) {
            printf("This works\n");
        }
        //exit condition
        else if(strcmp("QUIT", option) == 0) {
            onSwitch = 0; //off switch :)
            //passes the rows of the main double pointer as well as its constituents to be freed
            for(int i = 0; i < MAXROWS + 1; i++) {
                free_row(regal[i]);
            }
            
        }    
    }
    
    free(regal);
    return 0;
}
order* make_order(int start, int end, char* this_name) {
    order* tmp = (order*)malloc(sizeof(order));
    tmp->name = (char*)calloc(MAXLEN, sizeof(char));
    tmp->s_seat = start;
    tmp->e_seat = end;
    strcpy(tmp->name, this_name);

    return tmp;
}
theaterrow* make_empty_row() {
    theaterrow* tmp = (theaterrow*)malloc(sizeof(theaterrow));
    tmp->cur_size = 0;
    tmp->max_size = INITSIZE;
    tmp->list_orders = (order**)calloc(tmp->max_size - 1, sizeof(order*));
    for(int i = 0; i < tmp->max_size; i++) {
        tmp->list_orders[i] = (order*)malloc(sizeof(order));
    }

    return tmp;
}
int conflict(order* order1, order* order2) {
    for(int i = order1->s_seat; i <= order1->e_seat; i++) {
        for(int j = order2->s_seat; j <= order2->e_seat; j++) {
            if(i == j) {
                return 1;
            }
        }
    }
    return 0;
}
int can_add_order(theaterrow* this_row, order* this_order) {
    //Check for any conflicts among all orders in the row
    int res;
    for(int i = 0; i < this_row->cur_size; i++) {
        res = conflict(this_row->list_orders[i], this_order);  
        if(res == 1) {
            return 0; //there is conflict
        }
    }
    return 1;
}
int add_order(theaterrow* this_row, order* this_order) {
    if(can_add_order(this_row, this_order) == 0) {
        return 0; //cannot add order
    }

    //Row needs more memory
    if(this_row->cur_size == this_row->max_size) {
        order** tmpList = (order**)calloc(this_row->max_size - 1, sizeof(order*));
        tmpList = this_row->list_orders;
        int newMax = this_row->max_size * 2;
        int tmpCur = this_row->cur_size;
        
        this_row = (theaterrow*)realloc(this_row, newMax * sizeof(theaterrow));
        this_row->list_orders = (order**)realloc(this_row->list_orders, newMax * sizeof(order*));
        this_row->list_orders = tmpList;
        for(int i = this_row->cur_size; i < newMax; i++) {
            this_row->list_orders[i] = (order*)malloc( sizeof(order));
        }

        this_row->max_size = newMax;
        this_row->cur_size = tmpCur;
    }

    //Order can be added to row
    this_row->list_orders[this_row->cur_size] = this_order;
    this_row->cur_size++;
    return 1;
}
    
    
/*
char* get_owner(theaterrow** theater, int row, int seat_num) {

}
char* get_row_owner(theaterrow* this_row, int seat_num) {

}
int contains(order* myorder, int seat_no) {

}
*/
void free_order(order* this_order) {
    free(this_order->name);
    free(this_order);
}
void free_row(theaterrow* this_row) {
    //filters out rows that were not used
    if(this_row == NULL) {
        return;
    }
    //uses the free order function iterated up to current size of row used
    for(int i = 0; i < this_row->cur_size; i++) {
        free_order(this_row->list_orders[i]);
    }
    //empty orders in a given row are also freed
    for(int j = this_row->cur_size; j < this_row->max_size; j++) {
        free(this_row->list_orders[j]);
    }
    free(this_row);
}
