/*
File: list.c
Author: Owen DeKay
*/

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "list.h"
#define NODE_SIZE 64


typedef struct node{
    void **data; //pointer to array of void pointers of fixed size
    int count; //number of elements stored at a given node
    int first;//index of the first element in the circular queue
    int size;//how many slots are in a node
    struct node *next; //next node 
    struct node *prev;//previous node

}NODE;

typedef struct list{
    int count; //total number of elements stored in the list 
    struct node *head;//first node 
    struct node *tail;//last node
}LIST;

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

 int numItems(LIST *lp){
    assert(lp!=NULL);
    return lp->count;

 }

 void addFirst(LIST *lp, void *item){
    assert(lp!=NULL);
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
    lp->head->first=(lp->head->first-1 +lp->head->size)%lp->head->size;
    lp->head->data[lp->head->first]=item;
    lp->head->count++;
    lp->count++;

 }

 void addLast(LIST *lp, void *item){
    assert(lp!=NULL);
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

 void *removeFirst(LIST *lp){
    //Check for empty list
    assert(lp!=NULL && lp->count>0);
    //Get value
    void *value=lp->head->data[lp->head->first];
    //Move first
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

 void *getFirst(LIST *lp){
    assert(lp!=NULL);
    return lp->head->data[lp->head->first];

 }

 void *getLast(LIST *lp){
    assert(lp!=NULL);
    int index=(lp->tail->first + lp->tail->count -1)%lp->tail->size;
    return lp->tail->data[index];


 }

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
        int nodeStart=lp->count-temp->count;
        while(index<nodeStart){
            temp=temp->prev;
            nodeStart=nodeStart-temp->count;
        }
        index=index-nodeStart;
    }
    return temp->data[(temp->first+index)%temp->size];

 }

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