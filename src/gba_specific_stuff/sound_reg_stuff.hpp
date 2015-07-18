#ifndef sound_reg_stuff_hpp
#define sound_reg_stuff_hpp


#include "../misc_helper_stuff/misc_types.hpp"
#include "attribute_defines.hpp"
#include "memory_map.hpp"



// DMA Sound Control/Mixing (R/W)
#define reg_soundcnt_h		*((vu16*)(mem_io + 0x82))

// Sound on/off (R/W)
#define reg_soundcnt_x		*((vu16*)(mem_io + 0x84 ))


// Sound A FIFO, Data 0 and Data 1 (W)
#define reg_fifo_a_l		*((vu16*)(mem_io + 0xa0))
// Sound A FIFO, Data 2 and Data 3 (W)
#define reg_fifo_a_h		*((vu16*)(mem_io + 0xa2))


// Sound B FIFO, Data 0 and Data 1 (W)
#define reg_fifo_b_l		*((vu16*)(mem_io + 0xa4))
// Sound B FIFO, Data 2 and Data 3 (W)
#define reg_fifo_b_h		*((vu16*)(mem_io + 0xa6))




// Defines for reg_soundcnt_h

// 25% Volume for the GBC-compatible channels
#define channel_gbc_vol_25				( 0x0 << 0 )
// 50% Volume
#define channel_gbc_vol_50				( 0x1 << 0 )
// 100% Volume
#define channel_gbc_vol_100				( 0x2 << 0 )

#define channel_gbc_vol_mask			( 0x0003 )


// DMA Sound A Volume

// 50% Volume for DMA Sound A
#define dma_sound_a_vol_50				( 0x0 << 2 )
// 100% Volume
#define dma_sound_a_vol_100				( 0x1 << 2 )

#define dma_sound_a_vol_mask			( 0x0004 )



// DMA Sound B Volume

// 50% Volume for DMA Sound B
#define dma_sound_b_vol_50				( 0x0 << 3 )
// 100% Volume
#define dma_sound_b_vol_100				( 0x1 << 3 )

#define dma_sound_b_vol_mask			( 0x0008 )



// DMA Sound A RIGHT (For stereo sound)
#define dma_sound_a_right_disable		( 0x0 << 8 )
#define dma_sound_a_right_enable		( 0x1 << 8 )

#define dma_sound_a_right_mask			( 0x0100 )


// DMA Sound A LEFT (For stereo sound)
#define dma_sound_a_left_disable		( 0x0 << 9 )
#define dma_sound_a_left_enable			( 0x1 << 9 )

#define dma_sound_a_left_mask			( 0x0200 )



// DMA Sound A Timer Select (Timer 0 or Timer 1)
#define dma_sound_a_use_timer_0			( 0x0 << 10 )
#define dma_sound_a_use_timer_1			( 0x1 << 10 )

#define dma_sound_a_timer_select_mask	( 0x0400 )


// DMA Sound A Reset FIFO
#define dma_sound_a_reset_fifo			( 0x1 << 11 )





// DMA Sound B RIGHT (For stereo sound)
#define dma_sound_b_right_disable		( 0x0 << 12 )
#define dma_sound_b_right_enable		( 0x1 << 12 )

#define dma_sound_b_right_mask			( 0x1000 )


// DMA Sound B LEFT (For stereo sound)
#define dma_sound_b_left_disable		( 0x0 << 13 )
#define dma_sound_b_left_enable			( 0x1 << 13 )

#define dma_sound_b_left_mask			( 0x2000 )



// DMA Sound B Timer Select (Timer 0 or Timer 1)
#define dma_sound_b_use_timer_0			( 0x0 << 14 )
#define dma_sound_b_use_timer_1			( 0x1 << 14 )

#define dma_sound_b_timer_select_mask	( 0x4000 )


// DMA Sound A Reset FIFO
#define dma_sound_b_reset_fifo			( 0x1 << 15 )




// FIFO Master Switch for reg_soundcnt_x
#define sound_fifo_disable				( 0x0 << 7 )
#define sound_fifo_enable				( 0x1 << 7 )





#endif		// sound_reg_stuff_hpp
