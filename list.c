/*
File: list.c
Author: Owen DeKay
*/
//Implement a doubly linked list and a circular queue

//Should the linked list be singly-linked or doubly-linked?
//Doubly so that operations are more efficient, if we addLast is called or removeLast the time complexity is O(1)

//Do we need only a head pointer or both a head and a tail pointers?
//Both if we want to implement a doubly linked list. THis will improve effiency as we will not need to iterate through the list to get to the end.
//Without addLast and removeLast become O(N)

//Should the arrays within the nodes all be the same size, or should nodes increase in size as we add more and more elements?
//Fixed size so that we never have to resize which will cause efficiency losses.
//Indexing is simple
//Space is not wasted

/*indexing function to find the last postion:  Rather we keep track of the first slot, f ,
 *and the items are stored starting at slot f and continue through slot ( f + n − 1) mod m,
 *f=index of first item
 *n=number of items
 *m=size of array
 */



typedef struct node{
    void **data; //pointer to array of void pointers of fixed size
    int count; //number of elements stored at a given node
    int first;//index of the first element in the circular queue
    struct NODE *next; //next node 
    struct NoDE *prev;//previous node

}NODE;
typedef struct list{
    int count; //total number of elements stored in the list 
    struct LIST *head;//first node 
    struct LIST *tail;//last node
}LIST;