#ifndef _MMU_H
#define _MMU_H

// L1 & L2 table structure
struct table_descriptor_stage1 {
    unsigned int valid            : 1;
    unsigned int type             : 1; // block 0, table 1 (only for L1 and L2)
    unsigned int ignored          : 10;
    unsigned long next_lvl_table  : 36;
    unsigned int res0             : 11;
    unsigned int pxn_table        : 1;
    unsigned int xn_table         : 1;
    unsigned int ap_table         : 2;
    unsigned int ns_table         : 1; // Most significant bit
}__attribute__((packed));

// L3 4k granularity table structure
struct page_descriptor_stage1 {
    unsigned valid           : 1;  // if a valid entry
    unsigned type            : 1;  // block 1, table 0 (only for L3)
    // lower attributes (bits 11:2)
    unsigned attrindx        : 3;  // stage 1 memory attr index field
    unsigned int ns          : 1;  // non-secure
    unsigned int ap          : 2;  // data access permissions
    unsigned int sh          : 2;  // sharability field
    unsigned int af          : 1;  // access flag
    unsigned int ng          : 1;  // not global flag
    // output address (bits 47:12)
    unsigned long int addr   : 36; // output addr for 4k granularity
    // reserved bits (bits 51:51)
    unsigned int res0        : 4;  // reserved
    // upper attributes (bits 63:52)
    unsigned int cont        : 1;  // if possibly in contiguous set of entries cached in single TLB entry
    unsigned int pxn         : 1;  // priveledged execute never
    unsigned int uxn         : 1;  // execute never
    unsigned int ignored     : 9;  // don't need to worry about this right now
}__attribute__((packed));

/*
    Stores physical addresses for the mmu, mmu page addresses are identity
    mapped to their own page tables for easier mapping.
*/
typedef struct {
    struct table_descriptor_stage1* L1_table;      
    struct ppage* used_pages; // list of pages being used for tables
} mmu_t;

static void no_mmu_kmap(void*, void*, struct table_descriptor_stage1*);
static void set_recursive_entry(void*, void*);
static void* init_kernel_ptable();

void mmu_init();

#endif


