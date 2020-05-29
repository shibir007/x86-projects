#include <stdio.h>
#include <stdint.h>

int main(){
	uint32_t max_EAX_val_4_CPUID;
        uint8_t vendorStr[13];
	uint8_t *bytePtr = (char *)bytes;


        __asm__("movl  %1, %%edi\n"       // Store the start addr of string (bytePtr) in EDI
                "movl $0, %%eax\n"        // Initialize EAX with 0, required for cpuid
                "cpuid\n"
                "movl %%eax, %0\n"        // Copy result (EAX) to max_EAX_val_4_CPUID
                "movl %%ebx,(%%edi)\n"    // Copy first word of "Genuine Intel" to EBX
                "movl %%edx,4(%%edi)\n"   // Copy first word of "Genuine Intel" to EDX
                "movl %%ecx,8(%%edi)"     // Copy first word of "Genuine Intel" to ECX
               :"=r"(max_EAX_val_4_CPUID) // %0 - output
               :"r"(bytePtr)		  // %1 - input 
               :"cc");

	bytes[12] = 0;
	printf("max EAX val supported for CPUID cmd = %#x\nvendor string = %s\n", max_EAX_val_4_CPUID, vendorStr);
	return 0;
}
