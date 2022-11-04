#include <stdlib.h>
#include <stdio.h>

/**** class A ****/

void A_ping();

struct A_class {
    void (*ping)();
} A_class_table = {A_ping};

struct A {
    struct A_class *class;
};

void *new_A() {
    struct A *a = malloc(sizeof(*a));
    a->class = &A_class_table;
    return a;
};

void A_ping() {
    printf("A_ping\n");
}


/**** class B extends A ****/

void B_ping();

struct B_class {
    void (*ping)();
} B_class_table = {B_ping};

struct B {
    struct B_class *class;
};

void *new_B() {
    struct B *b = malloc(sizeof(*b));
    b->class = &B_class_table;
    return b;
}

void B_ping() {
    printf("B_ping\n");
}


/**** main ****/

int main() {
    for (int i=0; i<2; i++) {
        struct A *a;
        if (i==0)
            a = new_A();
        else
            a = new_B();
        a->class->ping();
    }
}