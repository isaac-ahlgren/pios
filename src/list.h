#ifndef _LIST_H
#define _LIST_H

struct list_element {
    struct list_element *next;
    struct list_element *prev;
    void* payload;
};

void list_add(struct list_element*, struct list_element**);
void list_remove(struct list_element*);

#endif
