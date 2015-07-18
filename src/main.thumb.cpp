#include "gba_specific_stuff/asm_funcs.hpp"

#include "gba_specific_stuff/button_stuff.hpp"
#include "gba_specific_stuff/bg_reg_stuff.hpp"
#include "gba_specific_stuff/oam_entry_classes.hpp"
#include "gba_specific_stuff/interrupt_stuff.hpp"
#include "gba_specific_stuff/bios_function_wrappers.hpp"
#include "gba_specific_stuff/dma_stuff.hpp"
#include "gba_specific_stuff/sound_reg_stuff.hpp"
#include "gba_specific_stuff/timer_stuff.hpp"
#include "gba_specific_stuff/sprite_class.hpp"



#include "misc_helper_stuff/fixed_classes.hpp"
#include "misc_helper_stuff/trigonometry_funcs.hpp"
#include "misc_helper_stuff/vec2_class.hpp"
#include "misc_helper_stuff/prev_curr_pair_class.hpp"
#include "misc_helper_stuff/array_2d_helper_class.hpp"
#include "misc_helper_stuff/misc_bitwise_funcs.hpp"
#include "misc_helper_stuff/debug_vars.hpp"

#include "gba_specific_stuff/level_loader_class.hpp"
#include "gba_specific_stuff/block_stuff.hpp"


#include "gfx/the_sprites.h"
#include "gfx/the_blocks.h"

//#include "test_level/test_level.hpp"


#include <stdlib.h>


scr_entry bg0_screenblock_mirror [screenblock_size] 
	__attribute__ ((_iwram));

int thing_thing_thing __attribute__ ((_iwram));


