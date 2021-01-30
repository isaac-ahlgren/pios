#include "list.h"

int list_add(struct list_element* new, struct list_element** head) {

    if (!new || !head) return 0;

    new->next = *head; //Assuming order does not matter
    *head = new;
    
    return 1;
}

int list_remove(int val, struct list_element** head) {
    int ret = 0;

    if (!head) return ret;

    struct list_element* n = *head;

    if (n->val == val) { //Case if first is val
        *head = n->next;
        ret = 1;
    }

    while (!ret && n->next) { //Normal Case

        if (val == n->next->val) {
            n->next = n->next->next;
            ret = 1;
            break;
        }
        n = n->next;
    }
    
    return ret;
}