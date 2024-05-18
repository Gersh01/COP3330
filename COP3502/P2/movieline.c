//Program Assignment 2 - Movie Line
//Alexander Gershfeld
//Arup Guha
//COP3502
//9-25-2023

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define QUEUESIZE 12
#define MAXCHAR 51

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
    int boothNum;
} q;

//These functions initializes memory, and declares the variables for its respective variable
customerInfo* createCustomer(char* newName, int newTickets, int newArrTime); 
customerNode* createNode(customerInfo* newCustomer);
q* createQ(int lineNo);

//These functions take in the customer and sorts them to their proper queues
int queueNum(q** queues, customerInfo* newCustomer);
int smallestQ(q** queues, q* singleQ);
int size(customerNode* node);
int emptyQ(q* queue); 
void enqueue(q* singleQ, customerInfo* newCustomer); 
customerNode* insertToBack(customerNode* newNode, customerInfo* newCustomer); 

//These functions sort the queues into booths and checkouts the queues per booth
int boothAssignment(int booth, int maxQ, q** queues); 
void checkoutBooth(int booth, int numQ, int limit, q** queues); 
q* getIndex(q** queues, int i);
customerNode* peek(q* queue);
customerInfo* dequeue(q* queue); 
int checkoutTime(customerInfo* newCustomer, int t); 

//These functions are responsible for freeing its elements, then itself
void freeCustomer(customerInfo* freeCust); 
void freeQueues(q** freeQ);

int totalQ, booths, custAmt, eof;

