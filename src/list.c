#include "list.h"

void list_add(struct list_element* new, struct list_element** head) {

    if (!new || !head) return;

    //Appends to beginning assuming order never matters
    if (*head) (*head)->prev = new;
    new->next = *head;
    *head = new;
    
}

void list_remove(struct list_element* ele) {

    if (ele) {
        
        if (ele->next)
	    ele->next->prev = ele->prev;
	if (ele->prev)
	    ele->prev->next = ele->next;
        
	ele->next = 0;
	ele->prev = 0;
    }
        
}
