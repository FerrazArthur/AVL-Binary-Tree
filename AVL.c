/*
Autores: Arthur Ferraz, Lorenzo Alves de Souza
*/
#include "AVL.h"

void *getInfo(Node* node)
{
    if(node != NULL)
        return node->info;
    return NULL;
}

void setInfo(Node* node, void* newInfo)
{
    if(node != NULL)
        node->info = newInfo;
}

Node* getLeft(Node* node)
{
    if(node != NULL)
        return node->leftAVL;
    return NULL;
}

Node* getRight(Node* node)
{
    if(node != NULL)
        return node->rightAVL;
    return NULL;
}

int getBalance(Node* node)
{
    if(node != NULL)
        return node->balance;
    return 0;
}

void setLeft(Node* node, Node* newLeftAVL)
{
    if(node != NULL)
        node->leftAVL = newLeftAVL;
}

void setRight(Node* node, Node* newRightAVL)
{
    if(node != NULL)
        node->rightAVL = newRightAVL;
}

void setBalance(Node* node, int newBalance)
{
    if(node != NULL)
        node->balance = newBalance;
}

void swapContent(Node* node1, Node* node2)
{
    if(node1 == NULL || node2 == NULL)
        return;
    Node aux;//copy content of node2 to aux
    setInfo(&aux, getInfo(node2));
    //copy content of node1 to node 2
    setInfo(node2, getInfo(node1));
    //copy content of aux to node 1
    setInfo(node1, getInfo(&aux));
}

Node* createNodeAVLTree(void* info)
{
    //Allocation of memory for Node
    Node* ptr = malloc(sizeof(Node));
    if(ptr != NULL)
    {//if it has been sucessfull:
        setInfo(ptr, info);
        setBalance(ptr, 0);
        setLeft(ptr, NULL);//needed to make we it knows it's limits
        setRight(ptr, NULL);
    }
    return ptr;
}

int calculateBalance(Node* node)
{
    int balance = 0;
    if(node != NULL)
    {
        balance = heightAVLTree(getLeft(node)) - heightAVLTree(getRight(node));
    }
    return balance;
}

void destroyNodeAVLTree(Node* node)
{
    if(node != NULL)
    {
        destroyInfo(node->info);
        free(node);
    }
}

void destroyAVLTree(Node* node)
{
    if(node != NULL)
    {
        destroyAVLTree(getLeft(node));
        destroyAVLTree(getRight(node));
        destroyNodeAVLTree(node);
    }
}

Node* searchKeyAVLTree(Node* head, void* key)
{
    if (head != NULL)
    {
            printKey(head);
            if(compareKey(getKey(head), key) == 1)
                return searchKeyAVLTree(getLeft(head), key);
            else if (compareKey(getKey(head), key) == -1)
                return searchKeyAVLTree(getRight(head), key);
        }
        return head;//return either NULL of the Node that has getKey(head) == key
    }

Node* searchSmallestKeyAVLTree(Node* node)
{
    if(node != NULL)
    {
        if(getLeft(node) != NULL)//when it can't reach a valid leftSon, it means this node is the smallest
            searchSmallestKeyAVLTree(getLeft(node));
        return node;
    }
    return NULL;
}

Node* searchBiggestKeyAVLTree(Node* node)
{
    if(node != NULL)
    {
        if(getRight(node) != NULL)
            searchBiggestKeyAVLTree(getRight(node));
        return node;
    }
    return NULL;
}

int heightAVLTree(Node* head)
{
    int l = 0, r = 0;
    if(head == NULL)
       return 0;
    l = 1 + heightAVLTree(getLeft(head));
    r = 1 + heightAVLTree(getRight(head));
    if(l > r)//this ensures that only the biggest path is returned
        return l;
    else
        return r;
}

void LLRotation(Node** head)
/*
all rotations implementation logic are sintetized in AVL.h, go check it out
*/
{
    Node* father = *head;
    Node* son = getLeft(father);
    setLeft(father, getRight(son));
    setRight(son, father);
    setBalance(son, 0);
    setBalance(father, 0);
    *head = son;
}

void LRRotation(Node** head)
/*
all rotations implementation logic are sintetized in AVL.h, go check it out
*/
{
    Node* father = *head;
    Node* son = getLeft(father);
    Node* grandSon = getRight(son);
    setLeft(father, getRight(grandSon));
    setRight(son, getLeft(grandSon));
    setLeft(grandSon, son);
    setRight(grandSon, father);
    switch(getBalance(grandSon))
    {
        case -1:
            setBalance(son, 1);
            setBalance(father, 0);
            break;
        case 0:
            setBalance(son, 0);
            setBalance(father, 0);
            break;
        case 1:
            setBalance(son, 0);
            setBalance(father, -1);
            break;
    }
    setBalance(grandSon, 0);
    *head = grandSon;
}

void RRRotation(Node** head)
/*
all rotations implementation logic are sintetized in AVL.h, go check it out
*/
{
    Node* father = *head;
    Node* son = getRight(father);
    setRight(father, getLeft(son));
    setLeft(son, father);
    setBalance(son, 0);
    setBalance(father, 0);
    *head = son;
}

void RLRotation(Node** head)
/*
all rotations implementation logic are sintetized in AVL.h, go check it out
*/
{
    Node* father = *head;
    Node* son = getRight(father);
    Node* grandSon = getLeft(son);
    setRight(father, getLeft(grandSon));
    setLeft(son, getRight(grandSon));
    setLeft(grandSon, father);
    setRight(grandSon, son);
    switch(getBalance(grandSon))
    {
        case -1:
            setBalance(son, 1);
            setBalance(father, 0);
            break;
        case 0:
            setBalance(son, 0);
            setBalance(father, 0);
            break;
        case 1:
            setBalance(son, 0);
            setBalance(father, -1);
            break;
    }
    setBalance(grandSon, 0);
    *head = grandSon;
}

