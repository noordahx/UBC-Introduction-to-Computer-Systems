#include "str_element.h"
#include "int_element.h"
#include "refcount.h"
#include <stdio.h>
#include <string.h>

struct str_element {
    struct str_element_class *class;
    char* str;
};

void str_print(struct element *thisv);
int str_compare(struct element *thisvOne, struct element *thisvTwo);
int is_str_element(struct element *thisv);
char* str_element_get_value(struct str_element *thisv);
struct str_element *str_element_new(char* thisv);
void str_finalizer(void *thisv);
struct str_element_class {
    void (*print)(struct element *);
    int (*compare)(struct element *, struct element *);
    int (*is_str_element)(struct element *);
    char* (*str_element_get_value)(struct str_element *);
    void (*finalizer)(void *);

};

struct str_element_class str_element_class = {str_print, str_compare, is_str_element, str_element_get_value,str_finalizer};

void str_print(struct element *thisv) {
    struct str_element *this = thisv;
    printf("%s", this->str);
}

int str_compare(struct element *thisvOne, struct element *thisvTwo) {
    struct str_element *thisOne = thisvOne;
    struct str_element *thisTwo = thisvTwo;
    if (!is_str_element(thisOne) && !is_str_element(thisTwo)) {
        struct int_element *intOne = thisOne;
        struct int_element *intTwo = thisTwo;
        return int_compare(intOne, intTwo);
    } else if (!is_str_element(thisOne) && is_str_element(thisTwo)) {
        return -1;
    } else if (is_str_element(thisOne) && !is_str_element(thisTwo)) {
        return 1;
    }
    return strcmp(str_element_get_value(thisOne), str_element_get_value(thisTwo));
}
int is_str_element(struct element *thisv) {
    struct str_element *this = thisv;
    if (this->class == &str_element_class) {
        return 1;
    }
    return 0;
}
char* str_element_get_value(struct str_element *thisv) {
    struct str_element* this = thisv;
    return this->str;
}
struct str_element *str_element_new(char* thisv) {
    struct str_element *this = rc_malloc(sizeof(struct str_element), str_finalizer);
    this->str = rc_malloc((strlen(thisv)+1), NULL);
    this->class = &str_element_class;
    strcpy(this->str, thisv);
    return this;
}

void str_finalizer(void *thisv) {
    struct str_element *this = thisv;
    rc_free_ref(this->str);
}