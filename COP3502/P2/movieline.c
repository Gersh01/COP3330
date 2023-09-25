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

customerInfo* createCustomer(char* newName, int newTickets, int newArrTime); 
customerNode* createNode(customerInfo* newCustomer);
q* createQ(int lineNo);
customerNode* insertToBack(customerNode* newNode, customerInfo* newCustomer); 
int queueNum(q** queues, customerInfo* newCustomer);
int smallestQ(q** queues, q* singleQ);
int emptyQ(q* queue); 
customerNode* peek(q* queue);
void enqueue(q* singleQ, customerInfo* newCustomer); 
int boothAssignment(int booth, int maxQ, q** queues); 
void checkoutBooth(int booth, int numQ, int limit, q** queues); 
q* getIndex(q** queues, int i);
customerInfo* dequeue(q* queue); 
int checkoutTime(customerInfo* newCustomer); 
void freeCustomer(); 
void freeNode();

int totalQ, booths, custAmt;

int main() {
    customerInfo* tmpCustomer = NULL;
    q** allQueues = (q**)calloc(QUEUESIZE, sizeof(q*));

    char tmpName[MAXCHAR];
    int tmpTickets, tmpLineNum, tmpArrTime, tmpQNum;
    int queuesPerBooth, excessQueues;

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

    //booth assignment time
    excessQueues = totalQ%booths;
    int checkoutPerBooth;
    for(int i = 1; i <= booths; i++) {
        queuesPerBooth = totalQ/booths;     
        if(excessQueues != 0) {
            queuesPerBooth++;
            excessQueues--;
            checkoutPerBooth = boothAssignment(i, queuesPerBooth, allQueues);
        }
        else checkoutPerBooth = boothAssignment(i, queuesPerBooth, allQueues);

        printf("\nBooth %d\n", i);
        checkoutBooth(i, queuesPerBooth, checkoutPerBooth, allQueues);
        //printf("\n");
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
q* createQ(int lineNo) {
    q* tmp = (q*)malloc(sizeof(q));
    tmp->front = NULL;
    tmp->back = NULL;
    tmp->size = 0;
    tmp->boothNum = 0;

    totalQ++;
    return tmp;
}
customerNode* insertToBack(customerNode* newNode, customerInfo* newCustomer) {
    customerNode* tmpNode = createNode(newCustomer);
    newNode->nextNode = tmpNode;

    return tmpNode;
}
int queueNum(q** queues, customerInfo* newCustomer) {
    int retVal = newCustomer->lineNum - 1;
    if(newCustomer->lineNum != 0) return retVal;
    if(totalQ == 0) {
        newCustomer->lineNum++;
        return 0;
    }
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

    for(int j = 0; j < QUEUESIZE; j++) {
        if(emptyQ(queues[j]) == 1) continue;
        if(singleQ->size <= queues[j]->size) count++;
        if(count == totalQ) return 1;
    }
    return 0;
}
int emptyQ(q* queue) {
    if((queue == 0) || (queue->size == 0)) return 1;
    return 0;
}
customerNode* peek(q* queue) {
    return queue->front;
}
void enqueue(q* singleQ, customerInfo* newCustomer) {
    if(singleQ->size == 0) { 
        singleQ->front = createNode(newCustomer);
        singleQ->back = singleQ->front;
    }
    else singleQ->back = insertToBack(singleQ->back, newCustomer);
    
    singleQ->size++;   
}
int boothAssignment(int booth, int maxQ, q** queues) {
    int ret = 0;
    for(int i = 0; i < QUEUESIZE; i++) {
        if(emptyQ(queues[i]) == 1) continue;
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

    int count, index, time = 0;

    for(int i = 0; i < numQ; i++)
        for(int j = 0; j < QUEUESIZE; j++)
            if((emptyQ(queues[j]) == 0) && (queues[j]->boothNum == booth)) {
                tmpQueues[i] = queues[j];
                queues[j]->boothNum = 0;
                break;
            }

    while(limit > 0) {
        tmpQueue = getIndex(tmpQueues, numQ);
        tmpCust = dequeue(tmpQueue);

        if(tmpQueue->front == 0) {
            numQ--;
            for(int i = 0; i < numQ; i++) {
                tmpQueues[i] = tmpQueues[i+1];
            }
            
        }
        time = checkoutTime(tmpCust) + time;
        printf("%s from line %d checks out at time %d\n", tmpCust->name, tmpCust->lineNum, time);
        limit--;
    }
    free(tmpQueues);
}
q* getIndex(q** queues, int i) {
    int count = 0;
    for(int j = 0; j < i; j++) 
        for(int k = 0; k < i; k++) {
            if((emptyQ(queues[j]) == 1 ) || (emptyQ(queues[k]) == 1)) continue;
            if(peek(queues[j])->customer->arrivalTime <= peek(queues[k])->customer->arrivalTime) count++;
            if(count == i) return queues[j];
        }
}
customerInfo* dequeue(q* queue) {
    customerNode* tmpNode;
    customerInfo* tmpCust; 

    tmpCust = peek(queue)->customer;
    tmpNode = queue->front;
    queue->front = queue->front->nextNode;

    if(queue->front == NULL) {
        queue->back == queue->front;
    }

    queue->size--;
    free(tmpNode);

    return tmpCust;
}
int checkoutTime(customerInfo* newCustomer) {
    int checkout = (30 + (newCustomer->numOfTickets * 5)) + newCustomer->arrivalTime; 
    return checkout;
}
void freeCustomer() {

}
void freeNode() {

}

