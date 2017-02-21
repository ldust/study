//
//  b-tree.h
//  tool
//
//  Created by Approx on 14-6-9.
//  Copyright (c) 2014年 Aily. All rights reserved.
//

#ifndef tool_b_tree_h
#define tool_b_tree_h

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

#define M 3

struct _node {
    int p_value;
    struct _node *pointer[M + 1];
    int value[M + 1];
    
    struct _node *parent;
    bool is_leaf;
};

typedef struct _node *node;

void print_node(node n, int depth){
    for (int i = 0; i < depth; i++) {
        printf("    ");
    }
    if (n != NULL) {
        if (n->is_leaf) {
            for (int i = 0; i < n->p_value; i++) {
                printf("(%d) ",n->value[i]);
            }
            printf("\n");
        }else{
            printf("[");
            for (int i = 0; i < n->p_value; i++) {
                printf("%d",n->value[i]);
                if (i != n->p_value) {
                    printf(" ");
                }
            }
            printf("]\n");
            for (int i = 0; i <= n->p_value; i++) {
                print_node(n->pointer[i], depth + 1);
            }
            printf("\n");
        }
    }
}
void print(node t){
    print_node(t, 0);
}

void sort_int(int box[], int size){
    for (int i = 1; i < size; i++) {
        int tmp = box[i];
        int j;
        for (j = i; j > 0 && box[j - 1] > tmp; j--) {
            box[j] = box[j - 1];
        }
        box[j] = tmp;
    }
}
void sort_node(node box[], int size){
    for (int i = 1; i < size; i++) {
        node tmp = box[i];
        int j;
        for (j = i; j > 0 && box[j - 1]->value[0] > tmp->value[0]; j--) {
            box[j] = box[j - 1];
        }
        box[j] = tmp;
    }
}

node insert(node n, int v);

int find_min(node n){
    while (!n->is_leaf) {
        n = n->pointer[0];
    }
    return n->value[0];
}

void fill_parent_value(node n){
    for (int i = 1; i <= n->p_value; i++) {
        n->value[i - 1] = find_min(n->pointer[i]);
    }
}

node separate_node(node parent, node n){
    if (parent == NULL) {
        parent = malloc(sizeof(struct _node));
        parent->p_value = 0;
        parent->parent = NULL;
        parent->is_leaf = false;
        parent->pointer[0] = n;
    }
    node separate = NULL;
    if (n->is_leaf) {
        for (int i = n->p_value / 2; i < n->p_value; i++) {
            separate = insert(separate, n->value[i]);
        }
    }else{
        separate = malloc(sizeof(struct _node));
        separate->p_value = 0;
        separate->parent = NULL;
        separate->is_leaf = false;
        for (int i = n->p_value / 2 + 1; i < n->p_value; i++) {
            separate->value[separate->p_value] = n->value[i];
            separate->pointer[separate->p_value] = n->pointer[i];
            separate->p_value++;
        }
        separate->pointer[separate->p_value] = n->pointer[n->p_value];
    }
    parent->pointer[parent->p_value + 1] = separate;
    parent->p_value++;
    
    n->parent = separate->parent = parent;
    n->p_value /= 2;
    
    sort_node(parent->pointer, parent->p_value + 1);
    fill_parent_value(parent);
    
    return parent;
}

node insert(node n, int v){
    if (n == NULL) {
        n = malloc(sizeof(struct _node));
        n->p_value = 0;
        n->parent = NULL;
        n->is_leaf = true;
        n = insert(n, v);
    }else if (n->is_leaf){
        n->value[n->p_value] = v;
        n->p_value++;
        sort_int(n->value, n->p_value);
    }else{
        int pos = n->p_value;
        for (int i = 0; i < n->p_value; i++) {
            if (v < n->value[i]) {
                pos = i;
                break;
            }
        }
        n->pointer[pos] = insert(n->pointer[pos], v);
        if (n->pointer[pos]->p_value > (n->pointer[pos]->is_leaf ? M : M - 1)) {
            n = separate_node(n, n->pointer[pos]);
        }
    }
    if (n->parent == NULL && n->p_value > (n->is_leaf ? M : M - 1)) {
        n = separate_node(n->parent, n);
    }
    return n;
}

