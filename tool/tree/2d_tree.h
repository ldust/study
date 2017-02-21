//
//  2d_tree.h
//  tool
//
//  Created by Aily on 14-6-23.
//  Copyright (c) 2014年 Aily. All rights reserved.
//

#ifndef tool__d_tree_h
#define tool__d_tree_h

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

struct point {
    float x;
    float y;
};

struct _node {
    struct point point;
    struct _node *left;
    struct _node *right;
};

typedef struct _node *node;

node create_tree(node n, struct point p, bool flag){
    if (n == NULL) {
        n = malloc(sizeof(struct _node));
        n->left = NULL;
        n->right = NULL;
        n->point = p;
    }else{
        int a, b;
        if (flag) {
            a = n->point.x;
            b = p.x;
        }else{
            a = n->point.y;
            b = p.y;
        }
        if (b > a) {
            n->right = create_tree(n->right, p, !flag);
        }else{
            n->left = create_tree(n->left, p, !flag);
        }
    }
    return n;
}

float distance(struct point a, struct point b){
    float i = a.x - b.x;
    float j = a.y - b.y;
    return sqrtf(i * i + j * j);
}

struct point result = {0, 0};

float get_min(node t, const struct point p, float min, bool flag){
    if (t) {
        float dis = distance(t->point, p);
        if (dis < min) {
            min = dis;
            result = t->point;
        }
        float l = get_min(t->left, p, min, !flag);
        if (l < min) {
            min = l;
        }
        float sss = 0.0;
        if (flag) {
            sss = sqrtf((t->point.x - p.x) * (t->point.x - p.x));
        }else{
            sss = sqrtf((t->point.y - p.y) * (t->point.y - p.y));
        }
        if (sss <= min) {
            l = get_min(t->right, p, min, !flag);
            if (l < min) {
                min = l;
            }
        }else{
            printf("%f %f\n",t->point.x, t->point.y);
        }
    }
    return min;
}


void test(){
    
    struct point pos[] = {
        {1, 1},
        {1, 3},
        {3, 4},
    };
    node n = NULL;
    for (int i = 0; i < sizeof(pos) / sizeof(struct point); i++) {
        n = create_tree(n, pos[i], true);
    }
    
    struct point p = {2, 3};
    float min = 100000.0;
    min = get_min(n, p, min, true);
    
    printf("%f %f %f",result.x, result.y, min);
}


#endif
