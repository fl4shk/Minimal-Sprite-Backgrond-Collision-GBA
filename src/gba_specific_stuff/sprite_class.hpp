#ifndef sprite_class_hpp
#define sprite_class_hpp


#include "bg_reg_stuff.hpp"
#include "oam_entry_defines.hpp"
#include "dma_stuff.hpp"
#include "asm_funcs.hpp"
#include "../misc_helper_stuff/misc_bitwise_funcs.hpp"
#include "block_stuff.hpp"

#include "oam_entry_classes.hpp"

#include "../misc_helper_stuff/coll_box_class.hpp"

#include "../misc_helper_stuff/debug_vars.hpp"

class sprite
{
protected:		// variables
	vec2_u32 the_shape_size_vec2;
	oam_entry::shape_size the_shape_size;
	
public:		// variables
	// in_level_pos is the "global" position of the sprite within the
	// current level.
	vec2_f24p8 in_level_pos;
	
	vec2_f24p8 vel;
	
	oam_entry the_oam_entry;
	
	// the_coll_box's "pos" member variable is the in-level coordinate
	coll_box the_coll_box;
	
	
	
	// cb_pos_offset is the position of the coll_box relative to
	// in_level_pos.
	vec2_f24p8 cb_pos_offset;
	
	
public:		// functions
	
	sprite ();
	inline oam_entry::shape_size get_shape_size () const
	{
		return the_shape_size;
	}
	inline const vec2_u32& get_shape_size_as_vec2 () const
	{
		return the_shape_size_vec2;
	}
	
	inline void set_shape_size ( oam_entry::shape_size n_shape_size )
	{
		the_shape_size = n_shape_size;
		the_oam_entry.set_shape_size (n_shape_size);
		the_shape_size_vec2 = get_shape_size_as_vec2_raw ();
	}
	
	inline void update_f24p8_positions ()
	{
		in_level_pos += vel;
		the_coll_box.pos = in_level_pos + cb_pos_offset;
		
		vel = { 0, 0 };
	}
	
	void update_on_screen_pos ( const bg_point& camera_pos );
	
	inline void update_full ( const bg_point& camera_pos )
	{
		//in_level_pos += vel;
		//the_coll_box.pos = in_level_pos + cb_pos_offset;
		
		update_f24p8_positions ();
		
		update_on_screen_pos (camera_pos);
	}
	
	
	inline void copy_the_oam_entry_to_oam_mirror 
		( u32 slot_for_oam_mirror )
	{
		oam_mirror [slot_for_oam_mirror].attr0 = the_oam_entry.attr0;
		oam_mirror [slot_for_oam_mirror].attr1 = the_oam_entry.attr1;
		oam_mirror [slot_for_oam_mirror].attr2 = the_oam_entry.attr2;
	}
	
	virtual void basic_collision_stuff ();
	
	
protected:		// functions
	vec2_u32 get_shape_size_as_vec2_raw () const;
	
	
} __attribute__ ((_align4));





#endif		// sprite_class_hpp
