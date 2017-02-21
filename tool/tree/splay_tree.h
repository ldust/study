//
//  splay_tree.h
//  tool
//
//  Created by Aily on 14-6-9.
//  Copyright (c) 2014年 Aily. All rights reserved.
//

#ifndef tool_splay_tree_h
#define tool_splay_tree_h

#include <stdlib.h>
#include <stdio.h>

extern "C"{
struct _node {
    int value;
    struct _node *parent;
    struct _node *left;
    struct _node *right;
    
    int x;
    int y;
};

typedef struct _node *node;
typedef node tree;

void print_node(node n, int depth){
    for (int i = 0; i < depth; i++) {
        printf("    ");
    }
    if (n != NULL) {
        printf("%d \n",n->x);
        print_node(n->left, depth + 1);
        print_node(n->right, depth + 1);
    }else{
        printf("~ \n");
    }
}

void print(tree t){
    print_node(t, 0);
}

node insert(node n, int v){
    if (n == NULL) {
        n = (node)malloc(sizeof(struct _node));
        n->left = n->right = n->parent = NULL;
        n->value = v;
    }else if (v > n->value){
        n->right = insert(n->right, v);
        n->right->parent = n;
    }else if (v < n->value){
        n->left = insert(n->left, v);
        n->left->parent = n;
    }
    return n;
}

node single_rotate(node p, int is_left){
    if (is_left) {
        node s = p->left;
        p->left = s->right;
        s->right = p;
        
        s->parent = p->parent;
        if (p->left) {
            p->left->parent = p;
        }
        p->parent = s;
        return s;
    }else{
        node s = p->right;
        p->right = s->left;
        s->left = p;
        
        s->parent = p->parent;
        if (p->right) {
            p->right->parent = p;
        }
        p->parent = s;
        return s;
    }
}

node double_rotate(node p, int is_left){
    if (is_left) {
        p->left = single_rotate(p->left, 0);
        return single_rotate(p, 1);
    }else{
        p->right = single_rotate(p->right, 1);
        return single_rotate(p, 0);
    }
}

node zig_zig(node p, int is_left){
    p = single_rotate(p, is_left);
    return single_rotate(p, is_left);
}

tree spaly(node n){
    node parent = n->parent;
    if (parent) {
        node grand_parent = parent->parent;
        if (grand_parent) {
            node new_toper = NULL;
            node gg_parent = grand_parent->parent;
            int link_left = 0;
            if (grand_parent->parent) {
                if (grand_parent->parent->left == grand_parent) {
                    link_left = 1;
                }
            }
            
            if (grand_parent->left == parent) {
                if (parent->left == n) {
                    new_toper = zig_zig(grand_parent, 1);
                }else{
                    new_toper = double_rotate(grand_parent, 1);
                }
            }else{
                if (parent->right == n) {
                    new_toper = zig_zig(grand_parent, 0);
                }else{
                    new_toper = double_rotate(grand_parent, 0);
                }
            }
            if (gg_parent) {
                if (link_left) {
                    gg_parent->left = new_toper;
                }else{
                    gg_parent->right = new_toper;
                }
            }
            n = spaly(n);
        }else{
            n = single_rotate(parent, parent->left == n);
        }
    }
    return n;
}

node find(const tree t, int v){
    if (t->value == v) {
        return t;
    }else if (v > t->value){
        return find(t->right, v);
    }else{
        return find(t->left, v);
    }
}

node splay_find(tree t, int v){
    node n = find(t, v);
    return spaly(n);
}

node splay_find_max(tree t){
    while (t->right) {
        t = t->right;
    }
    return spaly(t);
}

node delete_node(tree t, int v){
    t = splay_find(t, v);
    node new_root = splay_find_max(t->left);
    new_root->right = t->right;
    free(t);
    return new_root;
}

void test(){
    tree t = NULL;
    for (int i = 32; i > 0; i--) {
        t = insert(t, i);
    }
    for (int i = 1; i <= 9; i++) {
        t = splay_find(t, i);
    }
    print(t);
    
    t = delete_node(t, 12);
    
    printf("==========\n");
    
    print(t);
}
}
#endif
