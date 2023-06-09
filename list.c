#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"
#define CURRENT_DATA (list->current)->data
#define IFCURRENTNULL if (list->current == NULL) return NULL;

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {

  List* nuevo = (List *) malloc(sizeof(List));

  nuevo->head=NULL;
  nuevo->tail=NULL;
  nuevo->current=NULL;

  
     return nuevo;
}

void * firstList(List * list) {
    
    if (list->head == NULL) return NULL;
  
    list->current = list->head;
    
    return CURRENT_DATA;
}

void * nextList(List * list) {
    IFCURRENTNULL
    if ((list->current)->next == NULL) return NULL;
  
    list->current = (list->current)->next;
    
    return CURRENT_DATA;
}

void * lastList(List * list) {
    IFCURRENTNULL
  
    list->current = list->tail;
    return CURRENT_DATA;
}

void * prevList(List * list) {
    IFCURRENTNULL

    if ((list->current)->prev == NULL ) return NULL;
  
  
    list->current = (list->current)->prev; 
    return CURRENT_DATA;
}

void pushFront(List * list, void * data) {

  //Crea un nuevo nodo y lo intercambia por head.
  Node* newNode = createNode(data);
  
  if (list->head == NULL) 
  {
    //En caso de que no haya nodos en la lista.
    list->head=newNode;
    list->tail=list->head;
  }
  
  newNode->next=list->head;

  (list->head)->prev=newNode;
  list->head=newNode;

  return;  
  
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  //Poner nuevo nodo frente a current.
  Node* newNode =  createNode(data);
  Node* prev = list->current;
  Node* next = list->current->next;

  if (next !=NULL)
  {
    //asignar newnode->next y al next cambiar su nuevo Prev
    newNode->next = next;
    next->prev = newNode;
  }
  else{
    //Si el siguiente es NULL, entonces el nuevo nodo es el ultimo.
    list->tail=newNode;
  }

  newNode->prev=prev;
  prev->next=newNode;
  
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if (list == NULL ) return NULL;
    IFCURRENTNULL

    

    Node * selected = list->current;
    void * dato = selected->data;

    if (selected == list->head) 
    {
        
        list->head = selected->next;
        if (list->head != NULL) 
        {
            list->head->prev = NULL;
        }
    } else if (selected == list->tail) 
    {
        list->tail = selected->prev;
        if (list->tail != NULL) {
            list->tail->next = NULL;
        }
    } else {
        // El nodo actual está en el medio de la lista.
        selected->prev->next = selected->next;
        selected->next->prev = selected->prev;
    }

    list->current = selected->next;
    free(selected);
    return dato;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}