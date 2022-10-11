#include <stdlib.h>
#include <stdio.h>

int main() {
    int a[10] = { 14, 46, 14, 40, 14, 34, 20, 31, 35, 36 };
    printf("%d", &a[6] - &a[4]);
}