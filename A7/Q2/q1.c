#include <stdio.h>
int array[10] = {0,0,0,0,0,0,0,0,0,0};

int add_store(int a, int b) {
    array[b] = array[b] + a;
}


int main() {
    int a, b, c, d;
    a = 1;
    b = 2;
    c = 3;
    d = 4;
    add_store(c, d);
    add_store(a, b);

    for (int i = 0; i < 10; i++) {
        printf("%d ",array[i]);
    }
}