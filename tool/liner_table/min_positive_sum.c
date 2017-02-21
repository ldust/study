#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void minpositive(){
    int line;
    scanf("%d",&line);
    for (int x = 0; x < line; x++) {
        int num;
        scanf("%d",&num);
        int *box = malloc(sizeof(int) * num);
        int i = 0;
        while (i < num) {
            scanf("%d", box + i++);
        }
        
        int *sumbox = malloc(sizeof(int) * (num + 1));
        int sum = 0;
        sumbox[0] = 0;
        for (int i = 1; i < num + 1; i++) {
            sum += box[i - 1];
            sumbox[i] = sum;
        }
        
        int minsub = 2000;
        
        for (int i = 1; i < num + 1; i++) {
            for (int j = 0; j < i; j++) {
                int current = sumbox[i] - sumbox[j];
                if (current < minsub && current > 0) {
                    printf("%d %d\n",i, j);
                    minsub = current;
                }
            }
        }
        
        printf("%d\n",minsub);
        free(sumbox);
        free(box);
    }
}

struct numberSet{
    int value;
    int order;
};

int cmp(const void *a, const void *b){
    struct numberSet *sa = (struct numberSet *)a;
    struct numberSet *sb = (struct numberSet *)b;
    return sa->value - sb->value;
}

void newminpositivesum(){
    int line;
    scanf("%d",&line);
    for (int x = 0; x < line; x++) {
        int num;
        scanf("%d",&num);
        int *box = malloc(sizeof(int) * num);
        int i = 0;
        while (i < num) {
            scanf("%d", box + i++);
        }
        
        struct numberSet *sumbox = malloc(sizeof(struct numberSet) * (num + 1));
        int sum = 0;
        sumbox[0].value = 0;
        sumbox[0].order = 0;
        
        for (int i = 1; i < num + 1; i++) {
            sum += box[i - 1];
            sumbox[i].value = sum;
            sumbox[i].order = i;
        }
        qsort(sumbox, num + 1, sizeof(struct numberSet), cmp);
        
        int min = 2000;
        for (int i = 0; i < num; i++) {
            int minus = sumbox[i + 1].value - sumbox[i].value;
            if (minus < min && minus > 0 && sumbox[i + 1].order > sumbox[i].order) {
                min = minus;
            }
        }
        printf("%d\n",min);
        free(sumbox);
        free(box);
    }
}

void max(){
    
}

int main(int argc, const char * argv[]){
    int n = 12;
    
    while (n) {
        if (n & 1)
            printf("1");
        else
            printf("0");
        
        n >>= 1;
    }
    printf("\n");
    
    //minpositive();
    newminpositivesum();
    return 0;
}

