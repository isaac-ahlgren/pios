#ifndef _LIST_H
#define _LIST_H

struct list_element {
    struct list_element *next;
    int val;
};

int list_add(struct list_element*, struct list_element**);
int list_remove(int val, struct list_element**);

#endif