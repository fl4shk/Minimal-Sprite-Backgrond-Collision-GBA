#include "level_loader_class.hpp"


void correct_bg0_scroll_mirror ()
{
	s16 level_x_coord_tile = bgofs_mirror [0].x >> 3;
	s16 level_y_coord_tile = bgofs_mirror [0].y >> 3;
	
	
	if ( level_x_coord_tile < 0 )
	{
		bgofs_mirror [0].x = 0;
	}
	
	else if ( level_x_coord_tile 
		> (s16)(level_width_in_tiles (horiz_level_block_ids_2d) 
		- screen_width_in_tiles - 1 ) )
	{
		bgofs_mirror [0].x = ( level_width_in_tiles
			(horiz_level_block_ids_2d)
			* num_pixels_per_tile_row_or_column )
			- screen_width;
	}
	
	
	
	if ( level_y_coord_tile < 0 )
	{
		bgofs_mirror [0].y = 0;
	}
	
	else if ( level_y_coord_tile 
		> (s16)(level_height_in_tiles (horiz_level_block_ids_2d)
		- screen_height_in_tiles -1 ) )
	{
		bgofs_mirror [0].y = ( level_height_in_tiles
			(horiz_level_block_ids_2d)
			* num_pixels_per_tile_row_or_column )
			- screen_height;
	}
}


void update_level_in_array_2d_helper
	( array_2d_helper <scr_entry>& the_array_2d_helper )
{
	correct_bg0_scroll_mirror ();
	
	s16 level_x_coord_tile = bgofs_mirror [0].x >> 3;
	s16 level_y_coord_tile = bgofs_mirror [0].y >> 3;
	
	
	for ( u32 i=0; i<screen_width_in_tiles + 1; ++i )
	{
		for ( u32 j=0; j<screen_height_in_tiles + 1; ++j )
		{
			the_array_2d_helper.data_at 
				( ( level_x_coord_tile + i ) & 0x1f,
				( level_y_coord_tile +j ) & 0x1f )
			= horiz_level_tile_at ( level_x_coord_tile + i, 
				level_y_coord_tile + j );
		}
	}
	
}


void copy_level_from_array_2d_helper_to_vram
	( array_2d_helper <scr_entry>& bg0_screenblock_2d,
	array_2d_helper <scr_entry>& the_array_2d_helper )
{
	memcpy32 ( bg0_screenblock_2d.the_array, 
		the_array_2d_helper.the_array,
		sizeof (scr_entry) * the_array_2d_helper.get_size () 
			/ sizeof (u32) ); 
}

