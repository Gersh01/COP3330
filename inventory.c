//Alexander Gershfeld
//Program Assignment 6 - Theater Inventory
//COP3502
//Arup Guha
//December 3, 2023

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXLEN 19
#define TABLESIZE 300007

typedef struct item {
    char name[MAXLEN+1];
    int quantity;
    int saleprice;
} item;

typedef struct node {
    item* iPtr;
    struct node* next;
} node;

typedef struct hashtable {
    node** lists;
    int size;
} hashtable;

//man of the hour
int hashfunc(char* word, int size);

//initialize table
hashtable* initTable();

//buy item and its helper functions
node* findNode(node* head, char* name);
node* insertFront(node* head, char* name, int quantity, int price);
node* buyItem(node* head, char* name, int quantity, int price);

//rest of the commands
void sellItem(node* head, char* name, int quantity);
void changePrice(node* head, char* name, int newPrice);

//the lists
void freeTable(node* head);

//Global variables
int complexity = 0;
int total = 100000;

int main() {
    int numCommands;
    char tmpName[MAXLEN + 1];
    char command[MAXLEN + 1];
    int tmpQuantity, tmpPrice, tmpNewPrice, index;
    hashtable* inventory = initTable();

    scanf("%d", &numCommands);
    while(numCommands != 0) {
        scanf("%s", command);

        //commands
        if(strcmp(command, "buy") == 0) { //buy functionality
            scanf("%s %d %d", tmpName, &tmpQuantity, &tmpPrice);

            //calculate which list to add | calculate where the item is in the list
            index = hashfunc(tmpName, TABLESIZE);

            //change the head if necessary
            inventory->lists[index] = buyItem(inventory->lists[index], tmpName, tmpQuantity, tmpPrice);
        }
        else if(strcmp(command, "sell") == 0) { //sell
            scanf("%s %d", tmpName, &tmpQuantity);

            index = hashfunc(tmpName, TABLESIZE);
            sellItem(inventory->lists[index], tmpName, tmpQuantity);
        }
        else { //change price
            scanf("%s %d", tmpName, &tmpNewPrice);

            index = hashfunc(tmpName, TABLESIZE);
            changePrice(inventory->lists[index], tmpName, tmpNewPrice);
        }

        numCommands--;
    }
    printf("%d\n%d\n", total, complexity); //total then complexity
    
    for(int i = 0; i < inventory->size; i++) { //free each list
        if(inventory->lists[i] != NULL) freeTable(inventory->lists[i]);
    }
    free(inventory->lists);
    free(inventory);

    return 0;
}
int hashfunc(char* word, int size) {
    int len = strlen(word);
    int res = 0;

    for(int i = 0; i < len; i++)
        res = (1151*res + (word[i] - 'a')) % size;
    
    return res;
}
hashtable* initTable() {
    hashtable* tmp = (hashtable*)calloc(TABLESIZE, sizeof(hashtable));
    tmp->lists = (node**)calloc(TABLESIZE, sizeof(node*));
    tmp->size = TABLESIZE;

    return tmp;
}
node* findNode(node* head, char* name) {
    complexity++; //every time a recursive call is made, add to the complexity
    if(head == NULL) return NULL;
    else if(strcmp(head->iPtr->name, name) == 0) return head;
    else return findNode(head->next, name);
}
node* insertFront(node* head, char* name, int quantity, int price) {
    node* tmp = (node*)malloc(sizeof(node));
    tmp->iPtr = (item*)malloc(sizeof(item));

    //insert to front
    tmp->next = head;

    strcpy(tmp->iPtr->name, name);
    tmp->iPtr->quantity = quantity;
    tmp->iPtr->saleprice = 0;

    //update and print the newly added node
    total -= price;
    printf("%s %d %d\n", name, quantity, total);

    return tmp;
}
//seach if the item is in the list already, if it is, update the quantity and the total price
//if it is not in the list insert to front 
node* buyItem(node* head, char* name, int quantity, int price) {
    node* tmp = findNode(head, name); 
    
    if(tmp == NULL) { //item is not in list
        return insertFront(head, name, quantity, price);
    }    
    else { //item is in list, now update it and print
        total -= price;
        tmp->iPtr->quantity += quantity;

        printf("%s %d %d\n", name, tmp->iPtr->quantity, total);
        return head;
    }
}
//runs under the assumption that the item being sold exists in the table
void sellItem(node* head, char* name, int quantity) {
    int saleTotal, newQuantity;

    //every time this recursively calls, add to the complexity
    complexity++;
    if(strcmp(head->iPtr->name, name) == 0) { //found it
        if(head->iPtr->quantity != 0) { //you need to buy more of the item to sell it
            newQuantity = head->iPtr->quantity - quantity;
            if(newQuantity < 0) { //if the amount trying to sell is greater than on-hand
                saleTotal = head->iPtr->saleprice * head->iPtr->quantity;
                head->iPtr->quantity = 0;
            }
            else { //regular case
                saleTotal = head->iPtr->saleprice * quantity;
                head->iPtr->quantity = newQuantity;
            }
            total += saleTotal;
        } 
        printf("%s %d %d\n", name, head->iPtr->quantity, total); //print regardless of what happens
    } else sellItem(head->next, name, quantity); 
    
}
void changePrice(node* head, char* name, int newPrice) {
    complexity++; //every time its called add

    if(strcmp(head->iPtr->name, name) == 0)
        head->iPtr->saleprice = newPrice;
    else changePrice(head->next, name, newPrice);
}
void freeTable(node* head) {
    if(head->next != NULL) {
        freeTable(head->next);
    }

    free(head->iPtr);
    free(head);
}
