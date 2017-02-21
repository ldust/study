//
//  self_adjusting_table.h
//  tool
//
//  Created by Aily on 14-6-4.
//  Copyright (c) 2014年 Aily. All rights reserved.
//

#ifndef tool_self_adjusting_table_h
#define tool_self_adjusting_table_h

#include "pointer_double_list.h"

void sa_insert(list l, int v){
    insert(l, v);
}

position sa_find(list l, int v){
    position i = l->next;
    while (i != NULL) {
        if (i->value == v) {
            break;
        }
        i = i->next;
    }
    position i_p = i->front;
    position i_n = i->next;
    i_p->next = i_n;
    i_n->front = i_p;
    
    position l_n = l->next;
    l->next = i;
    i->front = l;
    i->next = l_n;
    l_n->front = i;
    
    return l->next;
}

void test3_15(){
    list l = new_list();
    
    for (int i = 0; i < 10; i++) {
        sa_insert(l, i);
    }
    
    
    printf("%d\n",sa_find(l, 6)->value);
    print(l);
}

#endif
