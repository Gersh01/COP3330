//Program Assignment 2 - Movie Line
//Alexander Gershfeld
//Arup Guha
//COP3502
//9-25-2023

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
    struct customerNode* nextNode;
} customerNode;

typedef struct q {
    customerNode* front;
    customerNode* back;
    int size;
    int numElements;
} q;

//Adds the newly made customer into a linked list
customerNode* createNode(customerInfo* newCustomer);
//Inserts new node to the front of the list
customerNode* insertToBack(customerNode* newNode, customerInfo* newCustomer);
//Creates a new customer, populating the struct with input values
customerInfo* createCustomer(char* newName, int newTickets, int newArrTime);
//Calculates the queue number for each customer
int queueNum(q** queues, customerInfo* newCustomer);
//Compares queues to find the smallest one
int smallestQ(q** queues, q* singleQ);
//Creates the memory for the queue
q* createQ(int lineNo);

void enqueue(q* singleQ, customerInfo* newCustomer);

int emptyQ(q* queue);

int totalQ;

int main() {
    
    customerInfo* tmpCustomer = NULL;
    q** allQueues = (q**)calloc(QUEUESIZE, sizeof(q*));

    char tmpName[MAXCHAR];
    int custAmt, booths;
    int tmpTickets, tmpLineNum, tmpArrTime, tmpQNum;

    scanf("%d %d", &custAmt, &booths); //input the amount of customers and functioning booths
    
    //Itemizes all of the input customers into one concise linked list; to then be processed one
    //list item at a time. 
    while(custAmt != 0) {
        scanf("%s %d %d", tmpName, &tmpTickets, &tmpArrTime);

        //Create the customer struct and populate, making sure no memory errors occur.
        tmpCustomer = createCustomer(tmpName, tmpTickets, tmpArrTime);
        if(tmpCustomer == NULL) {
            printf("Error allocating customer\n");
            return 0;
        }

        //assigns the Queue number to the temporary customer at the time
        tmpQNum = queueNum(allQueues, tmpCustomer);

        //if the queue does not exist make it
        if(allQueues[tmpQNum] == 0) allQueues[tmpQNum] = createQ(tmpQNum);

        //add the temporary customer to the assigned queue
        enqueue(allQueues[tmpQNum], tmpCustomer); 

        

        custAmt--;
    }

    free(tmpCustomer->name);
    free(tmpCustomer);
    return 0;
}

customerInfo* createCustomer(char* newName, int newTickets, int newArrTime) {
    customerInfo* tmp = (customerInfo*)malloc(sizeof(customerInfo));
    
    //allocate and assign name for customer
    tmp->name = (char*)calloc(MAXCHAR, sizeof(char));
    if(tmp->name != NULL) 
        strcpy(tmp->name, newName);
    else return 0;

    //assign number of tickets and arrival time
    tmp->numOfTickets = newTickets;
    tmp->arrivalTime = newArrTime;
    
    //calculate the queue flag for each customer
    tmp->lineNum = (tmp->name[0] - 'A') % 13; 

    return tmp;
}
customerNode* createNode(customerInfo* newCustomer) {
    customerNode* tmp = (customerNode*)malloc(sizeof(customerNode));

    tmp->customer = newCustomer; 
    tmp->nextNode = NULL;

    return tmp;
}
customerNode* insertToBack(customerNode* newNode, customerInfo* newCustomer) {
    customerNode* tmpNode = createNode(newCustomer);
    newNode->nextNode = tmpNode;

    return tmpNode;
}
q* createQ(int lineNo) {
    q* tmp = (q*)malloc(sizeof(q));
    tmp->front = NULL;
    tmp->back = NULL;
    tmp->size = 0;
    tmp->numElements = 0;

    totalQ++;
    return tmp;
}
int queueNum(q** queues, customerInfo* newCustomer) {
    int retVal = newCustomer->lineNum;

    if(retVal != 0) return retVal;
    if(totalQ == 0) return 0;
    for(int i = 0; i < QUEUESIZE; i++) {
        if(emptyQ(queues[i]) == 0) continue;
        if(smallestQ(queues, queues[i]) == 1) return i;
    }

    return retVal;
}
int smallestQ(q** queues, q* singleQ) {
    int count = 0;

    for(int j = 0; j < QUEUESIZE; j++) {
        if(emptyQ(queues[j]) == 0) continue;
        if(singleQ->size <= queues[j]->size) count++;
        if(count == totalQ) return 1;
    }
    return 0;
}
int emptyQ(q* queue) {
    if((queue == 0) || (queue->size == 0)) return 1;
    return 0;
}

void enqueue(q* singleQ, customerInfo* newCustomer) {
    if(singleQ->size == 0) { 
        singleQ->front = createNode(newCustomer);
        singleQ->back = singleQ->front;
    }
    else singleQ->back = insertToBack(singleQ->back, newCustomer);
    
    singleQ->size++;
    singleQ->numElements++;    
}
int dequeue() {
    return 0;
}
int front() {
    return 0;
}
