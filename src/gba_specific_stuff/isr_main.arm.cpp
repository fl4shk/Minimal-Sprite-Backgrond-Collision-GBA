#include "interrupt_stuff.hpp"
#include "bg_reg_stuff.hpp"
//#include "bg_helper_class.hpp"


// This function is currently only intended to service the VBlank
// interrupt.  I'll probably add support for other interrupts later on.
void isr_main ()
{
	
	// Before we leave this function, we have to acknowledge that VBlank
	// IRQ was serviced.
	if ( reg_if & irq_vblank )
	{
		// Acknowledge the VBlank interrupt.
		reg_ifbios = irq_vblank;
		reg_if = irq_vblank;
	}
	
	
	// Timer 1 and its corresponding interrupt are used to count played
	// samples.  When Timer 1 is done, we need to disable DMA1 and Timer 0.
	// As usual, we also need to acknowledge that the IRQ was serviced. 
	else if ( reg_if & irq_timer1 )
	{
		// The sound stuff is finished.  Stop the Direct Sound.
		// Disable Timer 0
		reg_tm0cnt_h = 0;
		// Disable DMA1
		reg_dma1cnt = 0;
		
		
		// Acknowledge the Timer 1 interrupt.
		//reg_ifbios = irq_timer1;
		reg_if = irq_timer1;
		
	}
	
	
}
