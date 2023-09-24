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
customerInfo* peek(q* queue);
void enqueue(q* singleQ, customerInfo* newCustomer); 
void boothAssignment(int booth, int maxQ, q** queues); 
void checkoutBooth(int limit, q** queues); 
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
    for(int i = 1; i <= booths; i++) {
        queuesPerBooth = totalQ/booths;     
        if(excessQueues != 0) {
            queuesPerBooth++;
            excessQueues--;
            boothAssignment(i, queuesPerBooth, allQueues);
        }
        else boothAssignment(i, queuesPerBooth, allQueues);

        printf("Booth %d\n", i);
        checkoutBooth(queuesPerBooth, allQueues);
        printf("\n");
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
    int retVal = newCustomer->lineNum;

    if(retVal != 0) return retVal - 1;
    if(totalQ == 0) return 0;
    for(int i = 0; i < QUEUESIZE; i++) {
        if(emptyQ(queues[i]) == 1) continue;
        if(smallestQ(queues, queues[i]) == 1) return i;
    }

    newCustomer->lineNum = retVal - 1;
    return retVal - 1;
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
customerInfo* peek(q* queue) {
    return queue->front->customer;
}
void enqueue(q* singleQ, customerInfo* newCustomer) {
    if(singleQ->size == 0) { 
        singleQ->front = createNode(newCustomer);
        singleQ->back = singleQ->front;
    }
    else singleQ->back = insertToBack(singleQ->back, newCustomer);
    
    singleQ->size++;   
}
void boothAssignment(int booth, int maxQ, q** queues) {
    for(int i = 0; i < QUEUESIZE; i++) {
        if(emptyQ(queues[i]) == 1) continue;
        else if((maxQ != 0) && (queues[i]->boothNum == 0)) {
            queues[i]->boothNum = booth;
            maxQ--;
        }
    }   
}
void checkoutBooth(int limit, q** queues) {
    //sort among all queues in booth by arrival time
    customerInfo* tmpCust = NULL;
    int count, index, time;

    while(limit > 0) {
        count = 0;
        for(int i = 0; i < QUEUESIZE; i ++) {
            if(emptyQ(queues[i]) == 1) continue;
            for(int j = 0; j < QUEUESIZE; j++) {
                if(emptyQ(queues[j]) == 1) continue;
                if(peek(queues[i])->arrivalTime <= peek(queues[j])->arrivalTime) count++;
            }
            if(count == limit) {
                index = i;
                limit--;
                break;
            }
        }

        tmpCust = dequeue(queues[index]);

        time = checkoutTime(tmpCust);
        printf("%s from line %d checks out at time %d\n", tmpCust->name, (tmpCust->lineNum + 1), time);
    }
}
customerInfo* dequeue(q* queue) {
    customerNode* tmpNode;
    customerInfo* tmpCust; 

    tmpCust = peek(queue);
    tmpNode = queue->front;
    queue->front = queue->front->nextNode;

    if(queue->front == NULL) {
        queue->back == NULL;
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

