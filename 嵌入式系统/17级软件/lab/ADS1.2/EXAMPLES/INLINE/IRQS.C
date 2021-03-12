/* Example 4-2 */

/* Enabling and disabling interrupts */

/*
Interrupts are enabled or disabled by reading the cpsr flags and updating bit 7. 
This example shows how this can be done by using small functions that can be inlined. 
These functions work only in a privileged mode, because the control bits of the 
cpsr and spsr cannot be changed while in User mode.
*/

__inline void enable_IRQ(void)
{
    int tmp;
    __asm
    {
        MRS tmp, CPSR
        BIC tmp, tmp, #0x80
        MSR CPSR_c, tmp
    }
}

__inline void disable_IRQ(void)
{
    int tmp;
    __asm
    {
        MRS tmp, CPSR
        ORR tmp, tmp, #0x80
        MSR CPSR_c, tmp
    }
}

int main(void)
{
    disable_IRQ();
    enable_IRQ();
}

