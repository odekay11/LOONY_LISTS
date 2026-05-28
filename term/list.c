/*
 *File: list.c
 *Author: Owen DeKay
 *Introduction:
 *The purpose of this program is to implement a data structure that can efficiently support stack, queue, and indexing operations.
 *The program uses a doubly linked list with head and tail pointers to achieve fast stack and queue operations.
 *Each node contains an pointer array of NODE_SIZE.
 *The pointer array is fixed in size to maintain simplicty of add first operations.
 *
 */

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "list.h"
#define NODE_SIZE 64

//Node structure definition
typedef struct node{
    void **data; //pointer to array of void pointers of fixed size
    int count; //number of elements stored at a given node
    int first;//index of the first element in the circular queue
    int size;//how many slots are in a node
    struct node *next; //next node 
    struct node *prev;//previous node

}NODE;

//List structure definition
typedef struct list{
    int count; //total number of elements stored in the list 
    struct node *head;//first node 
    struct node *tail;//last node
}LIST;
/*CreateList
 *Purpose:
 *  Allocate space for the list and initialize first node.
 *Return:
 *  lp=list pointer
 *Big O:
 *  O(1)
 */
 LIST *createList(void){
    //allocate list struct
    LIST *lp=malloc(sizeof(LIST));
    assert(lp!=NULL);

    //allocate first node
    NODE *node=malloc(sizeof(NODE));
    assert(node!=NULL);

    node->data=malloc(sizeof(void *)*NODE_SIZE);
    assert(node->data!=NULL);
    node->size=NODE_SIZE;
    node->first=0;
    node->count=0;
    node->next=NULL;
    node->prev=NULL;

    lp->count=0;
    lp->head=node;
    lp->tail=node;

    return lp;

 }
/*destroyList;
 *Purpose:
 *  Free all data allocate the list and node structure.
 *Parameters:
 *  lp=list pointer
 *Big O:
 *  O(N)
 */
 void destroyList(LIST *lp){
    assert(lp!=NULL);
    NODE *current=lp->head;
    NODE *temp;
    while(current!=NULL){
        temp=current;
        current=current->next;
        //free data array
        free(temp->data);
        //free node
        free(temp);
    }
    //free list
    free(lp);
 }
/*numItems:
 * Purpose:
 *  Return the number of items in the list.
 * Parameters:
 *  lp=list pointer
 * Return:
 *  lp->count=number of items in the list.
 * Big O:
 *  O(1)
 */
 int numItems(LIST *lp){
    assert(lp!=NULL);
    return lp->count;

 }
/*addFirst:
 * Purpose:
 *  Add a value to the front of the list.
 *  If the first node is full it allocates a new node.
 * Parameter:
 *  lp=list pointer
 *  item= item to add to the list
 * Big O:
 *  O(1)
 */
 void addFirst(LIST *lp, void *item){
    assert(lp!=NULL);
    //alocate new node
    if(lp->head->count ==lp->head->size){
        NODE *newNode=malloc(sizeof(NODE));
        assert(newNode!=NULL);
        newNode->data=malloc(sizeof(void *)*NODE_SIZE);
        assert(newNode->data!=NULL);
        newNode->next=lp->head;
        newNode->prev=NULL;
        lp->head->prev=newNode;
        lp->head=newNode;
        newNode->size=NODE_SIZE;
        newNode->first=0;
        newNode->count=0;
    }
    //Update first to new value
    //-1 makes it so first moves slot before the current first
    lp->head->first=(lp->head->first-1 +lp->head->size)%lp->head->size;
    lp->head->data[lp->head->first]=item;
    lp->head->count++;
    lp->count++;

 }
/*addLast:
 * Purpose: 
 *  Add an item at the last slot in the last node in the list.
 *  If the node is full it allocates a new node.
 * Parameters:
 *  lp=list pointer.
 *  item=value to add to the list
 * Big O:
 *  O(1)
 */
 void addLast(LIST *lp, void *item){
    assert(lp!=NULL);
    //allocate new node if last node is full
    if(lp->tail->count == lp->tail->size){
        NODE *newNode=malloc(sizeof(NODE));
        assert(newNode!=NULL);
        newNode->data=malloc(sizeof(void *)*NODE_SIZE);
        assert(newNode->data!=NULL);
        newNode->size=NODE_SIZE;
        newNode->first=0;
        newNode->count=0;

        newNode->prev=lp->tail;
        newNode->next=NULL;
        lp->tail->next=newNode;
        lp->tail=newNode;
    }
    //Compute the last slot in the array
    lp->tail->data[(lp->tail->first+lp->tail->count)%lp->tail->size]=item;
    lp->tail->count++;
    lp->count++;
 }
