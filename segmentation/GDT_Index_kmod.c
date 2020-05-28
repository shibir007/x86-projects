/*
 * GDT_Index_kmod.c - A simple kernel module to dump the segment selecters and decode them
 *
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


#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <asm-generic/int-ll64.h>

void printSegReg(char* name, u16 value) {
    printk("%8s|%#8x|%8s|%#8x\n",
           name,
           (value & 0xFFF8) >> 3,
           (value & 0x4) ? "LDT" : "GDT", 
           (value & 0x3));
}

int init_module(void)
{
    u16 _CS, _DS, _ES, _FS, _GS, _SS;

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
            :"=r" (_CS), "=r" (_DS), "=r" (_ES), "=r" (_FS), "=r" (_GS), "=r" (_SS));

    printk("-------------------------------------\n");
    printk("Register|   Index| GDT/LDT|     RPL\n");
    printk("-------------------------------------\n");
    printSegReg("CS", _CS);
    printSegReg("SS", _SS);
    printSegReg("DS", _DS);
    printSegReg("ES", _ES);
    printSegReg("FS", _FS);
    printSegReg("GS", _GS);

    return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "Module exiting..\n");
}
