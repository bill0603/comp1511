//A BUGGY linked list implementation of a queue

#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

struct queueNode { 
    int item; 
    struct queueNode * next; 
};

struct queue { 
    struct queueNode * head; 
    struct queueNode * tail;
    int size; 
    int maxSize;
};


static struct queueNode * createNode(int item){ 
    struct queueNode * n = malloc (sizeof(struct queueNode));
    if(n == NULL){
        fprintf(stderr,"out of memory\n");
        exit(EXIT_FAILURE);
    }
    n->item = item; 
    n->next = NULL;     
    return n;                         
}

// Creates an empty Queue
Queue queueCreate (int maxSize){ 
    Queue q = malloc (sizeof (struct queue));
    if(q == NULL){
        fprintf(stderr,"out of memory\n");
        exit(EXIT_FAILURE);
    } 
    q->head = NULL; 
    q->tail = NULL;
    q->size = 0; 
    q->maxSize = maxSize;
    return q;
}

//Delete the queue.
void queueDestroy(Queue queue){
    struct queueNode * curr;
    struct queueNode * next;
    curr = queue->head;
    while(curr != NULL){
        next = curr->next;
        free(curr);
        curr = next;
    }
}

//Size of the queue.
int queueSize (Queue q){ 
    return q->size; 
}

//Even though linked lists have no fixed size,
//we are respecting the interface and giving the
//queue a max size limit in this implementation.
//Delete queue if queue is too big. Add a node at the end of the queue.
void enqueue (Queue q, int item){ 
    if (q->size >= q->maxSize){
       fprintf(stderr,"Queue full\n");
       queueDestroy(q);
       exit(EXIT_FAILURE);
    }
    struct queueNode * n = createNode(item);
    struct queueNode * current = q->head;
    if (current == NULL) {
        q->head = n;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = n;
    }
    q->tail = n; 
    q->size ++;
}

//Delete the queue if queue is too big. Delete the first node in queue.
int dequeue (Queue q){
    if(q->size == 0){       
        fprintf(stderr,"Queue empty\n");
        queueDestroy(q);
        exit(EXIT_FAILURE);
    }
    int item = q->head->item;
    struct queueNode * delNode = q->head;
    if(q->head != q->tail){
        q->head = q->head->next;
    } 
    free(delNode);
    q->size--;
    return item;
}

//return item  in the first node.
int queueFront (Queue q){
    if(q->size == 0){       
        fprintf(stderr,"Queue empty\n");
        queueDestroy(q);
        exit(EXIT_FAILURE);
    }      
    return q->head->item;
}

