#ifndef interrupt_stuff_hpp
#define interrupt_stuff_hpp

#include "../misc_helper_stuff/misc_types.hpp"
#include "memory_map.hpp"
#include "attribute_defines.hpp"
#include "dma_stuff.hpp"
#include "timer_stuff.hpp"


// The Interrupt Enable Register (R/W)
#define reg_ie *((vu16*)(mem_io + 0x0200))

// The Interrupt Request Flags/IRQ Acknowledge Register (R/W)
#define reg_if *((vu16*)(mem_io + 0x0202))

// The Interrupt Master Enable Register (R/W)
#define reg_ime *((vu32*)(mem_io + 0x0208))


/* ---- Defines for the flags of IE and IF ---- */
#define irq_vblank ( 0x1 << 0x0 )
#define irq_hblank ( 0x1 << 0x1 )
#define irq_vcount ( 0x1 << 0x2 )

#define irq_timer0 ( 0x1 << 0x3 )
#define irq_timer1 ( 0x1 << 0x4 )
#define irq_timer2 ( 0x1 << 0x5 )
#define irq_timer3 ( 0x1 << 0x6 )

#define irq_com ( 0x1 << 0x7 )

#define irq_dma0 ( 0x1 << 0x8 )
#define irq_dma1 ( 0x1 << 0x9 )
#define irq_dma2 ( 0x1 << 0xa )
#define irq_dma3 ( 0x1 << 0xb )

#define irq_keypad ( 0x1 << 0xc )

#define irq_gamepak ( 0x1 << 0xd )

#define irq_mask ( (u16)(0x3fff) )
/* ---- End of Defines for the flags of IE and IF ---- */


/* ---- Inline Functions for IME ---- */
inline void ime_disable ()
{
	reg_ime = 0x0000;
}

inline void ime_enable ()
{
	reg_ime = 0x0001;
}
/* ---- End of Inline Functions for IME ---- */


// Function Pointer for Interrupt Service Routines
typedef void (*isr_funcptr)(void);

// This is a pointer to the main ISR (an ARM mode function btw), which MUST
// be set properly for interrupts to work!
#define reg_isr_main *((volatile isr_funcptr*)(mem_iwram + 0x7ffc))

// Some BIOS calls require interrupts, which have to be acknowledged by
// using this register (I still think it's weird that there are registers
// in what I thought was IWRAM).
#define reg_ifbios *((vu16*)(mem_iwram + 0x7ff8))


void irq_init ();


void isr_main () __attribute__((_iwram_code));

//#define isr_main_counter *((vu16*)(mem_ewram + 0x8000))
//#define isr_main_arr0 ((vu16*)(mem_ewram + 0x8002))
//static const u32 isr_main_arr0_size = 0x20;



#endif		// interrupt_stuff_hpp
