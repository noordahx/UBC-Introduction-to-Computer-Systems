#include "int_element.h"
#include "refcount.h"
#include <stdio.h>
#include "str_element.h"
#include <string.h>

struct int_element {
    struct int_element_class *class;
    int value;
};


struct int_element_class {
    void (*print)(struct element *);
    int (*compare)(struct element *, struct element *);
    int (*int_element_get_value)(struct int_element *);
    int (*is_int_element)(struct element *);
};
void int_print(struct element *thisv);
int int_compare(struct element *thisvOne, struct element *thisvTwo);
int int_element_get_value(struct int_element *thisv);
int is_int_element(struct element *thisv);
struct int_element_class int_element_class = {int_print, int_compare, int_element_get_value, is_int_element};

void int_print(struct element *thisv) {
    struct int_element *this = thisv;
    printf("%d", this->value);
}

int int_compare(struct element *thisvOne, struct element *thisvTwo) {
    struct int_element *thisOne = thisvOne;
    struct int_element *thisTwo = thisvTwo;
    if (!is_int_element(thisOne) && !is_int_element(thisTwo)) {
        struct str_element *strOne = thisOne;
        struct str_element *strTwo = thisTwo;
        return strcmp(str_element_get_value(strOne), str_element_get_value(strTwo));
    } else if (!is_int_element(thisOne) && is_int_element(thisTwo)) {
        return 1;
    } else if (is_int_element(thisOne) && !is_int_element(thisTwo)) {
        return -1;
    }
    if (thisOne->value > thisTwo->value)
        return 1;
    else if (thisOne->value < thisTwo->value) 
        return -1;
    else 
        return 0;
}
int is_int_element(struct element *thisv) {
    struct int_element *this = thisv;
    if (this->class == &int_element_class)
        return 1;
    else 
        return 0;
}
int int_element_get_value(struct int_element *thisv) {
    struct int_element *this = thisv;
    return this->value;
}


struct int_element* int_element_new(int value) {
    struct int_element *obj = rc_malloc(sizeof(struct int_element), NULL);
    obj->class = &int_element_class;
    obj->value = value;
    return obj;
}