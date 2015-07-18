#include "interrupt_stuff.hpp"
#include "bg_reg_stuff.hpp"


void irq_init ()
{
	//isr_main_counter = 0x0000;
	
	// Clear reg_ime (for safety or something)
	ime_disable ();
	
	
	
	// Clear reg_ie (for safety or something)
	reg_ie &= ~(irq_mask);
	
	
	// Now we enable VBlank Interrupts
	
	// Now we enable VBlank Interrupts in reg_ie
	reg_ie |= irq_vblank;
	
	// To do this, we also have to enable VBlank IRQs in reg_dispstat
	reg_dispstat |= dstat_vbl_irq;
	
	
	
	// Also, enable the timer1 interrupts
	reg_ie |= irq_timer1;
	
	
	// We will use isr_main () as the primary Interrupt Service Routine
	reg_isr_main = isr_main;
	
	
	// Set reg_ime
	ime_enable ();
	
}
