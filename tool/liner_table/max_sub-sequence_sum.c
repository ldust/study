#include <stdio.h>
int main(int argc, const char * argv[]){
    int line;
    scanf("%d",&line);
    int i;
    for (i = 0; i < line; i++) {
        int num = 0;
        scanf("%d",&num);
        int max = -2000;
        int this = 0;
        
        int start = 1;
        int tryStart = 1;
        int end = 1;
        int index = 1;
        while (num-- > 0) {
            int n;
            scanf("%d", &n);
            
            if (this < 0) {
                this = n;
                tryStart = index;
            }else{
                this += n;
            }
            if (this > max) {
                max = this;
                end = index;
                start = tryStart;
            }
            index++;
        }
        printf("Case %d:\n%d %d %d\n",i + 1,max, start, end);
        if (i < line - 1) {
            printf("\n");
        }
    }
    return 0;
}

