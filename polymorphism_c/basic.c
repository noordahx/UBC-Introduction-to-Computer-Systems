#include <stdlib.h>
#include <stdio.h>

// A class jump table
struct A_class {
    void (*ping)();
};
// procedure ping
void A_ping();
// jump table A
struct A_class A_class_table = {A_ping};

struct A {
    struct A_class *class;
};

struct A *new_A() {
    struct A *a = malloc(sizeof(*a));
    a->class = &A_class_table;
    return a;
};

void A_ping() {
    printf("A_ping\n");
}

int main() {
    struct A *a = new_A();
    a->class->ping();
}