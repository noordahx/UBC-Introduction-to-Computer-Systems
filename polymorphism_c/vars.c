#include <stdlib.h>
#include <stdio.h>

/**
 * TODO: Add an instance variable
 * (1) add an instance variable "i",
 * (2) add a parameter to the "constructor" to initialize it,
 * (3) PAUSE to consider how to print the value of "i" in A_ping ... we will discuss this together
 * (4) implenent "this" and use it to print the value of "i" in A_ping
 */


struct A_class {
    int s;
    void (*ping)(void*);
};

void A_ping(void*);
struct A_class A_class_table = {1234, A_ping};

struct A {
    struct A_class *class;
    int i;
};

struct A *new_A(int val) {
    struct A *a = malloc(sizeof(*a));
    a->class = &A_class_table;
    a->i = val;
    return a;
};

void A_ping(void* this_v) {
    struct A* a = this_v;
    printf("A_ping s=%d\n", A_class_table.s);
    printf("A_ping i=%d ", a->i);
}

int main() {
    struct A *a = new_A(4);
    a->class->ping(a);
}