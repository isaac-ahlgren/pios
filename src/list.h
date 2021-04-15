#ifndef _LIST_H
#define _LIST_H

typedef struct list_element {
    struct list_element *next;
    struct list_element *prev;
    void* payload;
} List_Element;

void list_insert_before(struct list_element*, struct list_element*);
void list_insert_after(struct list_element*, struct list_element*);
void list_unlink(struct list_element*);
void list_add(struct list_element*, struct list_element**);
struct list_element* list_remove(struct list_element**);

#endif
