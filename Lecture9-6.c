#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node {
    int data;
    struct node* next;
} node;

//linked list 1. add, 2. delete, 3. search
//should be run in O(n) time where n = # of items
node* makenode(int val);
node* insertfront(node* list, int val);

int main() {
//for adding:
//cur tells us index
//copy info into this index then cur++
//if full realloc maxsize * 2


//for deleting:
//1. find item to delete
//2. free item
//3. reassign pointer to last item
//4. cur--

    return 0;
}
//if you change the address of the next pointer to an already made list, the new node will go in front
node* makenode(int val) {
    node* tmp = malloc(sizeof(node));
    tmp->data = val;
    tmp->next = NULL;
    return tmp;
}
node* insertfront(node* list, int val) {
    node* newn = makenode(val);
    newn->next = list;
    return newn;
}
void freelist(node* list) {
    if (list == NULL) return;

    node* ahead = list->next;

    while(ahead != NULL) {
        //free the head
        //now point to ahead
        //ahead now points to the next one after ahead
        //repeat
        free(list);
        list = ahead;
        ahead = ahead->next;
    }
    free(list);
}