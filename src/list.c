#include "list.h"

/*
 * Inserts element into list before given element
 */
void list_insert_before(struct list_element* new, struct list_element* list) {
    
    // change pointer for previous of new and list nodes
    new->prev = list->prev;
    list->prev = new;
    
    // if list node has a prev pointer, make that node point to new
    if (new->prev) {
        new->prev->next = new;
    }    
    
    // make the next in new node the list node
    new->next = list;    
}

/*
 * Inserts element into list after given element
 */
void list_insert_after(struct list_element* new, struct list_element* list) {
    
    // change pointer for previous of new and list nodes
    new->next = list->next;
    list->next = new;
    
    // if list node has a prev pointer, make that node point to new
    if (new->next) {
        new->next->prev = new;
    }    
    
    // make the next in new node the list node
    new->prev = list;    
}

/*
 * Unlinks element from list
 */

void list_unlink(struct list_element* ele) {

    // disconnect node from list
    if (ele->next) {
        ele->next->prev = ele->prev;
    }    
    if (ele->prev) {
        ele->prev->next = ele->next;
    }
    
    // set pointers to null
    ele->prev = 0;
    ele->next = 0;
    
}    
 

/*
 * Adds an individual element to head of
 * linked list.
 */
void list_add(struct list_element* new, struct list_element** head) {

    struct list_element* list = *head;
    
    if (list) {
        list_insert_before(new, list);
    }
    else {
        new->next = 0;
    }        
    
    // set list double pointer to new pointer
    *head = new;

}     

/*
 * Removes head of linked list and returns it
 */
struct list_element* list_remove(struct list_element** head) {

    struct list_element* ret = 0;
    struct list_element* remove = *head;

    if (remove) {
        
        // set head to next;
        *head = remove->next;
        
        list_unlink(remove);    
	
	// set return vlaue
	ret = remove;
	       
    }
    
    return ret;
        
}