int main ()
{
	
	irq_init ();
	
	
	// Use video Mode 0, use 1D object mapping, enable forced blank, 
	// display objects, and display BG 0
	reg_dispcnt |= dcnt_mode0 | dcnt_obj_1d | dcnt_blank_on | dcnt_obj_on
		| dcnt_bg0_on;
	
	
	// Use screen base block 31 for BG0's Map
	reg_bg0cnt |= bgcnt_sbb (bg0_sbb);
	
	
	
	// Copy the sprite palettes to OBJ Palette RAM.
	memcpy32 ( obj_pal_ram, the_spritesPal, 
		the_spritesPalLen / sizeof (u32) );
	
	// Copy the sprite graphics to OBJ Video RAM.
	memcpy32 ( obj_tile_vram, the_spritesTiles,
		the_spritesTilesLen / sizeof (u32) );
	
	
	
	// Also, copy the_blocksPal to BG Palette RAM
	memcpy32 ( bg_pal_ram, the_blocksPal,
		the_blocksPalLen / sizeof (u32) );
	
	// Finally, copy the_blocksTiles to BG VRAM, screenblock 0
	update_block_graphics_in_vram (the_blocksTiles);
	
	
	array_2d_helper <scr_entry> bg0_screenblock_2d ( se_ram [bg0_sbb],
		screenblock_size_2d );
	
	array_2d_helper <scr_entry> bg0_screenblock_mirror_2d 
		( bg0_screenblock_mirror, screenblock_size_2d );
	
	
	
	block_data_array [1].type = bt_qmark;
	block_data_array [2].type = bt_log;
	block_data_array [3].type = bt_dud;
	block_data_array [4].type = bt_wood;
	block_data_array [5].type = bt_exclam;
	
	
	//for ( u32 i=0; i<horiz_level_block_ids_2d.width (); ++i )
	//{
	//	horiz_level_block_ids_2d.data_at ( i, 0 ) = 2;
	//	horiz_level_block_ids_2d.data_at ( i, 
	//		horiz_level_block_ids_2d.height () - 1 ) = 2;
	//}
	//for ( u32 j=0; j<horiz_level_block_ids_2d.height (); ++j )
	//{
	//	horiz_level_block_ids_2d.data_at ( 0, j ) = 2;
	//	horiz_level_block_ids_2d.data_at 
	//		( horiz_level_block_ids_2d.width (), j ) = 2;
	//}
	
	
	//for ( u32 j=0; j<horiz_level_block_ids_2d.height (); ++j )
	//{
	//	for ( u32 i=0; i<horiz_level_block_ids_2d.width (); ++i )
	//	{
	//		horiz_level_block_ids_2d.data_at ( i, j ) = 3;
	//	}
	//}
	
	
	memfill32 ( block_id_array, 0x00000000, 
		block_id_array_size * sizeof (u16) / sizeof (u32) );
	
	horiz_level_block_ids_2d.data_at ( 5, 3 ) = 2;
	horiz_level_block_ids_2d.data_at ( 6, 3 ) = 2;
	horiz_level_block_ids_2d.data_at ( 7, 3 ) = 2;
	horiz_level_block_ids_2d.data_at ( 8, 3 ) = 2;
	horiz_level_block_ids_2d.data_at ( 9, 3 ) = 2;
	
	horiz_level_block_ids_2d.data_at ( 5, 4 ) = 2;
	
	horiz_level_block_ids_2d.data_at ( 5, 8 ) = 2;
	
	
	
	update_level_in_array_2d_helper (bg0_screenblock_mirror_2d);
	
	copy_level_from_array_2d_helper_to_vram ( bg0_screenblock_2d,
		bg0_screenblock_mirror_2d );
	
	
	
	// Disable forced blank
	clear_bits ( reg_dispcnt, dcnt_blank_mask );
	
	sprite spr0;
	
	spr0.in_level_pos = { 0x2000, 0x2000 };
	
	spr0.the_oam_entry.set_tile_number (4);
	
	//spr0.set_shape_size (oam_entry::ss_16x16);
	//
	//spr0.the_coll_box.size = { make_f24p8 (16), make_f24p8 (16) };
	
	
	spr0.update_full ( bgofs_mirror [0] );
	
	
	
	fixed24p8 spr0_speed = {0x100};
	
	
	
	
	
	for (;;)
	{
		clear_debug_vars ();
		
		key_poll ();
		
		
		spr0.vel = { 0, 0 };
		
		
		if ( key_hit_or_held (key_left) )
		{
			spr0.vel.x = -spr0_speed;
		}
		
		else if ( key_hit_or_held (key_right) )
		{
			spr0.vel.x = spr0_speed;
		}
		
		if ( key_hit_or_held (key_up) )
		{
			spr0.vel.y = -spr0_speed;
		}
		
		else if ( key_hit_or_held (key_down) )
		{
			spr0.vel.y = spr0_speed;
		}
		
		spr0.update_f24p8_positions ();
		
		
		spr0.basic_collision_stuff ();
		
		
		
		
		bgofs_mirror [0].x = ( spr0.in_level_pos.x 
			- make_f24p8 ( screen_width / 2 ) ).round_to_int ();
		bgofs_mirror [0].y = ( spr0.in_level_pos.y 
			- make_f24p8 ( screen_height / 2 ) ).round_to_int ();
		
		correct_bg0_scroll_mirror ();
		
		
		spr0.update_on_screen_pos (bgofs_mirror [0]);
		
		
		spr0.copy_the_oam_entry_to_oam_mirror (0);
		
		
		
		update_level_in_array_2d_helper (bg0_screenblock_mirror_2d);
		
		
		
		bios_wait_for_vblank ();
		
		update_block_graphics_in_vram (the_blocksTiles);
		
		copy_oam_mirror_to_oam ();
		copy_bgofs_mirror_to_registers ();
		
		
		//update_level_in_array_2d_helper (bg0_screenblock_mirror_2d);
		
		copy_level_from_array_2d_helper_to_vram
			( bg0_screenblock_2d, bg0_screenblock_mirror_2d );
		
		
	}
	
	
	return 0;
}



