#include "sprite_class.hpp"

sprite::sprite ()
{
	
	in_level_pos = { 0, 0 };
	vel = { 0, 0 };
	the_oam_entry = { 0, 0, 0, 0 };
	
	set_shape_size (oam_entry::ss_16x16);
	
	the_coll_box.pos = { 0, 0 };
	the_coll_box.size = { make_f24p8 (16), make_f24p8 (16) };
	
	cb_pos_offset = { 0, 0 };
}

void sprite::update_on_screen_pos ( const bg_point& camera_pos )
{
	vec2_f24p8 on_screen_pos_f24p8;
	
	on_screen_pos_f24p8.x = ( in_level_pos.x - make_f24p8 (camera_pos.x) );
	on_screen_pos_f24p8.y = ( in_level_pos.y - make_f24p8 (camera_pos.y) );
	
	vec2_u32 ss_vec2 = get_shape_size_as_vec2 ();
	vec2_f24p8 offset;
	offset.x = make_f24p8 (ss_vec2.x);
	offset.y = make_f24p8 (ss_vec2.y);
	
	if ( on_screen_pos_f24p8.x + offset.x >= (fixed24p8){0} 
		&& on_screen_pos_f24p8.x <= make_f24p8 (screen_width)
		&& on_screen_pos_f24p8.y + offset.y >= (fixed24p8){0}
		&& on_screen_pos_f24p8.y <= make_f24p8 (screen_height) )
	{
		the_oam_entry.show_non_affine ();
			
		the_oam_entry.set_x_coord 
			( on_screen_pos_f24p8.x.round_to_int () );
		the_oam_entry.set_y_coord 
			( on_screen_pos_f24p8.y.round_to_int () );
	}
	else
	{
		// Hide the sprite if it's not on screen
		the_oam_entry.hide_non_affine ();
	}
}

extern int thing_thing_thing;

void sprite::basic_collision_stuff ()
{
	// The collision points
	vec2_f24p8 pt_lt, pt_lb,
		pt_tl, pt_tr,
		pt_rt, pt_rb,
		pt_bl, pt_br;
	
	pt_lt.x = pt_lb.x = the_coll_box.left ();
	pt_rt.x = pt_rb.x = the_coll_box.right ();
	
	pt_lt.y.data = pt_rt.y.data
		= the_coll_box.top ().data + ( the_coll_box.size.y.data / 4 );
	pt_lb.y.data = pt_rb.y.data
		= the_coll_box.bot ().data - ( the_coll_box.size.y.data / 4 );
	
	
	pt_tl.x.data = pt_bl.x.data 
		= the_coll_box.left ().data + ( the_coll_box.size.x.data / 4 );
	pt_tr.x.data = pt_br.x.data 
		= the_coll_box.right ().data - ( the_coll_box.size.x.data / 4 );
	
	pt_tl.y =  pt_tr.y = the_coll_box.top ();
	pt_bl.y =  pt_br.y = the_coll_box.bot ();
	
	
	// The blook coords of the collision points
	vec2_s32 lt_block_coord, lb_block_coord, tl_block_coord,
		tr_block_coord, rt_block_coord, rb_block_coord, bl_block_coord,
		br_block_coord;
	
	// The types of blocks intersected by the the collsion points
	block_type lt_block_type, lb_block_type, tl_block_type, tr_block_type, 
		rt_block_type, rb_block_type, bl_block_type, br_block_type;
	
	
	// Left side
	get_block_type_and_block_coord_at_point ( pt_lt, lt_block_coord, 
		lt_block_type );
	get_block_type_and_block_coord_at_point ( pt_lb, lb_block_coord,
		lb_block_type );
	
	// Top side
	get_block_type_and_block_coord_at_point ( pt_tl, tl_block_coord, 
		tl_block_type );
	get_block_type_and_block_coord_at_point ( pt_tr, tr_block_coord, 
		tr_block_type );
	
	// Right side
	get_block_type_and_block_coord_at_point ( pt_rt, rt_block_coord, 
		rt_block_type );
	get_block_type_and_block_coord_at_point ( pt_rb, rb_block_coord,
		rb_block_type );
	
	
	// Bottom side
	get_block_type_and_block_coord_at_point ( pt_bl, bl_block_coord, 
		bl_block_type );
	get_block_type_and_block_coord_at_point ( pt_br, br_block_coord, 
		br_block_type );
	
	if ( lt_block_type != bt_air || lb_block_type != bt_air )
	{
		in_level_pos.x = make_f24p8 ( ( lt_block_coord.x + 1 ) * 16 );
	}
	
	else if ( rt_block_type != bt_air || rb_block_type != bt_air )
	{
		in_level_pos.x = make_f24p8 ( ( rt_block_coord.x - 1 ) * 16 );
	}
	
	
	if ( tl_block_type != bt_air || tr_block_type != bt_air )
	{
		in_level_pos.y = make_f24p8 ( ( tl_block_coord.y + 1 ) * 16 );
	}
	
	else if ( bl_block_type != bt_air || br_block_type != bt_air )
	{
		in_level_pos.y = make_f24p8 ( ( bl_block_coord.y - 1 ) * 16 );
	}
	
	
	
}




vec2_u32 sprite::get_shape_size_as_vec2_raw () const
{
	
	switch (the_shape_size)
	{
		// Square shapes
		case oam_entry::ss_8x8:
			return { 8, 8 };
		case oam_entry::ss_16x16:
			return { 16, 16 };
		case oam_entry::ss_32x32:
			return { 32, 32 };
		case oam_entry::ss_64x64:
			return { 64, 64 };
		
		// Horizontal shapes
		case oam_entry::ss_16x8:
			return { 16, 8 };
		case oam_entry::ss_32x8:
			return { 32, 8 };
		case oam_entry::ss_32x16:
			return { 32, 16 };
		case oam_entry::ss_64x32:
			return { 64, 32 };
		
		// Vertical shapes
		case oam_entry::ss_8x16:
			return { 8, 16 };
		case oam_entry::ss_8x32:
			return { 8, 32 };
		case oam_entry::ss_16x32:
			return { 16, 32 };
		case oam_entry::ss_32x64:
			return { 32, 64 };
	}
	
}

