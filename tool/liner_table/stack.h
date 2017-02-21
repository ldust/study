//
//  stack.h
//  tool
//
//  Created by Aily on 14-5-27.
//  Copyright (c) 2014年 Aily. All rights reserved.
//

#ifndef tool_stack_h
#define tool_stack_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define pchar_stack

#ifdef char_stack
#define stack_type char
#endif

#ifdef pchar_stack
#define stack_type char*
#endif

struct stack_ {
    int pointer;
    stack_type *container;
};

typedef struct stack_ *stack;

stack new_stack(int capacity){
    stack v = malloc(sizeof(struct stack_));
    v->pointer = -1;
    v->container = malloc(sizeof(stack_type) * capacity);
    return v;
}

void delete_stack(stack s){
    free(s->container);
    free(s);
}

void push(stack s, stack_type value){
    s->container[++s->pointer] = value;
}

stack_type pop(stack s){
    return s->container[s->pointer--];
}

stack_type top(stack s){
    return s->container[s->pointer];
}

int empty(stack s){
    return s->pointer == -1;
}

#ifdef char_stack
void test3_18(){
    char *source = "begin/end()[]{(}";
    char begin[5] = "begin";
    char end[3] = "end";
    
    stack stack = new_stack(50);
    
    int b_index = 0;
    int e_index = 0;
    
    for (int i = 0; i < strlen(source); i++) {
        char current = source[i];
        if (current == begin[b_index]) {
            b_index++;
            if (b_index == 5) {
                push(stack, 0);
                b_index = 0;
            }
        }else{
            b_index = 0;
        }
        if (current == end[e_index]) {
            e_index++;
            if (e_index == 3) {
                if (empty(stack)) {
                    printf("error end without begin\n");
                }else{
                    if (pop(stack) != 0) {
                        printf("error end without begin\n");
                    }
                }
                e_index = 0;
            }
        }else{
            e_index = 0;
        }
        switch (current) {
            case '(':{
                push(stack, 1);
                break;
            }
            case ')':{
                if (empty(stack)) {
                    printf("error ) without (\n");
                }else{
                    if (pop(stack) != 1) {
                        printf("error ) without (\n");
                    }
                }
                break;
            }
            
            case '[':{
                push(stack, 2);
                break;
            }
            case ']':{
                if (empty(stack)) {
                    printf("error ] without [\n");
                }else{
                    if (pop(stack) != 2) {
                        printf("error ] without [\n");
                    }
                }
                break;
            }
 
            case '{':{
                push(stack, 3);
                break;
            }
            case '}':{
                if (empty(stack)) {
                    printf("error } without {\n");
                }else{
                    if (pop(stack) != 3) {
                        printf("error } without {\n");
                    }
                }
                break;
            }

            default:
                break;
        }
    }
    
}

int to_number(char c){
    if (c >= 48 && c <= 57) {
        return c - 48;
    }
    return -1;
}

void test3_19(){
    char *source = "6523+8*+3+*";
    stack stack = new_stack(10);
    
    for (int i = 0; i < strlen(source); i++) {
        char c = source[i];
        switch (c) {
            case '+':{
                int a = pop(stack);
                int b = pop(stack);
                push(stack, a + b);
                break;
            }
            case '-':{
                int a = pop(stack);
                int b = pop(stack);
                push(stack, a - b);
                break;
            }
            case '*':{
                int a = pop(stack);
                int b = pop(stack);
                push(stack, a * b);
                break;
            }
            case '/':{
                int a = pop(stack);
                int b = pop(stack);
                push(stack, a / b);
                break;
            }
            default:{
                int num = to_number(c);
                if (num != -1) {
                    push(stack, num);
                }
                break;
            }
        }
    }
    
    int result = pop(stack);
    printf("%d",result);
}

int is_pop(char new_one, char stack_top){
    //3  5  2  7  0  1
    //+  -  *  /  (  )
    int box[8] = {
        9, //0
        9, //1
        7, //2
        6, //3
        8, //4
        6, //5
        0, //6
        7, //7
    };
    if (new_one == '^') {
        if (stack_top != '^') {
            new_one = 44;
        }else{
            return 0;
        }
    }
    if (stack_top == '^') {
        stack_top = 44;
    }
    return box[new_one - 40] <= box[stack_top - 40] && stack_top != '(';
}

int do_symbol(char c, stack stack){
    switch (c) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case '^':
        {
            if (!empty(stack)) {
                char t = top(stack);
                while (!empty(stack) && is_pop(c, t)) {
                    printf("%c",t);
                    pop(stack);
                    t = top(stack);
                }
            }
            push(stack, c);
            return 1;
        }
        case ')':{
            if (!empty(stack)) {
                char t = top(stack);
                while (!empty(stack) && t != '(') {
                    printf("%c",t);
                    pop(stack);
                    t = top(stack);
                }
                pop(stack);
            }
            return 1;
        }
        default:{
            return 0;
        }
    }
}

void t3_20a(){
    char *source = "A+B*(C+D)-E/F";
    stack stack = new_stack(10);
    for (int i = 0; i < strlen(source); i++) {
        char c = source[i];
        if (do_symbol(c, stack) == 0) {
            printf("%c",c);
        }
    }
    while (!empty(stack)) {
        printf("%c",pop(stack));
    }
}
#endif

int lower(char last, char current){
    int box[8] = {
        9, //0
        9, //1
        7, //2
        6, //3
        0, //4
        6, //5
        0, //6
        7, //7
    };
    return box[last - 40] < box[current - 40];
}

int is_number(char c){
    return c >= 'a' && c <= 'z';
}

void test3_20(){
    char *source = "abc*+de*f+g*+";
    stack stack = new_stack(50);
    
    
    char last_symbol = '+';
    
    for (int i = 0; i < strlen(source); i++) {
        char c = source[i];
        if (is_number(c)) {
            char *tmp = malloc(2);
            tmp[0] = c;
            tmp[1] = '\0';
            //printf("push %s\n",tmp);
            push(stack, tmp);
        }else {
            char *b = pop(stack);
            char *a = pop(stack);
            //printf("pop %s\n",a);
            //printf("pop %s\n",b);
            //printf("last:%c current:%c %s\n",last_symbol, c, b);
            if (lower(last_symbol, c)) {
                if (strlen(a) != 1) {
                    char *tmp = malloc(strlen(a) + 3);
                    tmp[0] = '(';
                    memcpy(tmp + 1, a, strlen(a));
                    tmp[strlen(a) + 1] = ')';
                    tmp[strlen(a) + 2] = '\0';
                    free(a);
                    a = tmp;
                }else if (strlen(b) != 1){
                    char *tmp = malloc(strlen(b) + 3);
                    tmp[0] = '(';
                    memcpy(tmp + 1, b, strlen(b));
                    tmp[strlen(b) + 1] = ')';
                    tmp[strlen(b) + 2] = '\0';
                    free(b);
                    b = tmp;
                }
            }
            
            char *tmp = malloc(strlen(a) + strlen(b) + 2);
            memcpy(tmp, a, strlen(a));
            tmp[strlen(a)] = c;
            memcpy(tmp + strlen(a) + 1, b, strlen(b));
            tmp[strlen(a) + strlen(b) + 1] = '\0';
            //printf("push %s\n",tmp);
            push(stack, tmp);
            free(a);
            free(b);
            last_symbol = c;
        }
    }
    printf("%s\n",pop(stack));
}


























#endif
