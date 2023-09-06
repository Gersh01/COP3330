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
void add_order(theaterrow* this_row, order* this_order);
//if a seat in a row is owned, return the name, otherwise NULL
char* get_owner(theaterrow** theater, int row, int seat_num);
//does the same thing as the previous function but for the selected row and seat number
char* get_row_owner(theaterrow* this_row, int seat_num);
//returns 1 if the seat number compared is contained in the range of seats under myorder
int contains(order* myorder, int seat_no);
void free_order(order* this_order);
void free_row(theaterrow* this_row);

int main() {
    theaterrow** regal = calloc(MAXROWS+1, sizeof(theaterrow*));

    free(regal);
    return 0;
}
order* make_order(int start, int end, char* this_name) {

}
theaterrow* make_empty_row() {

}
int conflict(order* order1, order* order2) {

}
int can_add_order(theaterrow* this_row, order* this_order) {

}
void add_order(theaterrow* this_row, order* this_order) {

}
char* get_owner(theaterrow** theater, int row, int seat_num) {

}
char* get_row_owner(theaterrow* this_row, int seat_num) {

}
int contains(order* myorder, int seat_no) {

}
void free_order(order* this_order) {

}
void free_row(theaterrow* this_row) {

}
