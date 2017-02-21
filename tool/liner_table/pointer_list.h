//
//  pointer_list.h
//  tool
//
//  Created by Aily on 14-5-27.
//  Copyright (c) 2014年 Aily. All rights reserved.
//

#ifndef tool_pointer_list_h
#define tool_pointer_list_h

#include <stdlib.h>
#include <stdio.h>

struct node {
    int value;
    struct node *next;
};

typedef struct node *list;
typedef struct node *position;

struct node *new_node(int value){
    struct node *l = malloc(sizeof(struct node));
    l->value = value;
    l->next = NULL;
    return l;
}

list new_list(){
    return new_node(0);
}

void push_back(list l, int value){
    struct node *pos = l;
    while (pos->next != NULL) {
        pos = pos->next;
    }
    struct node *n = new_node(value);
    pos->next = n;
}

void insert_back(position p, int value){
    struct node *n = new_node(value);
    n->next = p->next;
    p->next = n;
}

void delete_back(position p){
    struct node *i = p->next;
    p->next = i->next;
    free(i);
}

int empty(list l){
    return l->next == NULL;
}

int islast(struct node *n){
    return n->next == NULL;
}

position find(list l, int value){
    struct node *i = l->next;
    while (i != NULL && i->value != value) {
        i = i->next;
    }
    return i;
}

void print(list l){
    struct node *i = l->next;
    while (i != NULL) {
        printf("%d->",i->value);
        i = i->next;
    }
    printf("end\n");
}

position head(list l){
    return l->next;
}

void swap_back(position a, position b){
    position an = a->next;
    position bn = b->next;
    a->next = bn;
    b->next = an;
    position tmp = an->next;
    an->next = bn->next;
    bn->next = tmp;
}

void reverse1(list l){
    struct node *current = l->next;
    while (current->next != NULL) {
        insert_back(l, current->next->value);
        delete_back(current);
    }
    
    print(l);
}
void reverse2(list l){
    //l->0->1->2->3
    position p = l->next;
    position c = p->next;
    p->next = NULL;
    while (c) {
        c->next = p;
        p = c;
        
    }
    
    
    /*
    struct node *current = l->next;
    while (current && current->next) {
        struct node *willHead = current->next;
        struct node *willHeadNext = willHead->next;
        struct node *currentHead = l->next;
        
        l->next = willHead;
        willHead->next = currentHead;
        current->next = willHeadNext;
    }*/
}
list reverse3(list l, position p){
    //l->0->{9,8,7,..}->null
    //l->{9,8,7,..}->0->null
    if (p && p->next != NULL) {
        l->next = p->next;
        list big_end = reverse3(l, p->next);
        big_end->next = p;
        p->next = NULL;
    }
    return p;
}
void test3_12(){
    list l = new_list();
    for (int i = 0; i < 10; i++) {
        push_back(l, i);
    }
    print(l);
    
    position current = l;
    position next = l->next;
    position previous = NULL;
    while (next != NULL) {
        current->next = previous;
        previous = current;
        current = next;
        next = next->next;
    }
    current->next = previous;
    
    print(current);
    
}

#endif
