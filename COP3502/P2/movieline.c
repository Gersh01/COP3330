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

typedef struct q {
    customerNode* front;
    customerNode* back;
    int size;
} q;

//Adds the newly made customer into a linked list
customerNode* createNode();
//Creates a new customer, populating the struct with input values
customerInfo* createCustomer(char* newName, int newTickets, int newArrTime);

int main() {
    int custAmt, booths;
    customerInfo* tmpCustomer;
    char* tmpName;
    int tmpTickets, tmpLineNum, tmpArrTime;
    printf("Enter the amount of customers and then the amount of booths\n");
    scanf("%d %d", &custAmt, &booths);

    printf("Please enter the customers coming into line\n");
    while(custAmt != 0) {
        scanf("%s %d %d", tmpName, &tmpTickets, &tmpArrTime);
        tmpCustomer = createCustomer(tmpName, tmpTickets, tmpArrTime);

        custAmt--;
    }

    return 0;
}

customerInfo* createCustomer(char* newName, int newTickets, int newArrTime) {
    

}
customerNode* createNode() {

}

q* createQ() {

}



