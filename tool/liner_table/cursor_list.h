//
//  cursor_list.h
//  tool
//
//  Created by Aily on 14-5-27.
//  Copyright (c) 2014年 Aily. All rights reserved.
//

#ifndef tool_cursor_list_h
#define tool_cursor_list_h

#include <stdio.h>

typedef int position;
typedef int list;

struct node {
    int value;
    position next;
};

#define space_size 500

static struct node space[space_size];

void init_space(){
    for (int i = 0; i < space_size; i++) {
        space[i].next = i + 1;
    }
    space[space_size - 1].next = 0;
}

position cursor_alloc(){
    position p = space[0].next;
    space[0].next = space[p].next;
    return p;
}

void cursor_free(position i){
    space[i].next = space[0].next;
    space[0].next = i;
}

void print(list list){
    position i = space[list].next;
    while (i) {
        printf("%d ",space[i].value);
        i = space[i].next;
    }
    printf("end\n");
}

position new_node(int value){
    position i = cursor_alloc();
    space[i].value = value;
    space[i].next = 0;
    return i;
}

list new_list(){
    return new_node(0);
}

void push_back(list list, int value){
    position i = list;
    while (space[i].next) {
        i = space[i].next;
    }
    position v = new_node(value);
    space[i].next = v;
}

position find(list list, int value){
    position i = space[list].next;
    while (i && space[i].value != value) {
        i = space[i].next;
    }
    return i;
}

void insert(position pos, int value){
    position v = new_node(value);
    position oldnext = space[pos].next;
    space[pos].next = v;
    space[v].next = oldnext;
}

void delete_back(position p){
    position i = space[p].next;
    space[p].next = space[i].next;
    cursor_free(i);
}

#endif
