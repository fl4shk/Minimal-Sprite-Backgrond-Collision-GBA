#ifndef level_loader_class_hpp
#define level_loader_class_hpp


#include "bg_reg_stuff.hpp"
#include "../misc_helper_stuff/array_2d_helper_class.hpp"
#include "block_stuff.hpp"

#define bg0_sbb 31


inline scr_entry horiz_level_tile_at ( u32 tile_x, u32 tile_y )
{
	//return the_block_ids_2d
	
	u32 block_x = tile_x >> 0x1, block_y = tile_y >> 0x1;
	
	u32 inner_block_x = tile_x & 0x1, inner_block_y = tile_y & 0x1;
	
	
	u32 block_data_array_index 
		= horiz_level_block_ids_2d.data_at ( block_x, block_y );
	
	block_type the_block_type 
		= block_data_array [block_data_array_index].get_block_type ();
	
	u32 the_metatile_id = get_metatile_number_of_block_type
		(the_block_type);
	
	
	
	
	// First inner row
	if ( inner_block_y == 0 )
	{
		if ( inner_block_x == 0 )
		{
			return (u16)( the_metatile_id * 4 );
		}
		else //if ( inner_block_x == 1 )
		{
			return (u16)( ( the_metatile_id * 4 ) + 1 );
		}
	}
	// Second inner row
	else //if ( inner_block_y == 1 )
	{
		if ( inner_block_x == 0 )
		{
			return (u16)( ( the_metatile_id * 4 ) + 2 );
		}
		else //if ( inner_block_x == 1 )
		{
			return (u16)( ( the_metatile_id * 4 ) + 3 );
		}
	}
	
}

inline u32 level_width_in_tiles 
	( array_2d_helper <u16>& the_block_ids_2d )
{
	return the_block_ids_2d.width () * 2;
}
inline u32 level_height_in_tiles 
	( array_2d_helper <u16>& the_block_ids_2d )
{
	return the_block_ids_2d.height () * 2;
}

void correct_bg0_scroll_mirror () __attribute__ ((_iwram_code));

void update_level_in_array_2d_helper
	( array_2d_helper <scr_entry>& the_array_2d_helper )
	__attribute__ ((_iwram_code));

void copy_level_from_array_2d_helper_to_vram
	( array_2d_helper <scr_entry>& bg0_screenblock_2d,
	array_2d_helper <scr_entry>& the_array_2d_helper )
	__attribute__ ((_iwram_code));




#endif		// level_loader_class_hpp