node combine(node parent, int pos){
    node small = parent->pointer[pos];
    if (pos == parent->p_value) {
        node brother = parent->pointer[pos - 1];
        if (small->is_leaf) {
            int total_size = small->p_value + brother->p_value;
            if (total_size <= M) {
                for (int i = 0; i < small->p_value; i++) {
                    brother->value[brother->p_value] = small->value[i];
                    brother->p_value++;
                }
                sort_int(brother->value, brother->p_value);
                free(small);
                parent->p_value--;
            }else{
                int brother_size = brother->p_value;
                for (int i = total_size / 2; i < brother_size; i++) {
                    small->value[small->p_value] = brother->value[i];
                    small->p_value++;
                    brother->p_value--;
                }
                sort_int(small->value, small->p_value);
            }
        }else{
            int total_size = small->p_value + brother->p_value + 2;
            if (total_size <= M) {
                for (int i = 0; i <= small->p_value; i++) {
                    brother->pointer[brother->p_value + 1] = small->pointer[i];
                    brother->p_value++;
                }
                sort_node(brother->pointer, brother->p_value + 1);
                free(small);
                parent->p_value--;
                fill_parent_value(brother);
            }else{
                int brother_size = brother->p_value;
                for (int i = total_size / 2; i <= brother_size; i++) {
                    small->pointer[small->p_value + 1] = brother->pointer[i];
                    small->p_value++;
                    brother->p_value--;
                }
                sort_node(small->pointer, small->p_value + 1);
                fill_parent_value(brother);
                fill_parent_value(small);
            }
        }
    }else{
        node brother = parent->pointer[pos + 1];
        if (small->is_leaf) {
            int total_size = small->p_value + brother->p_value;
            if (total_size <= M) {
                for (int i = 0; i < small->p_value; i++) {
                    brother->value[brother->p_value] = small->value[i];
                    brother->p_value++;
                }
                sort_int(brother->value, brother->p_value);
                free(small);
                for (int i = pos; i < parent->p_value; i++) {
                    parent->pointer[i] = parent->pointer[i + 1];
                }
                parent->p_value--;
            }else{
                for (int i = 0; i < total_size / 2 - 1; i++) {
                    small->value[small->p_value] = brother->value[i];
                    small->p_value++;
                }
                int brother_size = brother->p_value;
                for (int i = total_size / 2 - 1; i < brother_size; i++) {
                    brother->value[i - total_size / 2 + 1] = brother->value[i];
                }
                brother->p_value -= total_size / 2 - 1;
            }
        }else{
            int total_size = small->p_value + brother->p_value + 2;
            if (total_size <= M) {
                for (int i = 0; i <= small->p_value; i++) {
                    brother->pointer[brother->p_value + 1] = small->pointer[i];
                    brother->p_value++;
                }
                sort_node(brother->pointer, brother->p_value + 1);
                free(small);
                fill_parent_value(brother);
                for (int i = pos; i < parent->p_value; i++) {
                    parent->pointer[i] = parent->pointer[i + 1];
                }
                parent->p_value--;
            }else{
                for (int i = 0; i < total_size / 2 - 1; i++) {
                    small->pointer[small->p_value + 1] = brother->pointer[i];
                    small->p_value++;
                }
                int brother_size = brother->p_value;
                for (int i = total_size / 2 - 1; i <= brother_size; i++) {
                    brother->pointer[i - total_size / 2 + 1] = brother->pointer[i];
                }
                brother->p_value -= total_size / 2 - 1;
                fill_parent_value(brother);
                fill_parent_value(small);
            }
        }
    }
    return parent;
}

node erase_node(node n, int v){
    if (n->is_leaf) {
        for (int i = 0; i < n->p_value; i++) {
            int tmp = n->value[i];
            if (v == tmp) {
                n->value[i] = n->value[n->p_value - 1];
                n->value[n->p_value - 1] = tmp;
                n->p_value--;
                sort_int(n->value, n->p_value);
                break;
            }
        }
    }else{
        int pos = n->p_value;
        for (int i = 0; i < n->p_value; i++) {
            if (v < n->value[i]) {
                pos = i;
                break;
            }
        }
        n->pointer[pos] = erase_node(n->pointer[pos], v);
        int gate = n->pointer[pos]->is_leaf ? ceilf(M / 2.0) : ceilf((M - 1) / 2.0);
        if (n->pointer[pos]->p_value < gate) {
            n = combine(n, pos);
            fill_parent_value(n);
        }
    }
    if (!n->is_leaf && n->parent == NULL && n->p_value < ceilf((M - 1) / 2.0)) {
        assert(n->p_value == 0);
        node new_root = n->pointer[0];
        new_root->parent = NULL;
        free(n);
        n = new_root;
    }
    return n;
}

void test(){
    node test_tree = NULL;
    int numbers[] = {
        3, 1, 6, 8, 9, 2, 7, 0, 10, 11, 13, 14, 15
    };
    for (int i = 0; i < sizeof(numbers) / sizeof(int); i++) {
        test_tree = insert(test_tree, numbers[i]);
    }
    print(test_tree);
    for (int i = sizeof(numbers) / sizeof(int) - 1; i >= 0; i--) {
        test_tree = erase_node(test_tree, numbers[i]);
        print(test_tree);
    }

}

#endif
