//
//  pointer_double_list.h
//  tool
//
//  Created by Aily on 14-5-27.
//  Copyright (c) 2014年 Aily. All rights reserved.
//

#ifndef tool_pointer_double_list_h
#define tool_pointer_double_list_h

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct node {
    int value;
    struct node *next;
    struct node *front;
};

typedef struct node *list;
typedef struct node *position;


void print(list list){
    position i = list->next;
    while (i != NULL) {
        //printf("%d ",i->value);
        printf("%p %p %p\n",i->front, i, i->next);
        i = i->next;
    }
    printf("end\n");
}

struct node *new_node(int value){
    struct node *v = malloc(sizeof(struct node));
    v->value = value;
    v->front = NULL;
    v->next = NULL;
    return v;
}

list new_list(){
    return new_node(0);
}

void push_back(list list, int value){
    position i = list;
    while (i->next) {
        i = i->next;
    }
    
    struct node *v = new_node(value);
    i->next = v;
    v->front = i;
}

void insert(position pos, int value){
    struct node *v = new_node(value);
    position oldnext = pos->next;
    pos->next = v;
    v->front = pos;
    v->next = oldnext;
    if (oldnext) {
        oldnext->front = v;
    }
}

position find(list list, int value){
    position i = list->next;
    while (i && i->value != value) {
        i = i->next;
    }
    return i;
}

void delete_node(list l, position i){
    i->front->next = i->next;
    if (i->next) {
        i->next->front = i->front;
    }
    free(i);
}

int is_empty(list list){
    return list->next == NULL;
}

void swap(position a, position b){
    position af = a->front;
    position bf = b->front;
    position an = a->next;
    position bn = b->next;
    
    af->next = b;
    bf->next = a;
    if (an) {
        an->front = b;
    }
    if (bn) {
        bn->front = a;
    }
    a->front = bf;
    a->next = bn;
    b->front = af;
    b->next = an;
}

void test3_2(){
    list index = new_list();
    push_back(index, 1);
    push_back(index, 2);
    push_back(index, 3);
    push_back(index, 20);
    
    list data = new_list();
    for (int i = 1; i < 21; i++) {
        push_back(data, i);
    }
    
    position i = index->next;
    position j = data->next;
    int v = 1;
    while (i != NULL) {
        while (j != NULL && v != i->value) {
            j = j->next;
            v++;
        }
        printf("%d\n",j->value);
        i = i->next;
    }
}

#define rand01 (rand() / (float)RAND_MAX)

void test3_4and3_5(){
    list a = new_list();
    list b = new_list();
    int base = 1;
    for (int i = 0; i < 20; i++) {
        push_back(a, base + (rand01 * 3));
        base += 10;
    }
    base = 1;
    for (int i = 0; i < 20; i++) {
        push_back(b, base + (rand01 * 3));
        base += 10;
    }
    
    print(a);
    print(b);
    
    position ia = a->next;
    position ib = b->next;
    
    list result = new_list();
    
    while (ia != NULL && ib != NULL) {
        if (ia->value < ib->value) {
//            push_back(result, ia->value);
            ia = ia->next;
        }else if (ia->value > ib->value){
//            push_back(result, ib->value);
            ib = ib->next;
        }else{
            push_back(result, ia->value);
            ia = ia->next;
//            push_back(result, ib->value);
            ib = ib->next;
        }
    }
//    while (ia != NULL) {
//        push_back(result, ia->value);
//        ia = ia->next;
//    }
//    while (ib != NULL) {
//        push_back(result, ib->value);
//        ib = ib->next;
//    }
    print(result);
}

void test3_10(){
#define man_count       4
#define magic_numer     1
    list l = new_list();
    for (int i = 0; i < man_count; i++) {
        push_back(l, i);
    }
    int counter = 0;
    position i = l->next;
    while (1) {
        if (counter == magic_numer) {
            delete_node(l, i);
            printf("%d\n",i->value);
            counter = 0;
        }else{
            counter++;
        }
        if (i->next == NULL) {
            i = l->next;
        }else{
            i = i->next;
        }
        if (l->next == i && i->next == NULL) {
            break;
        }
    }
    printf("\n");
    print(l);
}

