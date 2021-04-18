#ifndef _ELF_H
#define _ELF_H

#include <stdint.h>

/*
 * Reference For Specifications Used:
 *     https://www.uclibc.org/docs/elf-64-gen.pdf
 */

typedef uint16_t Elf64_Half;	// unsigned half int
typedef uint64_t Elf64_Off;	// unsigned offset
typedef uint64_t Elf64_Addr;	// unsigned address
typedef uint32_t Elf64_Word;	// unsigned int
typedef int32_t  Elf64_Sword;	// signed int
typedef uint64_t Elf64_Xword;   // unsigned long integer
typedef int64_t  Elf64_Sxword;   // unsigend long integer

typedef struct {

    unsigned char e_ident[16]; // ELF identification
    Elf64_Half    e_type;      // object file type
    Elf64_Half    e_machine;   // machine tpye
    Elf64_Word    e_version;   // object file version
    Elf64_Addr    e_entry;     // entry point address
    Elf64_Off     e_phoff;     // program header offset
    Elf64_Off     e_shoff;     // section header offset
    Elf64_Word    e_flags;     // processor-specific flags
    Elf64_Half    e_ehsize;    // ELF header size
    Elf64_Half    e_phentsize; // size of program header entry
    Elf64_Half    e_phnum;     // number of program header entries
    Elf64_Half    e_shentsize; // size of section header entry
    Elf64_Half    e_shnum;     // number of section header entry
    Elf64_Half    e_shstrndx;  // sectionname string table index
    
} Elf64_Ehdr;

// ELF identification
#define EI_MAG0        0
#define EI_MAG1        1
#define EI_MAG2        2
#define EI_MAG3        3
#define EI_CLASS       4
#define EI_DATA        5
#define EI_VERSION     6
#define EI_OSABI       7
#define EI_ABIVERSION  8
#define EI_PAD         9
#define EI_NIDENT     16

// file clases
#define ELFCLASS32     1
#define ELFCLASS64     2

// data encoding
#define ELFDATA2LSB    1
#define ELFDATA2MSB    2

// ABI identifiers
#define ELFOSABI_STANDALONE 255 
                                     
// ELF types
#define ET_NONE        0
#define ET_REL         1
#define ET_EXEC        2
#define ET_DYN         3
#define ET_CORE        4

typedef struct {

    Elf64_Word    sh_name;      // section name
    Elf64_Word    sh_type;      // section type
    Elf64_Xword   sh_flags;     // section attributes
    Elf64_Addr    sh_addr;      // virtual address
    Elf64_Off     sh_offset;    // offset in file
    Elf64_Xword   sh_size;      // size of section
    Elf64_Word    sh_link;      // link to other section
    Elf64_Word    sh_info;      // miscellaneous info
    Elf64_Xword   sh_addralign; // address alignment boundary
    Elf64_Xword   sh_entsize;   // size of entry, if section had table

} Elf64_Shdr;

// section types
#define SHT_NULL         0
#define SHT_PROGBITS     1
#define SHT_SYMTAB       2
#define SHT_STRTAB       3
#define SHT_RELA         4
#define SHT_HASH         5
#define SHT_DYNAMIC      6
#define SHT_NOTE         7
#define SHT_NOBITS       8

// section attributes
#define SHF_WRITE        0x1
#define SHF_ALLOC        0x2
#define SHF_EXECINSTR    0x4

typedef struct {

    Elf64_Word    p_type;    // type of segment
    Elf64_Word    p_flags;   // segment atributes
    Elf64_Off     p_offset;  // offset in file
    Elf64_Addr    p_vaddr;   // virtual address
    Elf64_Xword   p_filesz;  // size of segment in file
    Elf64_Xword   p_memsz;   // size of segment in memory
    Elf64_Xword   p_align;   // alignment of segment

} Elf64_Phdr;

// segment types
#define PT_NULL    0
#define PT_LOAD    1
#define PT_DYNAMIC 2
#define PT_INTERP  3
#define PT_NOTE    4
#define PT_SHLIB   5
#define PT_PHDR    6
#define PT_LOOS    0x60000000
#define PT_HIOS    0x6fffffff

// segment attributes
#define PF_X       0x1
#define PF_W       0x2
#define PF_R       0x4

bool exec(char*, char* argv[]);
    
#endif
