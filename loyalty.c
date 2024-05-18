//Program Assignment 5 - Theater Loyalty Program
//Alexander Gershfeld
//Arup Guha
//COP3502
//11-14-2023

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXLEN 19

//prints out the outcome - set to 0 to test run time; if you dont want a wall of text for large input samples
#define PRINT 1

typedef struct customer {
    char name[MAXLEN+1];
    int points;
} customer;

typedef struct treenode {
    customer* cPtr;
    struct treenode* left;
    struct treenode* right;
    int size;
} treenode;

//helper functions
//---------------------------------------------
    //functions for comparing nodes in tree
    char* front(treenode* node);
    int compareBst(treenode* root, char name[]); //compare for bst
    treenode* findNode(treenode* root, char name[]);

    //used to calculate the depth of a node in a tree after searching for it
    int calcDepth(treenode* root, char name[], int depth);

//binary tree commands
//---------------------------------------------
    //functions for adding customer/ adding points and its helpers
    treenode* createNode(char name[], int points);
    treenode* addToTree(treenode* root, char name[], int points);
    treenode* addValueInTree(treenode* root, char name[], int points);

    //subtracting points from node
    treenode* subtractPoints(treenode* root, char name[], int subPoints);
    
    //deleting the node and its helpers
    int paternityTest(treenode* root);
    treenode* returnCust(treenode* root);
    treenode* delete(treenode* root, char name[]);

    //counting the amount of nodes before it alphabetically
    int count_small(treenode* root, char name[], int count);

    //free the nodes in the tree from bottom up
    void freeTree(treenode* root);

//host the menu for the commands
//---------------------------------------------
    int control(char option[]);
    treenode* commandCenter(treenode* root, char option[]);

//Quick sort functions && Merge sort functions
//---------------------------------------------
    //transfer customers from binary tree to array
    int populateArr(customer** arr, treenode* root, int index);

    //checks to see if the array at every recursive call of quickSort is in increasing order
    int isSorted(customer** arr, int low, int high);
    int compareName(customer* arr1, customer* arr2); //compare for sorts

    //Quick sort and its helper functions
    void swap(customer* arr1, customer* arr2);
    int partition(customer** arr, int low, int high);
    void quickSort(customer** arr, int low, int high);

    //Merge sort and helpers | sorts the same points in alphabetical order
    void merge(customer** arr, int low, int mid, int high);
    void sortSamePoints(customer** arr, int low, int high);

int main() {
//Binary tree manipulation portion
//---------------------------------------------
    treenode* customerTree = NULL;
    int numCommands, ret;
    scanf("%d", &numCommands);

    while(numCommands != 0) {
        char command[16];
        scanf("%s", command);

        customerTree = commandCenter(customerTree, command);
        numCommands--;
    }

//Quick sort the tree by least points to greatest
//---------------------------------------------
if(customerTree != NULL) {
    customer** treeArr = (customer**)calloc(customerTree->size, sizeof(customer*));
    populateArr(treeArr, customerTree, 0); //bst to array
    quickSort(treeArr, 0, customerTree->size - 1); //sort

    int j, k;

    for(int i = customerTree->size - 1; i >= 0; i--) {
        //marks the low and high of a series of same point runs in array
        j = i;
        while(j > 0 && treeArr[j]->points == treeArr[j-1]->points) j--;

        //merge sorts every consecutive entry that is equal in points, alphabetically
        if(i != j) sortSamePoints(treeArr, j, i);

        //prints out the customers in the array in decreasing order
        if(PRINT) printf("%s %d\n", treeArr[i]->name, treeArr[i]->points);
    }

    free(treeArr);
}
//Fin.
//---------------------------------------------
    //free binary tree
    if(customerTree != NULL) freeTree(customerTree);
    return 0;
}
treenode* findNode(treenode* root, char name[]) {
    if(root == NULL) return NULL;
    else {
        if(compareBst(root, name) == 0) return root;
        else if(compareBst(root, name) > 0) return findNode(root->left, name);
        else if(compareBst(root, name) < 0) return findNode(root->right, name);
    }
}
int compareBst(treenode* root, char name[]) {
    return strcmp(front(root), name);
}
char* front(treenode* node) {
    if(node != NULL) {
        return node->cPtr->name;
    }
    return NULL;
}
int calcDepth(treenode* root, char name[], int depth) {
    if(compareBst(root, name) == 0) return depth;
    else if(compareBst(root, name) > 0) return calcDepth(root->left, name, depth+1);
    else return calcDepth(root->right, name, depth+1);
}