/*
 约瑟夫斯环 以间隔k = 1为例
 0      ->  0
 0 1    ->  0
 
 0 1 2  ->  2
 0 2
 2 0    ->  2 先删掉第一个数1  之后剩余数字的个数就和上一次的数字个数一致了 那么只要把当前的编号映射到上一次 就可以递归的求解出全部的值
 映射的方法 把新起点和上一个起点重合 比如3的情况 新起点是2 把2放置到上次递归的0的位置 然后按顺序向后排就行了
 
 0 1 2 3 -> 0
 0 2 3
 2 3 0   -> 0
 
 0 1 2 3 4
 0 2 3 4
 
 2 3 4 0 -> 2
 
 于是公式就是 f(n) = (f(n - 1) + k + 1) % n
 
 k + 1重定向起点 求余把结果定位到新的区间
 
 */

int func(int gap, int total){
    if (total == 1) {
        return 0;
    }else{
        return (func(gap, total - 1) + gap + 1) % total;
    }
}

void test3_10_2(){
    
    int result = 0;
    for (int total = 1; total <= man_count; total++) {
        result = (result + magic_numer + 1) % total;
    }
    
    printf("%d\n",result);
    printf("%d\n", func(magic_numer, man_count));
}


//基数排序

int number_bit(int number, int slot){
    return (number / (int)powf(10, slot)) % 10;
}
int number_bit3(int number, int slot){
    return (number / (int)powf(1000, slot)) % 1000;
}

void card_sort(){
    int numbers[] = {
        64, 8, 216, 512, 27, 729, 0, 1, 343, 125,
    };
    
    list bucket[10];
    for (int i = 0; i < 10; i++) {
        bucket[i] = new_list();
    }
    
    for (int i = 0; i < sizeof(numbers) / sizeof(int); i++) {
        int bit = number_bit(numbers[i], 0);
        push_back(bucket[bit], numbers[i]);
    }

    
    for (int times = 1; times < 3; times++) {
        for (int i = 0; i < 10; i++) {
            position itr = bucket[i]->next;
            while (itr != NULL) {
                int bit = number_bit(itr->value, times);
                if (bit != i) {
                    push_back(bucket[bit], itr->value);
                    position del = itr;
                    itr = itr->next;
                    delete_node(bucket[i], del);
                }else{
                    itr = itr->next;
                }
            }
        }
    }
    list result = new_list();
    for (int i = 0; i < 10; i++) {
        position itr = bucket[i]->next;
        while (itr != NULL) {
            push_back(result, itr->value);
            itr = itr->next;
        }
    }
    print(result);
}

void test3_13(){
    
    
    int numbers[100];
    for (int i = 0; i < 100; i++) {
        numbers[i] = rand() % 899999999 + 100000000;
    }
    
#define bucket_count    1000
    
    list bucket[bucket_count];
    for (int i = 0; i < bucket_count; i++) {
        bucket[i] = new_list();
    }
    
    for (int i = 0; i < sizeof(numbers) / sizeof(int); i++) {
        int bit = number_bit3(numbers[i], 0);
        push_back(bucket[bit], numbers[i]);
    }
    
    
    for (int times = 1; times < 3; times++) {
        for (int i = 0; i < bucket_count; i++) {
            position itr = bucket[i]->next;
            while (itr != NULL) {
                int bit = number_bit3(itr->value, times);
                if (bit != i) {
                    push_back(bucket[bit], itr->value);
                    position del = itr;
                    itr = itr->next;
                    delete_node(bucket[i], del);
                }else{
                    itr = itr->next;
                }
            }
        }
    }
    list result = new_list();
    for (int i = 0; i < bucket_count; i++) {
        position itr = bucket[i]->next;
        while (itr != NULL) {
            push_back(result, itr->value);
            itr = itr->next;
        }
    }
    
    print(result);
}











#endif
