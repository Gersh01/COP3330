#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define QUEUESIZE 12
#define MAXCHAR 50

typedef struct customerInfo {
    char* name;
    int numOfTickets;
    int lineNum;
    int arrivalTime;
} customerInfo;

typedef struct customerNode {
    customerInfo* customer;
    customerNode* node;
} customerNode;

typedef struct queue {
    customerNode* front;
    customerNode* back;
    int size;
} queue;

//Adds the newly made customer into a linked list
customerNode* createNode();
//Creates a new customer, populating the struct with input values
customerInfo* createCustomer();

int main() {

    return 0;
}

customerNode* createNode() {

}
customerInfo* createCustomer() {

}



