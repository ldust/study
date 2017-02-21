//
//  hash_table.h
//  tool
//
//  Created by Approx on 14-6-23.
//  Copyright (c) 2014年 Aily. All rights reserved.
//

#ifndef tool_hash_table_h
#define tool_hash_table_h

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

enum hash_node_type {
    empty,
    legitimate,
    deleted,
};

struct hash_node {
    char *key;
    int value;
    enum hash_node_type type;
};

struct hash_table {
    unsigned size;
    struct hash_node *data;
};

typedef struct hash_table *hash_table;

hash_table init_table(unsigned size){
    hash_table tb = malloc(sizeof(struct hash_table));
    tb->size = size;
    tb->data = malloc(sizeof(struct hash_node) * size);
    
    for (int i = 0; i < size; i++) {
        tb->data[i].type = empty;
    }
    return tb;
}

unsigned hash(const char *k, unsigned table_size){
    unsigned index = 0;
    while (*k != '\0') {
        index = (index << 5) + *k++;
    }
    return index;
}

int find(hash_table tb, const char *k){
    unsigned index = hash(k, tb->size);
    int hit = 0;
    while (tb->data[index].type != empty && strcmp(tb->data[index].key, k) != 0) {
        index += 2 * ++hit - 1;
        if (index >= tb->size) {
            index -= tb->size;
        }
    }
    return index;
}

void insert(hash_table tb, int v, const char *k){
    unsigned index = find(tb, k);
    tb->data[index].key = malloc(sizeof(char) * (strlen(k) + 1));
    strcpy(tb->data[index].key, k);
    tb->data[index].value = v;
    tb->data[find(tb, k)].type = legitimate;
}

void test(){
    char *a = "abcd";
    char *b = "bcdf";
    
    unsigned hasha = hash(a, 13);
    unsigned hashb = hash(b, 13);
    unsigned fast = (hasha << 5) - ('a' << (4 * 5)) + 'f';
    printf("%u %u %u %u\n",hasha, hashb, fast, -1);
}

#endif










