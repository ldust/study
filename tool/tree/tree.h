//
//  tree.h
//  tool
//
//  Created by Approx on 14-6-7.
//  Copyright (c) 2014年 Aily. All rights reserved.
//

#ifndef tool_tree_h
#define tool_tree_h

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

struct _node {
    int value;
    int height;
    struct _node *left;
    struct _node *right;
};

typedef struct _node *tree;
typedef struct _node *node;


node new_node(int v){
    node n = malloc(sizeof(struct _node));
    n->value = v;
    n->left = n->right = NULL;
    n->height = 0;
    return n;
}

void print_node(node n, int depth){
    if (n != NULL) {
        for (int i = 0; i < depth; i++) {
            printf("    ");
        }
        printf("%d\n",n->value);
        print_node(n->left, depth + 1);
        print_node(n->right, depth + 1);
    }
}
void print(tree t){
    print_node(t, 0);
}

int max(int a, int b){
    return a > b?a:b;
}

int height(tree t){
    if (t) {
        return t->height;
    }else{
        return -1;
    }
}

node single_rotate(node a, int left){
    if (left) {
        node b = a->left;
        a->left = b->right;
        b->right = a;
        a->height = max(height(a->left), height(a->right)) + 1;
        b->height = max(height(b->left), height(b->right)) + 1;
        return b;
    }else{
        node b = a->right;
        a->right = b->left;
        b->left = a;
        a->height = max(height(a->left), height(a->right)) + 1;
        b->height = max(height(b->left), height(b->right)) + 1;
        return b;
    }
}

node double_rotate(node a, int left){
    if (left) {
        a->left = single_rotate(a->left, 0);
        return single_rotate(a, 1);
    }else{
        a->right = single_rotate(a->right, 1);
        return single_rotate(a, 0);
    }
}

tree insert(tree t, int v){
    if (t == NULL) {
        t = new_node(v);
    }else if (v > t->value){
        t->right = insert(t->right, v);
        if (height(t->right) - height(t->left) == 2) {
            if (v > t->right->value) {
                t = single_rotate(t, 0);
            }else{
                t = double_rotate(t, 0);
            }
        }
    }else if (v < t->value){
        t->left = insert(t->left, v);
        if (height(t->left) - height(t->right) == 2) {
            if (v < t->left->value) {
                t = single_rotate(t, 1);
            }else{
                t = double_rotate(t, 1);
            }
        }
    }
    t->height = max(height(t->left), height(t->right)) + 1;
    return t;
}

int find_min(tree t){
    while (t->left) {
        t = t->left;
    }
    return t->value;
}

node delete_node(tree t, int v){
    if (t) {
        if (t->value == v) {
            if (t->left && t->right) {
                int r_min = find_min(t);
                t->value = r_min;
                t->left = delete_node(t->left, r_min);
                
                if (height(t->right) - height(t->left) == 2) {
                    if (height(t->right->right) > height(t->right->left)) {
                        t = single_rotate(t, 0);
                    }else{
                        t = double_rotate(t, 0);
                    }
                }
            }else if (t->left == NULL && t->right == NULL){
                free(t);
                t = NULL;
            }else if (t->left){
                node tmp = t->left;
                free(t);
                t = tmp;
            }else if (t->right){
                node tmp = t->right;
                free(t);
                t = tmp;
            }
        }else if (v > t->value){
            t->right = delete_node(t->right, v);
            if (height(t->left) - height(t->right) == 2) {
                if (height(t->left->left) > height(t->left->right)) {
                    t = single_rotate(t, 1);
                }else{
                    t = double_rotate(t, 1);
                }
            }
        }else if (v < t->value){
            t->left = delete_node(t->left, v);
            if (height(t->right) - height(t->left) == 2) {
                if (height(t->right->right) > height(t->right->left)) {
                    t = single_rotate(t, 0);
                }else{
                    t = double_rotate(t, 0);
                }
            }
        }
        if (t) {
            t->height = max(height(t->left), height(t->right)) + 1;
        }
    }
    return t;
}

#define simpleRandom(from,to)  ((random() % (to + 1 - from)) + from)

tree create429(int min, int max){
    if (max >= min) {
        node n = new_node(simpleRandom(min, max));
        n->left = create429(min, n->value - 1);
        n->right = create429(n->value + 1, max);
        return n;
    }else{
        return NULL;
    }
}

void test_4_29(){
    tree t = NULL;
    t = create429(1, 10);
    print(t);
}

tree create430(int height, int *value){
    if (height >= 0) {
        node n = malloc(sizeof(struct _node));
        n->left = create430(height - 1, value);
        n->value = ++*value;
        n->right = create430(height - 1, value);
        return n;
    }
    return NULL;
}

void test_4_30(){
    tree t = NULL;
    int v = 0;
    t = create430(5, &v);
    print(t);
}

struct _queue {
    node value;
    struct _queue *last;
};
typedef struct _queue *queue;

void enqueue(queue q, node n){
    if (n) {
        while (q->last) {
            q = q->last;
        }
        q->last = malloc(sizeof(struct _queue));
        q->last->value = n;
        q->last->last = NULL;
    }
}

void print_level(tree t){
    queue node_queue = malloc(sizeof(struct _queue));
    node_queue->last = NULL;
    node_queue->value = t;

    while (node_queue) {
        node front = node_queue->value;
        enqueue(node_queue, front->left);
        enqueue(node_queue, front->right);
        printf("%d ", front->value);
        queue tmp = node_queue->last;
        free(node_queue);
        node_queue = tmp;
    }
}
void test435(){
    tree t = NULL;
    int box[] = {
        3,  2,   1,  4,  5,  6,
        7,  16, 15, 14, 13,
        12, 11, 10,  8,  9,
    };
    for (int i = 0; i < 16; i++) {
        t = insert(t, box[i]);
    }
    print(t);
    
    printf("-----\n");
    print_level(t);
}

void test(){
    tree t = NULL;
    int box[] = {
        3,  2,   1,  4,  5,  6,
        7,  16, 15, 14, 13,
        12, 11, 10,  8,  9,
    };
    for (int i = 0; i < 16; i++) {
        t = insert(t, box[i]);
    }
    print(t);
    for (int i = 0; i < 16; i++) {
        printf("============= %d\n", box[i]);
        t = delete_node(t, box[i]);
        print(t);
        
    }
}




#endif