int main() {
    //FILE* input = fopen("input.in", "r");
    
    q** allQueues = (q**)calloc(QUEUESIZE, sizeof(q*));
    customerInfo* tmpCustomer = NULL;

    char tmpName[MAXCHAR];
    int tmpTickets, tmpLineNum, tmpArrTime, tmpQNum;
    int queuesPerBooth, excessQueues, checkoutPerBooth;

    //eof = fscanf(input, "%d %d", &custAmt, &booths); //input the amount of customers and functioning booths
    eof = scanf("%d %d", &custAmt, &booths); 

    //This loop creates the customer and calculates the queue number, to then be added to its queue's 
    //linked list. It will continue until all customers are loaded.
    while(custAmt != 0) {
        //eof = fscanf(input, "%s %d %d", tmpName, &tmpTickets, &tmpArrTime);
        eof = scanf("%s %d %d", tmpName, &tmpTickets, &tmpArrTime);

        //Create the customer struct and populate, making sure no memory errors occur.
        tmpCustomer = createCustomer(tmpName, tmpTickets, tmpArrTime);
        if(tmpCustomer == NULL) {
            printf("Error allocating memory for customer. Goodbye!\n");
            return 0;
        }

        //assigns the Queue number to the temporary customer at the time
        tmpQNum = queueNum(allQueues, tmpCustomer);

        //if the queue does not exist make it; if the queue fails to allocate memory end program
        if(allQueues[tmpQNum] == 0) allQueues[tmpQNum] = createQ(tmpQNum);
        if(allQueues[tmpQNum] == NULL) {
            printf("Error allocating memory for queue. Goodbye!\n");
            return 0;
        }

        //add the temporary customer to the assigned queue
        enqueue(allQueues[tmpQNum], tmpCustomer); 

        custAmt--;
    }

    //booth assignment time
    excessQueues = totalQ%booths; //remainder calculation
    for(int i = 1; i <= booths; i++) {
        queuesPerBooth = totalQ/booths; //integer division calculation

        //if theres a remainder then add the amount of queues that will be assigned to booth i
        if(excessQueues != 0) {
            queuesPerBooth++;
            excessQueues--; //decrement so that else statment is reached in loop
            checkoutPerBooth = boothAssignment(i, queuesPerBooth, allQueues);
        }
        //if there is no remainder then the amount of queues per booth stays the same
        else checkoutPerBooth = boothAssignment(i, queuesPerBooth, allQueues);

        //checkout customers from queue then print their info
        printf("Booth %d\n", i);
        checkoutBooth(i, queuesPerBooth, checkoutPerBooth, allQueues);
    }

    //free the queues, then free the array holding those queues
    freeQueues(allQueues);
    free(allQueues);
    //fclose(input);
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
q* createQ(int lineNo) {
    q* tmp = (q*)malloc(sizeof(q));
    tmp->front = NULL;
    tmp->back = NULL;
    tmp->size = 0;
    tmp->boothNum = 0;

    //when a queue is created, increase the global amount of queues
    totalQ++;
    return tmp;
}
int queueNum(q** queues, customerInfo* newCustomer) {
    int retVal = newCustomer->lineNum - 1; //conver to zero based

    //normal case - lineNum equals queue number
    if(newCustomer->lineNum != 0) return retVal; 

    //if the customer has a lineNum of 0 but is the first customer to be assigned a queue
    if(totalQ == 0) {
        newCustomer->lineNum++;
        return 0;
    }

    //when the customer has a lineNum of 0, assigns them to the first queue with the smallest size
    for(int i = 0; i < QUEUESIZE; i++) {
        if(emptyQ(queues[i]) == 1) continue;
        if(smallestQ(queues, queues[i]) == 1) {
            newCustomer->lineNum = i+1;
            return i;
        }
    }
}
int smallestQ(q** queues, q* singleQ) {
    int count = 0;

    //loops through all of the queues comparing the selected queue size to all other allocated queue sizes
    for(int j = 0; j < QUEUESIZE; j++) {
        if(emptyQ(queues[j]) == 1) continue;
        if(singleQ->size <= queues[j]->size) count++;
        if(count == totalQ) return 1;
    }
    return 0;
}
int size(customerNode* node) {
    customerNode* tmpNode = node;
    int count = 0;

    //uses a counter to count the amount of nodes that are pointing to memory
    while((tmpNode != NULL) || (tmpNode != 0)) {
        tmpNode = tmpNode->nextNode;   
        count++;
    }
    return count;
}
int emptyQ(q* queue) {
    if((queue == 0) || (queue->size == 0)) return 1;
    return 0;
}
void enqueue(q* singleQ, customerInfo* newCustomer) {
    //creates a node that is pointed to by front and back if the queue has nothing in it
    if(singleQ->size == 0) { 
        singleQ->front = createNode(newCustomer);
        singleQ->back = singleQ->front;
    }

    //if the queue has entries then insert the new customer to the back
    else singleQ->back = insertToBack(singleQ->back, newCustomer);  

    //update the size of the queue
    singleQ->size = size(singleQ->front);
}
customerNode* insertToBack(customerNode* newNode, customerInfo* newCustomer) {
    //points the next node to the new customer, then returns the nextNode to the back of the queue
    customerNode* tmpNode = createNode(newCustomer);
    newNode->nextNode = tmpNode;

    return tmpNode;
}
int boothAssignment(int booth, int maxQ, q** queues) {
    int ret = 0;
    for(int i = 0; i < QUEUESIZE; i++) {
        //ignore the queues with nothing in it
        if(emptyQ(queues[i]) == 1) continue;

        //as long as the queue at i is not already assigned, and as long as the amount of queues per booth
        //is not exceeded, then calculates the amount of times the booth will check a customer out.
        else if((maxQ != 0) && (queues[i]->boothNum == 0)) {
            queues[i]->boothNum = booth;
            ret = queues[i]->size + ret;
            maxQ--;
        }
    }  
    return ret; 
}
void checkoutBooth(int booth, int numQ, int limit, q** queues) {
    q** tmpQueues = (q**)calloc(numQ, sizeof(q*));
    q* tmpQueue = NULL;
    customerInfo* tmpCust = NULL;

    int count, index;
    int time = 0;

    //temporarily assigns the queues that match the selected booth to another array of queues
    for(int i = 0; i < numQ; i++)
        for(int j = 0; j < QUEUESIZE; j++)
            if((emptyQ(queues[j]) == 0) && (queues[j]->boothNum == booth)) {
                tmpQueues[i] = queues[j];
                queues[j]->boothNum = 0; //makes sure that each index is different 
                                         //boothNum is no longer needed
                break;
            }

    //loops until all of customers in each queue is dequeued, regardless of individual queue size
    while(limit > 0) {
        //finds the front of the queue with the smallest arrivalTime
        tmpQueue = getIndex(tmpQueues, numQ);

        //dequeues onto a customer and frees the node
        tmpCust = dequeue(tmpQueue);

        //catches when the queue is empty and adjusts the temporary queue array accordingly
        if(tmpQueue->front == 0) {
            for(int i = 0, j = 0; i < numQ - 1; j++) {
                if(emptyQ(tmpQueues[j]) == 1) continue;
                tmpQueues[i] = tmpQueues[j];
                i++;
            }
            numQ--;
        }

        //calculates the checkout time for the tmpCust at the time
        time = checkoutTime(tmpCust, time);
        printf("%s from line %d checks out at time %d\n", tmpCust->name, tmpCust->lineNum, time);

        //customer is no longer needed and freed
        freeCustomer(tmpCust);
        limit--;
    }
    printf("\n");

    //the temporary array of queues is no longer needed, and space is freed for the next booth
    free(tmpQueues);
}
q* getIndex(q** queues, int i) {
    int count;
    for(int j = 0; j < i; j++) {
        count = 0; 
        for(int k = 0; k < i; k++) {
            if((emptyQ(queues[j]) == 1 ) || (emptyQ(queues[k]) == 1)) continue;
            if(peek(queues[j])->customer->arrivalTime <= peek(queues[k])->customer->arrivalTime) count++;
            if(count == i) return queues[j];
        }
    }
}
customerNode* peek(q* queue) {
    return queue->front;
}
customerInfo* dequeue(q* queue) {
    customerNode* tmpNode;
    customerInfo* tmpCust; 

    //places the customer struct onto a new tmpCust; the linked list is updated to remove the previous node
    tmpCust = peek(queue)->customer;
    tmpNode = queue->front;
    queue->front = queue->front->nextNode;

    //if the queue is empty, the back is updated to reflect the state of the front
    if(queue->front == NULL) {
        queue->back == queue->front;
    }

    //further updates the queue information and frees the node from the queue
    queue->size--;
    free(tmpNode);

    return tmpCust;
}
int checkoutTime(customerInfo* newCustomer, int t) {
    int checkout = (30 + (newCustomer->numOfTickets * 5));
    
    //adds the customer arrival time if it is greater than the previous checkout time, also when time = 0
    if(newCustomer->arrivalTime > t) checkout += newCustomer->arrivalTime;

    //adds the previous checkout time to calculation when arrival time is less
    if(newCustomer->arrivalTime < t) checkout += t;
     
    return checkout;
}
void freeCustomer(customerInfo* freeCust) {
    free(freeCust->name);
    free(freeCust);
}
void freeQueues(q** freeQ) {
    for(int i = 0; i < QUEUESIZE; i++)
        free(freeQ[i]);
}