/*removeFirst:
 * Purpose:
 *  Remove the value at the first slot in the first node from the list.
 *  Updates first value.
 *  If node is empty after removal it frees the node.
 * Parameters:
 *  lp=list pointer
 * Return:
 *  value=item removed from the list
 * Big O:
 *  O(1)
 *
 */
 void *removeFirst(LIST *lp){
    //Check for empty list
    assert(lp!=NULL && lp->count>0);
    //Get value
    void *value=lp->head->data[lp->head->first];
    //Move first to next slot 
    lp->head->first=(lp->head->first +1 )%lp->head->size;
    lp->head->count--;
    lp->count--;
    if(lp->head->count==0 && lp->head->next!=NULL){
        NODE *temp=lp->head;
        lp->head=temp->next;
        lp->head->prev=temp->prev;
        free(temp->data);
        free(temp);
        
    }
    return value;
 }
 /*removeLast:
 * Purpose:
 *  Remove the value at the last slot in the last node from the list.
 *  If node is empty after removal it frees the node.
 * Parameters:
 *  lp=list pointer
 * Return:
 *  value=item removed from the list
 * Big O:
 *  O(1)
 */
void *removeLast(LIST *lp){
    assert(lp!=NULL && lp->count>0);
    //Get last item
    int index=(lp->tail->first + lp->tail->count -1)%lp->tail->size;
    void *value=lp->tail->data[index];
    //decreament count
    lp->tail->count--;
    lp->count--;
    //check edge cases
    if(lp->tail->count==0 && lp->tail->prev!=NULL){
        NODE *temp=lp->tail;
        lp->tail=temp->prev;
        lp->tail->next=NULL;
        free(temp->data);
        free(temp);
    }
    return value;

 }
 /*getFirst:
  * Purpose:
  *  Return the value stored at the first slot in the first node.
  * Parameters:
  *  lp=list pointer
  * Return:
  *  lp->head->data[lp->head->first]=value stored in the first slot
  * Big O:
  *  O(1)
  */
void *getFirst(LIST *lp){
    assert(lp!=NULL);
    return lp->head->data[lp->head->first];

 }
/*getLast:
 * Purpose:
 *  Return the value stored at the last slot in the last node.
 * Parameters:
 *  lp=list pointer
 * Return:
 *  lp->tail->data[index]=value stored in the last slot
 * Big O:
 *  O(1)
 */
void *getLast(LIST *lp){
    assert(lp!=NULL);
    int index=(lp->tail->first + lp->tail->count -1)%lp->tail->size;
    return lp->tail->data[index];


 }
/*getItem:
 * Purpose:
 *  Return the value stored at a given index within the list.
 *  If the index is greater than the current count in the list, task it terminated.
 *  If the index is closer to the head it starts at the head.
 *  If the index is closer to the tial it starts searching at the tail.
 * Parameters:
 *  lp=list pointer
 *  index=index to return value stored at.
 * Return:
 *  temp->data[(temp->first+index)%temp->size]=value found at the index
 * Big O:
 *  O(log n)
 */
void *getItem(LIST *lp, int index){
    assert(lp!=NULL && index>=0 && lp->count>index);
    NODE *temp;
    //Closer to the head start at the head
    if(index<lp->count/2){
        temp=lp->head;
        while(index>= temp->count){
            index=index-temp->count;
            temp=temp->next;
        }
    }else{
        //Closer to the tail start at the tail
        temp=lp->tail;
        //reverse indexing
        int nodeStart=lp->count-temp->count;
        while(index<nodeStart){
            temp=temp->prev;
            nodeStart=nodeStart-temp->count;
        }
        index=index-nodeStart;
    }
    return temp->data[(temp->first+index)%temp->size];

 }
/*setItem:
 * Purpose:
 *  Replace an item at a given index within the list with a new value.
 *  If the index is less greater than the current count in the list, the task is terminates.
 *  If the index is closer to the head it starts at the head.
 *  If the index is closer to the tial it starts searching at the tail.
 * Parameters:
 *  lp=list pointer.
 *  index=index of value to replace.
 *  item=valeu to insert.
 * Big O:
 *  O(log n)
 */
void setItem(LIST *lp, int index, void *item){
    assert(lp!=NULL && index>=0 && index<lp->count);
    NODE *temp;
    //Closer to the head start at the head
    if(index<lp->count/2){
        temp=lp->head;
        while(index>= temp->count){
            index=index-temp->count;
            temp=temp->next;
        }
    }else{
        //Closer to the tail start at the tail
        temp=lp->tail;
        int nodeStart=lp->count-temp->count;
        while(index<nodeStart){
            temp=temp->prev;
            nodeStart=nodeStart-temp->count;
        }
        index=index-nodeStart;
    }
    temp->data[(temp->first+index)%temp->size]=item;

 }