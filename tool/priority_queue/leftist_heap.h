//
//  leftist_heap.h
//  tool
//
//  Created by Approx on 14-6-30.
//  Copyright (c) 2014年 Aily. All rights reserved.
//

#ifndef tool_leftist_heap_h
#define tool_leftist_heap_h

#include <stdlib.h>
#include <stdio.h>

#define simpleRandom(from,to)  ((random() % (to + 1 - from)) + from)


void test(){
    int namebox[105];
    for (int i = 0; i < 105; i++) {
        namebox[i] = 0;
    }
    
    for (int k = 0; k < 100; k++) {
        int box[10];
        int have = 0;
        for (int i = 0; i < 10; i++) {
            box[i] = simpleRandom(1, 105);
            if (box[i] == 5) {
                have = 1;
            }
            namebox[box[i]]++;
        }
        if (!have) {
            namebox[box[0]]--;
            namebox[5]++;
        }
    }
    for (int i = 0; i < 105; i++) {
        printf("%d\n",namebox[i]);
    }
    
}


#endif
