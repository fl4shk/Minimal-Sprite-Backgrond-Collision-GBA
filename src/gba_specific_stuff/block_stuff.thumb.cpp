#include "block_stuff.hpp"

#include "bg_reg_stuff.hpp"
#include "dma_stuff.hpp"


block_base_stuff* block_stuff_array [bt_count]
= {
	new air_block_stuff,
	new log_block_stuff,
	new wood_block_stuff,
	new qmark_block_stuff,
	new exclam_block_stuff,
	new dud_block_stuff,
	
};

const u32 air_block_stuff::get_metatile_number ()
{
	return metatile_number;
}

const u32 log_block_stuff::get_metatile_number ()
{
	return metatile_number;
}

const u32 wood_block_stuff::get_metatile_number ()
{
	return metatile_number;
}

const u32 qmark_block_stuff::get_metatile_number ()
{
	return metatile_number;
}

const u32 exclam_block_stuff::get_metatile_number ()
{
	return metatile_number;
}

const u32 dud_block_stuff::get_metatile_number ()
{
	return metatile_number;
}



void update_block_graphics_in_vram ( const unsigned short* the_tiles )
{
	for ( u32 i=0; i<block_type::bt_count; ++i )
	{
		u32 graphics_slot = get_graphics_slot_of_block_type 
			( (block_type)i );
		u32 metatile_number = get_metatile_number_of_block_type
			( (block_type)i );
		
		dma3_cpy ( &( bg_tile_vram [graphics_slot * 16]), 
			&( the_tiles 
				[metatile_number * 16 * 4] ),
			16 * 4, 0 );
		
	}
}




u16 block_id_array [block_id_array_size] __attribute__ ((_ewram));

block block_data_array [block_data_array_size] 
	__attribute__ ((_ewram));

u16 extra_block_data_array [extra_block_data_array_size]
	__attribute__ ((_ewram));



array_2d_helper <u16> horiz_level_block_ids_2d ( block_id_array, 
	horiz_level_size_2d ) ;



