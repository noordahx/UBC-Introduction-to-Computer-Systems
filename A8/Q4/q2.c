#include <stdio.h>
#include <stdlib.h>


int q2 (int a, int b, int c) {
    int value = 0;
    switch(a - 10) {
        case 0:
            value = b + c;
            break;
        case 1:
            value = 0;
            break;
        case 2:
            value = b - c;
            break;
        case 3:
            value = 0;
            break;
        case 4:
            value = (b > c)? 1 : 0;
            break;
        case 5:
            value = 0;
            break;
        case 6:
            value = (c > b)? 1 : 0;
            break;
        case 7:
            value = 0;
            break;
        case 8:
            value = (b == c)? 1 : 0;
            break;
        default:
            value = 0;
            break;
    }
    return value;
}


int main() {
    printf("10 = a %d \n", q2(10, 1, 2));
    printf("11 = b %d \n", q2(11, 1, 2));
    printf("12 = c %d \n", q2(12, 1, 2));
    printf("13 = d %d \n", q2(13, 1, 2));
    printf("14 = e %d \n", q2(14, 1, 2));
    printf("15 = f %d \n", q2(15, 1, 2));
    printf("16 = 10 %d \n", q2(16, 1, 2));
    printf("17 = 11 %d \n", q2(17, 1, 2));
    printf("18 = 12 %d \n", q2(18, 1, 2));
    printf("19 = 13 %d \n", q2(19, 1, 2));
}