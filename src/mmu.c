

#include "pbase.h"
#include "page.h"
#include "common.h"
#include "mmu.h"

/*
    Pages allocated to the MMU for tables shall be identity mapped in order to
    simplify the process of distinguishing between virtual and physical addresses.
    The MMU has a granularity of 4k at the L3 level. However, 2M blocks of memory
    can be mapped at the L2 level.

    38              30  29              21  20              12 11                  0
    |------------------|-------------------|------------------|--------------------|
    | L1 table entry   |  L2 table entry   | L3 table entry   |      Offset        |
    |------------------|-------------------|------------------|--------------------|

*/

mmu_t current_pagetable;

// only supports 4k page mapping at the moment
void map_pages(void *vaddr, void *paddr) {

    struct table_descriptor_stage1* L1_table = current_pagetable.L1_table;
    struct table_descriptor_stage1* L2_table = current_pagetable.L2_table_list;
    struct page_descriptor_stage1*  L3_table = current_pagetable.L3_table_list; 

    unsigned long int L3_index = ((unsigned long int) vaddr >> 12) & 0x1ff;
    unsigned long int L2_index = ((unsigned long int) vaddr >> 21) & 0x1ff;
    unsigned long int L1_index = ((unsigned long int) vaddr >> 30) & 0x1ff;

    // place in L1 table
    L1_table[L1_index].valid = 1;
    L1_table[L1_index].type = 1;
    L1_table[L1_index].next_lvl_table = ((unsigned long int)L2_table) >> 12;

    // place in L2 table
    L2_table[L2_index].valid = 1;
    L2_table[L2_index].type = 1;
    L2_table[L2_index].next_lvl_table = ((unsigned long int)L3_table) >> 12;
    
    // place in L3 table
    L3_table[L3_index].valid = 1;
    L3_table[L3_index].attrindx = 0;
    L3_table[L3_index].type = 1;
    L3_table[L3_index].sh = 3;
    L3_table[L3_index].ap = 0;
    L3_table[L3_index].af = 1;
    L3_table[L3_index].addr = (unsigned long int) paddr >> 12;
    
}

void mmu_init() {

    // initialize page table
    struct ppage* pages = allocate_physical_pages(3); // possible liability if not identity mapped
    current_pagetable.used_pages = pages;
    current_pagetable.L1_table = (struct table_descriptor_stage1*) pages->physical_addr;
    pages = pages->next;
    current_pagetable.L2_table_list = (struct table_descriptor_stage1*) pages->physical_addr;
    pages = pages->next;
    current_pagetable.L3_table_list = (struct page_descriptor_stage1*) pages->physical_addr;
    
    // identity map kernel code
    for (unsigned long int addr = 0x0; addr < &__end; addr += PAGE_SIZE) {
         map_pages((void*)addr, (void*)addr);
    }

   // mapPages(PBASE+0x00300000,PBASE+0x00300000); // map SD card addresses
   // mapPages(PBASE+0x215000,PBASE+0x215000);     // map aux addresses
   // mapPages(PBASE+0x200000,PBASE+0x200000);     // map gpio addresses
    
    // set page table, control registers, and start mmu

    unsigned long b, r;
   
    asm volatile ("mrs %0, id_aa64mmfr0_el1" : "=r" (r));
    b=r&0xF;
 
    // first, set Memory Attributes array, indexed by PT_MEM, PT_DEV, PT_NC in our example
    r=  (0xFF << 0) |    // AttrIdx=0: normal, IWBWA, OWBWA, NTR
        (0x04 << 8) |    // AttrIdx=1: device, nGnRE (must be OSH too)
        (0x44 <<16);     // AttrIdx=2: non cacheable

    asm volatile ("msr mair_el1, %0" : : "r" (r));

    // next, specify mapping characteristics in translate control register
    r=  (0b00LL << 37) | // TBI=0, no tagging
        (b << 32) |      // IPS=autodetected
        (0b10LL << 30) | // TG1=4k
        (0b11LL << 28) | // SH1=3 inner
        (0b01LL << 26) | // ORGN1=1 write back
        (0b01LL << 24) | // IRGN1=1 write back
        (0b0LL  << 23) | // EPD1 enable higher half
        (25LL   << 16) | // T1SZ=25, 3 levels (512G)
        (0b00LL << 14) | // TG0=4k
        (0b11LL << 12) | // SH0=3 inner
        (0b01LL << 10) | // ORGN0=1 write back
        (0b01LL << 8) |  // IRGN0=1 write back
        (0b0LL  << 7) |  // EPD0 enable lower half
        (25LL   << 0);   // T0SZ=25, 3 levels (512G)

    asm volatile ("msr tcr_el1, %0; isb" : : "r" (r));


    // tell the MMU where our translation tables are. TTBR_CNP bit not documented, but required
    // lower half, user space
    asm volatile ("msr ttbr0_el1, %0" : : "r" ((unsigned long) current_pagetable.L1_table));

    // finally, toggle some bits in system control register to enable page translation
    asm volatile ("dsb ish; isb; mrs %0, sctlr_el1" : "=r" (r));

    r|=0xC00800;     // set mandatory reserved bits
    r&=~((1<<25) |   // clear EE, little endian translation tables
         (1<<24) |   // clear E0E
         (1<<19) |   // clear WXN
         (1<<12) |   // clear I, no instruction cache
         (1<<4) |    // clear SA0
         (1<<3) |    // clear SA
         (1<<2) |    // clear C, no cache at all
         (1<<1));    // clear A, no aligment check
    r|=  (1<<0);     // set M, enable MMU

    asm volatile ("msr sctlr_el1, %0; isb" : : "r" (r));
        
}



