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
} q;

//Adds the newly made customer into a linked list
customerNode* createNode(customerInfo* newCustomer);
//Inserts new node to the front of the list
customerNode* insertToFront(customerNode* newNode, customerInfo* newCustomer);
//Creates a new customer, populating the struct with input values
customerInfo* createCustomer(char* newName, int newTickets, int newArrTime);
//Calculates the queue number for each customer
int queueNum(q** queues, customerInfo* newCustomer);
//Creates the memory for the queue
q* createQ(int lineNo);

int main() {
    
    customerInfo* tmpCustomer = NULL;
    customerNode* customerList = NULL;
    q** allQueues = (q**)calloc(QUEUESIZE, sizeof(q*));

    char tmpName[MAXCHAR];
    int custAmt, booths;
    int tmpTickets, tmpLineNum, tmpArrTime;

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

        //Calculates the queue number based on the first character of their name
        tmpCustomer->lineNum = queueNum(allQueues, tmpCustomer);

        
        customerList = insertToFront(customerList, tmpCustomer);

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

    return tmp;
}
customerNode* createNode(customerInfo* newCustomer) {
    customerNode* tmp = (customerNode*)malloc(sizeof(customerNode));

    tmp->customer = newCustomer; 
    tmp->nextNode = NULL;

    return tmp;
}
customerNode* insertToFront(customerNode* newNode, customerInfo* newCustomer) {
    customerNode* tmpNode = createNode(newCustomer);
    tmpNode->nextNode = newNode;

    return tmpNode;
}
int queueNum(q** queues, customerInfo* newCustomer) {
    //calculate the assigned queue
    int ret = 0;
    int position = (newCustomer->name[0] - 'A') % 13; 
    if(queues == NULL)
        return ret;
    else if(position != 0)
        ret = position;
    
    //rule for when mod is zero -- possibly move into its own function
    else if(position == 0) {
        for(int i = 0; i < QUEUESIZE; i++) 
            if(queues[i]->size != 0)
                for(int j = 1; j < QUEUESIZE; j++) 
                    if(queues[i]->size > queues[j]->size) ret = j;
    }

    return ret;
}
q* createQ(int lineNo) {

}