treenode* createNode(char name[], int points) {
    treenode* tmp = (treenode*)malloc(sizeof(treenode));
    tmp->cPtr = (customer*)malloc(sizeof(customer));
    strcpy(tmp->cPtr->name, name);

    tmp->cPtr->points = points;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->size = 1;

    return tmp;
}
treenode* addToTree(treenode* root, char name[], int points) {
    if(root == NULL) {
        if(PRINT)
            printf("%s %d\n", name, points);
        return createNode(name, points);
    }
    else if(compareBst(root, name) > 0) { //add one to size for every traversal when adding to tree
        root->size++;
        root->left = addToTree(root->left, name, points);
    }
    else { 
        root->size++;
        root->right = addToTree(root->right, name, points);
    }

    return root;
}
treenode* addValueInTree(treenode* root, char name[], int addPoints) {
    if(compareBst(root, name) == 0) { //if its found, add the points
        root->cPtr->points += addPoints;
        if(PRINT) printf("%s %d\n", name, root->cPtr->points);

        return root;
    }
    else if(compareBst(root, name) > 0) root->left = addValueInTree(root->left, name, addPoints);
    else root->right = addValueInTree(root->right, name, addPoints);

    return root;
}
treenode* subtractPoints(treenode* root, char name[], int subPoints) {
    if(compareBst(root, name) == 0) { //node is found, subtract the points
        root->cPtr->points -= subPoints;

        //if the subtracted total is less than zero, make the total 0
        if(root->cPtr->points < 0)
            root->cPtr->points = 0;

        if(PRINT) printf("%s %d\n", name, root->cPtr->points);
        return root;
    }
    else if(compareBst(root, name) > 0) root->left = subtractPoints(root->left, name, subPoints);
    else root->right = subtractPoints(root->right, name, subPoints);

    return root;
}
int paternityTest(treenode* root) {
    //has two children
    if(root->left != NULL && root->right != NULL) return 3;

    //has a left child
    else if(root->left != NULL && root->right == NULL) return 2;

    //has a right child
    else if(root->left == NULL && root->right != NULL) return 1;

    //has no children
    else return 0;
} 
treenode* returnCust(treenode* root) {
    if(root->right == NULL) return root;
    else return returnCust(root->right);
}
treenode* delete(treenode* root, char name[]) {
    treenode* tmp = NULL; //for returning purposes
    char tmpName[MAXLEN+1];
    int tmpPoints;

    //found the node to delete
    if(compareBst(root, name) == 0) {
        switch(paternityTest(root)) {
            case 3: //two children
                //store the right-most node from the left subtree
                tmp = returnCust(root->left);
                strcpy(tmpName, tmp->cPtr->name);
                tmpPoints = tmp->cPtr->points;

                //delete that node
                root->left = delete(root->left, tmpName);

                //make the current node the tmp node
                root->cPtr->points = tmpPoints;
                strcpy(root->cPtr->name, tmpName);
                root->size--;

                return root;
            case 2: //left child only
                tmp = root->left;
                free(root->cPtr);
                free(root);
                return tmp;
            case 1: //right child only
                tmp = root->right;
                free(root->cPtr);
                free(root);
                return tmp;
            case 0: //no children :(
                free(root->cPtr);
                free(root);
                return NULL;
            default: //three children? Scary, no thanks.
                return root;
        }
    }
    //traverse to left node
    else if(compareBst(root, name) > 0) {
        root->size--;
        root->left = delete(root->left, name);
    }
        
    //traverse to right node
    else {
        root->size--;
        root->right = delete(root->right, name);
    }
    return root;
}
int count_small(treenode* root, char name[], int count) {
    if(root == NULL) return count;
    if(compareBst(root, name) == 0) {
        if(root->left != NULL)
            count += root->left->size;
        
        return count;
    }
    //if the node is to the left of the root then do nothing
    else if(compareBst(root, name) > 0) {
        return count_small(root->left, name, count);
    }
    //if the node is to the right, add everything that is to the left of this current node plus itself
    else {
        if(root->left != NULL)
            count += root->left->size;
        return count_small(root->right, name, count+1);
    }
}
void freeTree(treenode* root) {
    if(root->left != NULL) freeTree(root->left);
    if(root->right != NULL) freeTree(root->right);
    
    free(root->cPtr);
    free(root);
}

