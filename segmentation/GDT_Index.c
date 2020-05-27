/*
 * Note: Segment registers are called selectors when operating in protected mode.
 *       In protected mode, segment registers simply point to data structures 
 *       called segment descriptors that contain the information needed to access
 *       a physical memory location.
 *        --------------------
 *       |   Index     |TI|RPL|
 *        --------------------
 *       15            3  2   0
 *
 *       Index:  13-bit field selects one of 8,192 segment descriptors.
 *       TI:     (table indicator) specifies segment descriptor (GDT/LDT)
 *       RPL:    (requestor privilege level) 2-bit field, specifies if the access to 
 *               the segment is allowed. 0 being highest privilege(kernel mode), 3 being
 *               lowest (user mode)
 *
 * Platform: x86
 * Compiler: gcc/clang
 */


#include <stdint.h>
#include <stdio.h>

void printSegReg(char* name, uint16_t value) {
    printf("%8s|%#8x|%8s|%#8x\n",
           name,
           (value & 0xFFF8) >> 3,
           (value & 0x4) ? "LDT" : "GDT", 
           (value & 0x3));
}

int main() {

    uint16_t CS, DS, ES, FS, GS, SS;

    //
    // copying all the 16-bit segment register 
    // to the respective variables
    //
    __asm__( 
            "mov %%cs,%0\n"
            "mov %%ds,%1\n"
            "mov %%es,%2\n"
            "mov %%fs,%3\n"
            "mov %%gs,%4\n"
            "mov %%ss,%5\n"
            :"=r" (CS), "=r" (DS), "=r" (ES), "=r" (FS), "=r" (GS), "=r" (SS));

    printf("-------------------------------------\n");
    printf("Register|   Index| GDT/LDT|     RPL\n");
    printf("-------------------------------------\n");
    printSegReg("CS", CS);
    printSegReg("SS", SS);
    printSegReg("DS", DS);
    printSegReg("ES", ES);
    printSegReg("FS", FS);
    printSegReg("GS", GS);

    return 0;
}

