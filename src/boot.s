// AArch64 mode
 
.section ".kernel-header"

// Kernel Header
// See https://www.kernel.org/doc/Documentation/arm64/booting.txt
b _start          /* CODE0 : Executable code */
.word 0           /* CODE1 : Executable code */
.dword _start     /* text_offset : Image load offset, little endian */
.dword 0x0        /* image_size : Image load offset, little endian */
.dword 0x2        /* flags */
.dword 0x0        /* reserved */
.dword 0x0        /* reserved */
.dword 0x0        /* reserved */
.dword 0x644d5241 /* magic */
.dword 0x0        /* reserved */

// To keep this in the first portion of the binary.
.section ".text.boot"
 
// To keep this in the first portion of the binary.
.section ".text.boot"
 
// Make _start global.
.globl _start
 
// Entry point for the kernel. Registers:
// x0 -> 32 bit pointer to DTB in memory (primary core only) / 0 (secondary cores)
// x1 -> 0
// x2 -> 0
// x3 -> 0
// x4 -> 32 bit kernel entry point, _start location
_start:

    mrs x1, mpidr_el1
    and x1,x1,#3
    cbz x1, maincore

notmaincore: // CPU id > 0: stop
    wfi
    b notmaincore

maincore:
    // Set stack before our code
    ldr     x5, =_start
    
    /* Set up EL1 */
    mrs	    x0, CurrentEL
    and     x0, x0, #12   // Clear bits

    // If running EL3
    cmp     x0, #12
    bne     1f
    mov     x2, #0x5b1
    msr     scr_el3, x2   // Set Secure Configuration Register
    mov     x2, #0x3c9
    msr     spsr_el3, x2  // Set EL3 Save Process Status
    adr     x2, 2f
    msr     elr_el3, x2
    eret

    // If running El2
1:  cmp     x0, #4
    beq     2f
    msr     sp_el1, x5
    msr     sp_el0, x5
    // Configure Events
    mrs     x0, cnthctl_el2
    orr     x0, x0, #3
    msr     cnthctl_el2, x0
    msr     cntvoff_el2, xzr
    // Enable AArch64
    mov     x0, #(1 << 31)
    orr     x0, x0, #(1 << 1)
    msr     hcr_el2, x0
    mrs     x0, hcr_el2 

    // Change execution level to EL1
    mov     x2, #0x3c4
//    mov     x2, #0x3c0 
    msr     spsr_el2, x2
    adr     x2, 2f
    msr     elr_el2, x2
    eret    

2:  mov     sp, x5

    ldr     x2, =_vectors_el1
    msr     vbar_el1, x2
 
    // clear bss
    bl       bss_clear
    
    // start mmu
    //bl       mmu_on
 
    // jump to C code, should not return
    bl      kernel_main
