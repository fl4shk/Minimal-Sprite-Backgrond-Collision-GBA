#include "bg_reg_stuff.hpp"


bg_point bgofs_mirror [bgofs_mirror_size];


void m4_line ( s32 x0, s32 y0, s32 x1, s32 y1, u32 color_id, u32 page )
{
	vec2_s32 delta, pixel_coord, offset;
	
	delta = { x1 - x0, y1 - y0 };
	
	if ( delta.x < 0 )
	{
		delta.x = -delta.x;
	}
	if ( delta.y < 0 )
	{
		delta.y = -delta.y;
	}
	
	pixel_coord = { x0, y0 };
	
	if ( x0 > x1 )
	{
		offset.x = -1;
	}
	else
	{
		offset.x = 1;
	}
	
	if ( y0 > y1 )
	{
		offset.y = -1;
	}
	else
	{
		offset.y = 1;
	}
	
	m4_plot ( pixel_coord.x, pixel_coord.y, color_id, page );
	
	if ( delta.x > delta.y )
	{
		s32 error = delta.x >> 1;
		
		while ( pixel_coord.x != x1 )
		{
			error -= delta.y;
			
			if ( error < 0 )
			{
				pixel_coord.y += offset.y;
				error += delta.x;
			}
			
			pixel_coord.x += offset.x;
			
			m4_plot ( pixel_coord.x, pixel_coord.y, color_id, page );
		}
		
	}
	else
	{
		s32 error = delta.y >> 1;
		
		while ( pixel_coord.y != y1 )
		{
			error -= delta.x;
			
			if ( error < 0 )
			{
				pixel_coord.x += offset.x;
				error += delta.y;
			}
			
			pixel_coord.y += offset.y;
			
			m4_plot ( pixel_coord.x, pixel_coord.y, color_id, page );
		}
		
	}
	
	
}


void m4_line_old ( s32 x0, s32 y0, s32 x1, s32 y1, u32 color_id )
{
	fixed24p8 delta_x, delta_y, error, delta_error;
	delta_x = make_f24p8 ( x1 - x0 );
	delta_y = make_f24p8 ( y1 - y0 );
	error = {0};
	
	// Handle horizontal and vertical lines separately
	// Vertical Line
	if ( delta_x == (fixed24p8){0} )
	{
		// Bottom to Top
		if ( delta_y < (fixed24p8){0} )
		{
			for ( s32 y=y1; y<y0; ++y )
			{
				m4_plot ( x0, y, color_id, 0 );
			}
		}
		
		// Top to Bottom
		else if ( delta_y > (fixed24p8){0} )
		{
			for ( s32 y=y0; y<y1; ++y )
			{
				m4_plot ( x0, y, color_id, 0 );
			}
		}
		
		return;
	}
	// Horizontal Line
	else if ( delta_y == (fixed24p8){0} )
	{
		// Right (x0) to Left (x1)
		if ( delta_x < (fixed24p8){0} )
		{
			for ( s32 x=x0; x>x1; --x )
			{
				m4_plot ( x, y0, color_id, 0 );
			}
		}
		
		// Left (x0) to Right (x1)
		if ( delta_x > (fixed24p8){0} )
		{
			for ( s32 x=x0; x<x1; ++x )
			{
				m4_plot ( x, y0, color_id, 0 );
			}
		}
		
		
		return;
	}
	
	//// Temporary!
	//delta_error.data = ( delta_y.data << 8 ) / delta_x.data;
	delta_error = delta_y / (fixed8p8)delta_x;
	
	if ( delta_error < (fixed24p8){0} )
	{
		delta_error = -delta_error;
	}
	
	s32 y = y0;
	
	for ( s32 x=x0; ; )
	{
		m4_plot ( x, y, color_id, 0 );
		
		error += delta_error;
		
		while ( error > (fixed24p8){0x80} )
		{
			m4_plot ( x, y, color_id, 0 );
			
			if ( delta_y < (fixed24p8){0} )
			{
				--y;
			}
			else if ( delta_y > (fixed24p8){0} )
			{
				++y;
			}
			
			error -= (fixed24p8){0x100};
		}
		
		if ( delta_x < (fixed24p8){0} )
		{
			--x;
			
			if ( x < x1 )
			{
				break;
			}
		}
		else if ( delta_x > (fixed24p8){0} )
		{
			++x;
			
			if ( x > x1 )
			{
				break;
			}
		}
	}
	
	
	
}

