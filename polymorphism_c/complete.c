#include <stdlib.h>
#include <stdio.h>

/**
 * TODO: Add pong, implemented by class A and inherited by class B
 * (1) impleent A_pong by copying A_ping
 * (2) add to A_class and the initialization of A_class_table
 * (3) add a call to main and test for an instance of A_class
 * (4) add to B_class and the initialization of B_class_table
 * (5) test for an instance of B_class
 */

 

/**** class A ****/

void A_ping(void *this_v);

struct A_class {
    int s;
    void (*ping)(void *this_v);
} A_class_table = {1234, A_ping};

struct A {
    struct A_class *class;
    int i;
};

void A_ctor(void *this_v, int i) {
    struct A* this = this_v;
    this->i = i;
}

void *new_A(int i) {
    struct A *a = malloc(sizeof(*a));
    a->class = &A_class_table;
    A_ctor(a, i);
    return a;
};

void A_ping(void *this_v) {
    struct A *this = this_v;
    printf("A_ping s=%d i=%d\n", A_class_table.s, this->i);
}


/**** class B extends A ****/

void B_ping(void *this_v);

struct B_class {
    int s;
    void (*ping)(void *this_v);
} B_class_table = {4567, B_ping};

struct B {
    struct B_class *class;
    int i;
};

void B_ctor(void *this_v, int i) {
    struct B *this = this_v;
    A_ctor(this, i);
}

void *new_B(int i) {
    struct B *b = malloc(sizeof(*b));
    b->class = &B_class_table;
    B_ctor(b, i);
    return b;
}

void B_ping(void* this_v) {
    struct B *this = this_v;
    printf("B_ping s=%d i=%d\n", B_class_table.s, this->i);
}


/**** main ****/

int main() {
    for (int i=0; i<2; i++) {
        struct A *a;
        if (i==0)
            a = new_A(i+100);
        else
            a = new_B(i+100);
        a->class->ping(a);
    }
}