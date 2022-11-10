#include <stdio.h>

int x[8] = {1,2,3,-1,-2,0,184,340057058};
int y[8] = {0,0,0,0,0,0,0,0};

int f(int val) {\
    int returnval = 0;
    while (val != 0) {
        if (val < 0) {
            returnval++;
        }
        val*=2;
    }
    return returnval;
}

int main() {
    int i = 8;
    while (i != 0) {
        i--;
        y[i] = f(x[i]);
    }

    for (int i = 0; i < 8; i++) {
        printf("%d\n",x[i]);
    }

    for (int i = 0; i < 8; i++) {
        printf("%d\n",y[i]);
    }
}