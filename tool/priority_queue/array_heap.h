//
//  array_heap.h
//  tool
//
//  Created by Approx on 14-6-28.
//  Copyright (c) 2014年 Aily. All rights reserved.
//

#ifndef tool_array_heap_h
#define tool_array_heap_h

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct _heap {
    int capacity;
    
    int size;
    int *data;
};

typedef struct _heap *heap;

heap new_heap(int capacity){
    heap h = malloc(sizeof(struct _heap));
    h->size = 0;
    h->capacity = capacity;
    h->data = malloc(sizeof(int) * (capacity + 1));
    return h;
}

bool is_full(heap h){
    return h->size == h->capacity;
}
void swap(heap h, int a, int b){
    int tmp = h->data[a];
    h->data[a] = h->data[b];
    h->data[b] = tmp;
}
void min_up(heap h, int index){
    for (int i = index; i > 1 && h->data[i] < h->data[i / 2]; i /= 2) {
        swap(h, i, i / 2);
    }
}
void max_down(heap h, int index){
    int i = index;
    int child = (h->data[i * 2] > h->data[i * 2 + 1]) ? (i * 2 + 1) : (i * 2);
    while (child <= h->size && h->data[i] > h->data[child]) {
        swap(h, i, child);
        i = child;
        child = (h->data[i * 2] > h->data[i * 2 + 1]) ? (i * 2 + 1) : (i * 2);
    }
}
void insert(heap h, int value){
    if (!is_full(h)) {
        h->data[++h->size] = value;
        min_up(h, h->size);
    }
}
void delete_min(heap h){
    h->data[1] = h->data[h->size--];
    max_down(h, 1);
}
void print(heap h){
    for (int i = 1; i <= h->size; i++) {
        printf("%d ",h->data[i]);
    }
    printf("\n");
}
void test(){
    heap h = new_heap(20);
    int value[] = {
        31, 32, 21, 19, 68, 16, 13, 14, 24, 65, 26
    };
    for (int i = 0; i < sizeof(value) / sizeof(int); i++) {
        insert(h, value[i]);
    }
    print(h);
    delete_min(h);
    print(h);
    delete_min(h);
    print(h);

}

#endif
