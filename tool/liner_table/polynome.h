//
//  polynome.h
//  tool
//
//  Created by Aily on 14-5-28.
//  Copyright (c) 2014年 Aily. All rights reserved.
//

#ifndef tool_polynome_h
#define tool_polynome_h

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <memory.h>


struct node {
    int coeff;
    int power;
    
    struct node *next;
    struct node *front;
};

typedef struct node *list;
typedef struct node *position;


void print(list list){
    position i = list->next;
    while (i != NULL) {
        printf("%d^%d + ",i->coeff, i->power);
        i = i->next;
    }
    printf("\n");
}

struct node *new_node(int coeff, int power){
    struct node *v = malloc(sizeof(struct node));
    v->coeff = coeff;
    v->power = power;
    v->front = NULL;
    v->next = NULL;
    return v;
}

list new_list(){
    return new_node(0, 0);
}

void push_back(list list, int coeff, int power){
    position i = list;
    while (i->next) {
        i = i->next;
    }
    
    struct node *v = new_node(coeff, power);
    i->next = v;
    v->front = i;
}

void insert(position pos, int coeff, int power){
    struct node *v = new_node(coeff, power);
    position oldnext = pos->next;
    pos->next = v;
    v->front = pos;
    v->next = oldnext;
    if (oldnext) {
        oldnext->front = v;
    }
}

position find(list list, int coeff, int power){
    position i = list->next;
    while (i && (i->coeff != coeff || i->power != power)) {
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

#define rand01 (rand() / (float)RAND_MAX)
void test3_6(){
    list a = new_list();
    list b = new_list();
    int base = 1;
    for (int i = 0; i < 6; i++) {
        push_back(a, i + 1, base + (rand01 * 3));
        base += 10;
    }
    base = 1;
    for (int i = 0; i < 5; i++) {
        push_back(b, i + 1, base + (rand01 * 3));
        base += 10;
    }
    
    print(a);
    print(b);
    
    position ia = a->next;
    position ib = b->next;
    
    list result = new_list();
    
    while (ia != NULL && ib != NULL) {
        if (ia->power < ib->power) {
            push_back(result, ia->coeff, ia->power);
            ia = ia->next;
        }else if (ia->power > ib->power){
            push_back(result, ib->coeff, ib->power);
            ib = ib->next;
        }else{
            push_back(result, ia->coeff + ib->coeff , ia->power);
            ia = ia->next;
            ib = ib->next;
        }
    }
    while (ia != NULL) {
        push_back(result, ia->coeff, ia->power);
        ia = ia->next;
    }
    while (ib != NULL) {
        push_back(result, ib->coeff, ib->power);
        ib = ib->next;
    }
    print(result);
}

void insertToResult(list result, int coeff, int power){
    //push_back(result, coeff, power);
    int find = 0;
    position ir = result->next;
    while (ir) {
        if (ir->power == power) {
            int new_coeff = ir->coeff + coeff;
            if (new_coeff >= 10) {
                ir->coeff = (new_coeff) % 10;
                insertToResult(result, (int)(new_coeff / 10), power + 1);
            }else{
                ir->coeff += coeff;
            }
            find = 1;
            break;
        }
        ir = ir->next;
    }
    if (find == 0 && coeff != 0) {
        if (coeff >= 10) {
            push_back(result, coeff % 10, power);
            insertToResult(result, (int)(coeff / 10), power + 1);
        }else{
            push_back(result, coeff, power);
        }
    }
}


list multiply(list a, list b){
    list result = new_list();
    
    position ia = a->next;
    while (ia != NULL) {
        position ib = b->next;
        
        while (ib != NULL) {
            int new_coeff = ia->coeff * ib->coeff;
            int new_power = ia->power + ib->power;
            insertToResult(result, new_coeff, new_power);
            ib = ib->next;
        }
        ia = ia->next;
    }
    return result;
}

void test3_7(){
    //4x^4 + 2x^3 + 3
    //5x^10 + 4x^4 + 7x + 10
    
    list a = new_list();
    push_back(a, 4, 4);
    
    list b = new_list();
    push_back(b, 5, 10);
    
    multiply(a, b);
}

list poly_power(list l, int p){
    if (p == 1) {
        return l;
    }else if (p % 2 == 0){
        return poly_power(multiply(l, l), p / 2);
    }else{
        return multiply(poly_power(multiply(l, l), p / 2), l);
    }
}

void test3_8(){
    list test = new_list();
    push_back(test, 5, 121);
    push_back(test, 7, 108);
    
    print(poly_power(test, 4));
}

void test3_9(){
    list number = new_list();
    //还是排序好... 这样算出来的顺序错误 而且消耗很大 因为每次是从头扫描
    //2^4000 = (2^4)^1000 = (1*10^1 + 6*10^0)^1000
    push_back(number, 1, 1);
    push_back(number, 6, 0);
    
    int box[10];
    memset(box, 0, sizeof(int) * 10);
    
    position i = poly_power(number, 1000)->next;
    while (i != NULL) {
        box[i->coeff]++;
        i = i->next;
    }
    for (int i = 0; i < 10; i++) {
        printf("%d ",box[i]);
    }
    
}
#endif

















