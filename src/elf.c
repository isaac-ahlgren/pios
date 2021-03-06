#include <stdbool.h>
#include <stdint.h>
#include "clib.h"
#include "elf.h"
#include "page.h"
#include "fat.h"
#include "list.h"
#include "mmu.h"

bool check_elf_magic(unsigned char* e_ident) {

    if (!e_ident) {
        return false;
    }
    
    return e_ident[EI_MAG0] == 0x7F && e_ident[EI_MAG1] == 'E'  &&
           e_ident[EI_MAG2] == 'L'  && e_ident[EI_MAG3] == 'F';
}

bool check_elf64_hdr(Elf64_Ehdr* hdr) {

    if (!check_elf_magic(hdr->e_ident)) {
        return false;
    }

    if (hdr->e_ident[EI_CLASS] != ELFCLASS64) {
	return false;
    }

    if (hdr->e_ident[EI_DATA] != ELFDATA2LSB) {
	return false;
    }
    
    if (hdr->e_ident[EI_OSABI] != ELFOSABI_SYSV) {
	return false;
    }

    if (hdr->e_type != ET_EXEC) {
	return false;
    }

    return true;
}       

bool elf_load_segments(Elf64_Ehdr*hdr, FILE* exec, struct ppage** pages) {

    Elf64_Phdr phdr[10]; // temporary buffer for program headers
    
    // change offset to place in file with program headers
    set_offset(exec, hdr->e_phoff);
    
    // map and allocate pages to loadable segments
    for (int i = 0; i < hdr->e_phnum; i++) {
    
        // if program header buffer empty or all read, read more
        if (!(i % 10)) { 
            read_file(exec, (unsigned char*) phdr, sizeof(Elf64_Phdr) * 10);
        }    
   
        Elf64_Phdr* prog_hdr = &phdr[i];
        
	// if segment is loadable
        if (prog_hdr->p_type == PT_LOAD) {

            // save and change offset to header's binary in the file
	    unsigned int offset = get_offset(exec);
	    set_offset(exec, prog_hdr->p_offset);
           
	    unsigned int pages_needed = prog_hdr->p_filesz / PAGE_SIZE + 1;
	    void* vaddr = (void*) prog_hdr->p_vaddr;
            struct ppage* new_page = 0;
            
	    // allocate and map necissary pages
	    for (int i = 0; i < pages_needed; i++) {
        
		// allocate page
                new_page = allocate_physical_pages(1);
                
		// check if page was allocated
	        if (!new_page) return false;
                
		// add to list of used pages
	        list_add((List_Element*) new_page, (List_Element**) pages);
                
		// map pages for mmu
	        kmap(vaddr, (void*)new_page->physical_addr);

                // read needed bytes into page
                unsigned int bytes_needed = (i*PAGE_SIZE > prog_hdr->p_filesz) ? prog_hdr->p_filesz % PAGE_SIZE : PAGE_SIZE;
	        read_file(exec, (unsigned char*) vaddr, bytes_needed);
                
		// next vaddr for next page
	        vaddr += PAGE_SIZE;
            }

            // set difference between memsize and filesize to 0
            memset(vaddr + prog_hdr->p_filesz, 0, prog_hdr->p_memsz - prog_hdr->p_filesz);
            
	    // return offset to previous
	    set_offset(exec, offset);
	}
    }
    
    return true;
}    	   

bool exec(char* path, char* argv[]) {
    
    Elf64_Ehdr elf_header;
    FILE exec;
    struct ppage* pages_used = 0;

    if (!file_open(&exec, path)) {
        return false;
    }    
    
    // read header
    read_file(&exec, (unsigned char*) &elf_header, sizeof(Elf64_Ehdr));
    
    // check header
    if (!check_elf64_hdr(&elf_header)) {
	return false;
    }
    
    // load segments
    if (!elf_load_segments(&elf_header, &exec, &pages_used)) {
        free_physical_pages(pages_used);
        return false;
    }

    // allocate stack space
    struct ppage* stack = allocate_physical_pages(1);

    // check if page was allocated
    if (!stack) {
        free_physical_pages(pages_used);
        return false;
    }

    // add to list of used pages
    list_add((List_Element*) stack, (List_Element**) &pages_used);

    // map pages for mmu
    kmap((void*)stack->physical_addr, (void*)stack->physical_addr);

    // stack pointer starts from high addresses then goes lower
    // stack pointer is aligned on the 16 byte boundary
//    uint64_t stack_pointer = (uint64_t) ((stack->physical_addr + PAGE_SIZE - 1) & ~15LL);

    uint64_t entry_point   = (uint64_t) elf_header.e_entry;
    
//    uint64_t program_status = 0x3c0;

    // EL issue, don't fully understand how aarch64 works with EL for this

//    asm volatile ("br %0" : : "r" (entry_point)); 

    // set up registers for context switch
//    asm volatile ("msr sp_el0, %0" : : "r" (stack_pointer));

//    asm volatile ("msr elr_el1, %0" : : "r" (entry_point));

//    asm volatile ("msr spsr_el1, %0" : : "r" (program_status));

    asm volatile ("br %0" : : "r" (entry_point));

//    asm volatile ("eret");
    
    return true;
    
}        