void printBalanceAVLTree(Node* head)
{
    if(head != NULL)
    {
        printBalanceAVLTree(getLeft(head));//first goes down to the smallest element, print then goes to the biggest's
        printKey(head);
        printf("balance: %d\n",getBalance(head));
        printBalanceAVLTree(getRight(head)); 
    }
}

void printAVLTree(Node* head, int height)
{
    if(head != NULL)
    {
        printAVLTree(getRight(head), height+1);
        for(int i = 0; i < height; i++)
            printf("    ");//print 4 spaces to each height level the current node has
        printKey(head);
        printAVLTree(getLeft(head), height+1);
    }
}

int insertNodeAVLTree(Node** head, Node* node)
/*
it returns int so the previous call can know if it has possibly changed height
*/
{
    static int grownUp = 0;//holds 0 by default, but it's value is changed to 1 if head's height has increased with the insertion
    if ((*head) == NULL)
    //when the NULL is reached, it means that node is the right position to insert node
    {
        *head = node;
        grownUp = 1;//tells the algorithm it has grownup
        return 1;//tells it has inserted
    }
    if (compareKey(getKey(*head), getKey(node)) == 0)//we dont want repetitive keys 
        return 0;//tells it has not inserted
    else if (compareKey(getKey(*head), getKey(node)) == 1)//compares if actual node key is bigger than the new key that is meant to be inserted
    {
        if(insertNodeAVLTree(&(*head)->leftAVL, node))//recursivelly searches the NULL pointer, where it should insert node; it can receive 1(sucess insertion) or 0
        {
            if(grownUp)//node is meant to maintain AVL property, where balance should never be bigger than 2 or lesser than -2
            {
                switch(getBalance(*head))
                {
                    case 1:
                        if(getBalance(getLeft(*head)) == 1)//get a glimpse of grandSon of *head, it's balance will tell the kind of rotation is needed
                            LLRotation(head);//if grandSon is left heavy
                        else
                            LRRotation(head);//if it's right heavy
                        grownUp = 0;//because we balanced node level of the AVL, the upper level's balance doesnt need to be updated
                        break;
                    case 0://1 or -1 balance are tolerable in AVl BST
                        setBalance(*head, 1);
                        break;
                    case -1://the balance is restored
                        setBalance(*head, 0);
                        grownUp = 0;
                        break;
                }
            }
            return 1;//node goes up into the first call and get's returned to the user, telling him that the insertion has sucessfull.
        }
        return 0;//node goes up into the first call and get's returned to the user, telling him that the insertion has not done.
    }
    else
    {//same logic as above, only reflected to the right
        if(insertNodeAVLTree(&(*head)->rightAVL, node))
        {
            if(grownUp)
            {
                switch(getBalance(*head))
                {
                    case -1:
                       if(getBalance(getRight(*head)) == -1) 
                           RRRotation(head);
                       else
                           RLRotation(head);
                       grownUp = 0;
                       break;
                   case 0:
                       setBalance(*head,-1);
                       break;
                   case 1:
                       setBalance(*head, 0);
                       grownUp = 0;
                       break;
                }
            }
            return 1;
        }
        return 0;
    }
}

int removeNodeAVLTree(Node** head, void* key)
/*
it return int so the previous call can know it it's height has changed or not, with the possibly deletion of a node
*/
{
    int res;//to prevent control of reaching end of non-void function
    Node *temp = NULL;
    if(*head == NULL)
        return 0;
    if(compareKey(getKey(*head), key) == 0)//has find the node to delete
    {
        if(getLeft(*head) == NULL || getRight(*head) == NULL)
        {//when we have only one subtree, proceed like this 
            temp = *head;
            if(getLeft(*head) == NULL)
                *head = getRight(*head);
            else if(getRight(*head) == NULL)
                *head = getLeft(*head);
            destroyNodeAVLTree(temp);
        }
        else
        {
            if(getBalance(*head) == 1)//if leftAVL is bigger than rightAVL, we search the biggest element smaller than current and swap'em
            {
                temp = searchBiggestKeyAVLTree(getLeft(*head));
                swapContent(*head, temp);
                removeNodeAVLTree(&(*head)->leftAVL, getKey(temp));
            }
            else//if is zero os ir -1, we search the smallest element bigger than current and swap'em too
            {
                temp = searchSmallestKeyAVLTree(getRight(*head));
                swapContent(*head, temp);
                removeNodeAVLTree(&(*head)->rightAVL, getKey(temp));
            }
        }
        setBalance(*head, calculateBalance(*head));//after deletion, this line is executted to ensure balance is right
        return 1;
    }
    else if(compareKey(getKey(*head), key) == 1)
    {
        if((res = removeNodeAVLTree(&(*head)->leftAVL, key)) == 1)//if remove happens, we must ensure this node balance is still between 1 and -1
        {
            setBalance(*head, calculateBalance(*head));
            if(getBalance(*head) == -2)//because we removing from the left, the balance is going towards -2
            {
                if(getBalance(getRight(*head)) == -1)
                    RRRotation(head);
                else
                    RLRotation(head);
            }
        }
    }
    else
    {
        if((res = removeNodeAVLTree(&(*head)->rightAVL, key)) == 1)
        {
            setBalance(*head, calculateBalance(*head));
            if(getBalance(*head) == 2)//because we removing from right, the balance is goind towards 2
            {
                if(getBalance(getLeft(*head)) == 1)
                    LLRotation(head);
                else
                    LRRotation(head);
            }
        }
    }
    return res;
}