int control(char option[]) {
    //converts string commands to switch compatitble options
    //-----------------------------------------------------------
    if(strcmp(option, "add") == 0) return 1;
    else if(strcmp(option, "sub") == 0) return 2;
    else if(strcmp(option, "del") == 0) return 3;
    else if(strcmp(option, "search") == 0) return 4;
    else if(strcmp(option, "count_smaller") == 0) return 5;

    return 0;
}
treenode* commandCenter(treenode* root, char option[]) {
    char tmpName[MAXLEN+1];
    int tmpPoints, subPoints;
    treenode* tmpNode;

    //keeps track of the commands
    switch(control(option)) {
        case 1: 
            scanf("%s %d", tmpName, &tmpPoints);

            //return the new root after adding a node, or adding points
            if(findNode(root, tmpName) != NULL) return addValueInTree(root, tmpName, tmpPoints);
            else return addToTree(root, tmpName, tmpPoints);
        case 2:
            scanf("%s %d", tmpName, &tmpPoints);

            //if the node is found subtract the points, else do nothing, return the new root
            if(findNode(root, tmpName) != NULL) return subtractPoints(root, tmpName, tmpPoints);
            else {
                if(PRINT) printf("%s not found\n", tmpName);
            }
            break;
        case 3:
            scanf("%s", tmpName);

            //find node, print, then delete, else its not in the tree
            if(findNode(root, tmpName) != NULL) {
                if(PRINT) printf("%s deleted\n", tmpName);
                return delete(root, tmpName);
            }
            else {
                if(PRINT) printf("%s not found\n", tmpName);
            }
            break;
        case 4:
            scanf("%s", tmpName);

            //grab the node to display the points
            tmpNode = findNode(root, tmpName);

            //print the name, points, and its depth
            if(tmpNode != NULL) {
                if(PRINT) printf("%s %d %d\n", tmpName, tmpNode->cPtr->points, calcDepth(root, tmpName, 0));
            }
            else { 
                if(PRINT) printf("%s not found\n", tmpName);
            }
            break;
        case 5:
            scanf("%s", tmpName);
            if(PRINT) printf("%d\n", count_small(root, tmpName, 0));
            break;
        default:
            return root;
    }

    return root;
}

int populateArr(customer** arr, treenode* root, int index) {
    //base case
    if(root == NULL) return 1;

    //start of the call assign the root customer then increment
    arr[index++] = root->cPtr;

    //traverse while preserving the index
    if(root->left != NULL)
        index = populateArr(arr, root->left, index);

    if(root->right != NULL)
        index = populateArr(arr, root->right, index);

    return index;
}
int isSorted(customer** arr, int low, int high) {

    for(int i = low; i < high; i++) {
        if(arr[i]->points > arr[i+1]->points) return 0;
    }
        
    
    return 1;
}
int compareName(customer* arr1, customer* arr2) {
    if(arr1->points == arr2->points) {
        if(strcmp(arr1->name, arr2->name) > 0) return 1;
    }
    return 0;
}
void merge(customer** arr, int low, int mid, int high) {
    int ptr1, ptr2, index = 0;
    int len = high - low + 1; //size of the array to copy
    customer** tmp = (customer**)calloc(len, sizeof(customer*));

    //sets the pointers to split array into two
    ptr1 = low;
    ptr2 = mid;
    
    //loops while ptrs stay inbounds
    while((ptr1 < mid) || (ptr2 <= high)) {
        //sets the index to the value that is being pointed to by ptr1 | ptr1 < ptr2
        if(ptr2 > high || (ptr1 < mid && compareName(arr[ptr1], arr[ptr2]))) {
            tmp[index] = arr[ptr1];
            ptr1++;
            index++;
        }
        //sets the index ot the value that is being pointed to by ptr2 | ptr2 < ptr1
        else {
            tmp[index] = arr[ptr2];
            ptr2++;
            index++;
        }
    }

    //updates the original orray to the sorted tmp array
    for(int i = low; i <= high; i++) arr[i] = tmp[i - low];

    free(tmp);
}
void sortSamePoints(customer** arr, int low, int high) {
    //low and high are the bounds of the consecutive same point values
    int mid;
    
    if(low < high) {
        //midpoint of the array
        mid = (low+high)/2;

        //sort left
        sortSamePoints(arr, low, mid);
        //sort right
        sortSamePoints(arr, mid+1, high);

        //merge left and right
        merge(arr, low, mid+1, high);
    }
}
void swap(customer* arr1, customer* arr2) {
    //store the first node
    customer* tmp = (customer*)malloc(sizeof(customer));
    strcpy(tmp->name, arr1->name);
    tmp->points = arr1->points;

    //make 1 equal to 2
    *arr1 = *arr2;

    //make 2 equal to 1
    strcpy(arr2->name, tmp->name);
    arr2->points = tmp->points;

    free(tmp);
}
int partition(customer** arr, int low, int high) {
    //make the index equal to the first index of the array
    int pivet = low;
    
    //update the lower pointer to one after pivet
    low++;

    //keep on swapping low and high until their indices cross
    while(low <= high) {
        //increment the left until its greater than right, and if the value in low is greater than that of pivet
        while(low <= high && arr[low]->points <= arr[pivet]->points) low++;
        //decrement the right until its less than the left, and if the right value is greater than the pivet 
        while(high >= low && arr[high]->points > arr[pivet]->points) high--;

        //after the left and right are updated, if left is still left, and right is still right swap
        //customer at low and customer at high are swapped
        if(low < high)
            swap(arr[low], arr[high]);

    }

    //swap the new low with the pivet
    swap(arr[pivet], arr[high]);

    return high;
}
void quickSort(customer** arr, int low, int high) {
    //returns if arr is sorted increasing
    if(!isSorted(arr, low, high)) {
        //creates the partition and sorts the left and right side
        int part = partition(arr, low, high);
        quickSort(arr, low, part - 1);
        quickSort(arr, part + 1, high);

    }

    
}