#include "list.h"
#include "led.h"

extern long __bss_start, __bss_end; //https://sourceware.org/binutils/docs/ld/Source-Code-Reference.html
int i; //Or else there is no bss segment to clear

void bss_clear() {
    long * start = &__bss_start;
    long * end   = &__bss_end;

    while (start != end) {
        *start = 0;
        start++;
    }
}

void kernel_main() {
    struct list_element a = {0, 1};
    struct list_element b = {0, 2};
    struct list_element c = {0, 3};
    struct list_element d = {0, 4};
    struct list_element e = {0, 5};
	
    struct list_element* list = 0;    

    list_add(&a, &list);
    list_add(&b, &list);
    list_add(&c, &list);
    list_add(&d, &list);
    list_add(&e, &list);

    list_remove(5, &list); //Removes value 5 from the list
    list_remove(1, &list); //Removes value 1 from the list
    list_remove(3, &list); //Removes value 3 from the list

    led_init();
    while(1){
        led_on();

        delay(500);
        //for (int i = 0; i < 100000; ++i);
        
        led_off();
        delay(500);
        //for (int i = 0; i < 100000; ++i);
    }
}
