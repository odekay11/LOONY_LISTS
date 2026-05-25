/*
File: list.c
Author: Owen DeKay
*/

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "list.h"
#define INTIAL_NODE_SIZE 2


typedef struct node{
    void **data; //pointer to array of void pointers of fixed size
    int count; //number of elements stored at a given node
    int first;//index of the first element in the circular queue
    int size;//how many slots are in a node
    struct NODE *next; //next node 
    struct NODE *prev;//previous node

}NODE;

typedef struct list{
    int count; //total number of elements stored in the list 
    struct LIST *head;//first node 
    struct LIST *tail;//last node
}LIST;

 LIST *createList(void){
    //allocate list struct
    LIST *lp=malloc(sizeof(LIST));
    assert(lp!=NULL);

    //allocate first node
    NODE *node=malloc(sizeof(NODE));
    assert(node!=NULL);

    node->data=malloc(sizeof(void *)*INTIAL_NODE_SIZE);
    assert(node->data!=NULL);

    node->size=INTIAL_NODE_SIZE;
    node->first=0;
    node->count=0;
    node->next=NULL;
    node->prev=NULL;

    lp->count=0;
    lp->head=node;
    lp->tail=node;


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

 }

 void addLast(LIST *lp, void *item){

 }

 void *removeFirst(LIST *lp){

 }

 void *removeLast(LIST *lp){

 }

 void *getFirst(LIST *lp){

 }

 void *getLast(LIST *lp){

 }

 void *getItem(LIST *lp, int index){

 }

 void setItem(LIST *lp, int index, void *item){

 }