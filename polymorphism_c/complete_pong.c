#include <stdlib.h>
#include <stdio.h>

/**** class A ****/

void A_ping(void *this_v);
void A_pong(void *this_v);

struct A_class {
    int s;
    void (*ping)(void *this_v);
    void (*pong)(void *this_v);
} A_class_table = {1234, A_ping, A_pong};

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

void A_pong(void *this_v) {
    struct A *this = this_v;
    printf("A_pong s=%d i=%d\n", A_class_table.s, this->i);
}


/**** class B extends A ****/

void B_ping(void *this_v);

struct B_class {
    int s;
    void (*ping)(void *this_v);
    void (*pong)(void *this_v);
} B_class_table = {4567, B_ping, A_pong};

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
        a->class->pong(a);
    }
}