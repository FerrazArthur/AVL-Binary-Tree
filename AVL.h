/*
Autores: Arthur Ferraz, Lorenzo Alves de Souza
*/
#include <stdlib.h>
#include <stdio.h>
typedef struct node
/*
this struct is the core of this AVL binary tree. It contains:
info: The Client library must treat this as a Generic type pointer. As so, this library expects it to cast this pointer to whatever type it intends to work;
balance: Represents the diference between the left side subtree height and the right subtree height;
key: Holds the weight of each node in the tree, it is the primary search argument;
leftAVL: Holds the pointer to the Node that has a key lesser than the current or NULL;
rightAVL: Holds the pointer to the Node that has a key bigger than the current or NULL;
*/
{ 
    void* info;
    int balance;
    struct node *leftAVL;
    struct node *rightAVL;
}Node;

void *getInfo(Node* node);
//return pointer to info member

void setInfo(Node* node, void* newInfo);
//point node->info to newInfo

Node* getLeft(Node* node);
//returns the pointer leftAVL

Node* getRight(Node* node);
//returns the pointer rightAVL

int getBalance(Node* node);
//return content of balance

void setLeft(Node* node, Node* newLeftAVL);
//assing newLeftAVL pointer to Left

void setRight(Node* node, Node* newRightAVL);
//assing newRightAVL pointer to Right

void setBalance(Node* node, int newBalance);
//assign newBalance value to balance

int calculateBalance(Node* node);
//algorithm to calculate node balance

void swapContent(Node* node1, Node* node2);
//swap Info between both;

//***********************************************************************************************Sector with codes user must define manually
void printKey(Node* node);
//The Client library must implement this algorithm, once it need to know the type of key;
//this algorithm must print key content

void *getKey(Node* node);
//The Client library must implement this algorithm, once it need to know the type of key;
//return content of key, must be implemented by 

int compareKey(void* key1, void* key2);
/*
The Client library must implement this algorithm, once it need to know the size of info, in bytes;
this must return 0 if key1 is equal to key,
return 1 if key1 is bigger than key2
return -1 if key2 is bigger than key1
*/
void destroyInfo(void* info);
/*
The Client library must implement this algorithm in order to properly free all allocated memory during removal of a Node
*/

//***********************************************************************************************End

Node* createNodeAVLTree(void* info);
/*
This algorithm alocates memory and return a pointer to this adress or return NULL;
*/

void destroyNodeAVLTree(Node* node);
/*
This algorithm releases the memory that is allocatted to this node and his members;
*/

void destroyAVLTree(Node* node);
/*
this algorithm reaches each node in the AVL and calls a self -destructive method with a call to destroyAVLTreeNode(this) on each one of them.
*/

Node* searchKeyAVLTree(Node* head, void* key);
/*
This algorithm receive the higthest node of the AVLTree, also know as its head, and recursively goes down the branches looking for key;
If key if find, the pointer to the current Node is returned;
Else, return NULL;
*/

Node* searchSmallestKeyAVLTree(Node* node);
/*
this algorithm return the smallest element of AVL node
*/

Node* searchBiggestKeyAVLTree(Node* node);
/*
this algorithm return the biggest element of AVL node
*/

int heightAVLTree(Node* head);
/*
This algorithm calculates and return the maximum number of branches that takes to get to a leave; 
*/

void printBalanceAVLTree(Node* head);
/*
recursivelly print the key's balance in crescent order
*/

void printAVLTree(Node* head, int height);
/*
height must receive zero when this function is called;
this algorithm prints the tree rotated to left, where the first thing to be printed is the biggest element and the last thing is the smallest
*/

void LLRotatation(Node** head);
/*
father: axis of rotation;
son: Sub AVL Tree from the left of father;
The father has balace 2 and it's son has balace 1, so we point father's leftAVL to son's rightAVL and son's rightSon to father. them we point *head to son.
and both father and son's balance become 0;
*/
void LRRotation(Node** head);
/*
father: axis of rotation;
son: Sub AVL Tree from left of father;
grandSon: Sub AVL Tree from right of son;
The father has balace 2 and it's son has balance -1 so we point grandSon's leftAVL by son's rightAVL, grandSon's rightAVL by father's leftAVL, father is pointed by grandSon's rightAVL and son is pointed by grandSon's leftAVL and them point *head to grandSon;
if grandSon's previous balance was zero, both father and son's balance become zero;
if grandSon's previous balance was -1, father balance become 1 and son's balance become 0;
if grandSon's previous balance was 1, father balance become 0 and son's balance become -1;
grandSon's balance become zero;
*/
void RRRotation(Node** head);
/*
father: axis of rotation;
son: Sub AVL Tree from the right of father;
The father has balance -2 and son has balace -1, so we point son's leftAVL by father's rightAVL and father by son's leftAVL. them we point *head to son.
Both father and son's balance become zero;
*/
void RLRotation(Node** head);
/*
father: axis of rotation;
son: sub AVL Tree from the right of father;
grandSon: sub AVL Tree from the left of son;
the father has balance -2 and son has balace 1, so we point grandSon leftAVL by father's rightAVL ,grandSon rightAVL by son's leftAVL, we point to father by grandSon leftAVL and to son by grandSon rightAVL and point *head to grandSon;
if grandSon's previous balance was zero, both father and son's balace become zero;
if grandSon's previous balance was -1, father balance become 1 and son's balance become 0;
if grandSon's previous balance was 1, father balance become zero and son's balance become -1;
grandSon's balance become zero;
*/

void printKeysAVLTree(Node* head);
/*
print all keys alongside their balances
*/
int insertNodeAVLTree(Node** head, Node* node);
/*
head: pointer to pointer to the beginning of AVL
node: the node that is meant to be added to this AVL Tree, if node key isnt already in the AVL Tree
This algorithm recursivelly tries to insert node in the correct position relative to the whole AVL Tree. If it suceeds, return 1, else return 0
The AVL property is always maintened;
It returns 1 if sucessfully inserted node in head AVL BST, or return 0 if it failed(AVL BST already has the key of node)
*/

int removeNodeAVLTree(Node** head, void* key);
/*
this algorithm searches the AVL Tree head until finds key, then remove it and return 1 or return 0 if it doesnt find it
the AVL property of the whole AVL Tree is maintain in the process
*/
