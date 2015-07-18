#ifndef oam_entry_classes_hpp
#define oam_entry_classes_hpp

#include "bg_reg_stuff.hpp"
#include "oam_entry_defines.hpp"
#include "dma_stuff.hpp"
#include "asm_funcs.hpp"
#include "../misc_helper_stuff/misc_bitwise_funcs.hpp"
#include "../misc_helper_stuff/fixed_classes.hpp"


class oam_entry;
class oam_entry_affine;

static const u32 oam_mirror_size = 128;
static const u32 oam_mirror_aff_size = 32;

extern oam_entry oam_mirror [oam_mirror_size];
#define oam_mirror_aff ( (oam_entry_affine*)(oam_mirror) )
//extern oam_entry_affine* const oam_mirror_aff;



// Regular OAM Entries, no affine transformations
class oam_entry
{
public:		// enums
	enum shape_size { ss_8x8, ss_16x16, ss_32x32, ss_64x64, ss_16x8, 
		ss_32x8, ss_32x16, ss_64x32, ss_8x16, ss_8x32, ss_16x32, 
		ss_32x64 };
	
public:		// variables
	u16 attr0;
	u16 attr1;
	u16 attr2;
	s16 fill;
	
public:		// wrapper functions
	
	s32 get_y_coord () const
	{
		return get_bits ( attr0, obj_attr0_y_coord_mask, 
			obj_attr0_y_coord_shift );
	}
	
	void set_y_coord ( s32 n_y_coord )
	{
		clear_and_set_bits ( attr0, obj_attr0_y_coord_mask,
			obj_attr0_y_coord ( n_y_coord ) );
	}
	
	s32 get_x_coord () const
	{
		return get_bits ( attr1, obj_attr1_x_coord_mask,
			obj_attr1_x_coord_shift );
	}
	
	void set_x_coord ( s32 n_x_coord )
	{
		clear_and_set_bits ( attr1, obj_attr1_x_coord_mask,
			obj_attr1_x_coord (n_x_coord) );
	}
	
	inline void show_non_affine ()
	{
		clear_bits ( attr0, 
			( obj_attr0_affine_mask | obj_attr0_disable_mask ) );
	}
	
	inline void hide_non_affine ()
	{
		clear_bits ( attr0, 
			( obj_attr0_affine_mask | obj_attr0_disable_mask ) );
		
		set_bits ( attr0, obj_attr0_disable_on );
	}
	
	inline void set_tile_number ( u32 n_tile )
	{
		clear_and_set_bits ( attr2, obj_attr2_tile_number_mask,
			obj_attr2_tile_number (n_tile) );
	}
	
	
	
	void set_shape_size ( shape_size n_shape_size );
	shape_size get_shape_size () const;
	
	void set_shape_size_with_vec2 ( const vec2_u32& n_shape_size );
	vec2_u32 get_shape_size_as_vec2 () const;
	
	
	
} __attribute__((_align4));



// A class for OAM Affine stuffs
// I could probably change every s16 member variable in this class to a
// fixed8p8, since that's basically what it's supposed to be.
class oam_entry_affine
{
public:		// variables
	static const u32 fill_size = 3;
	
	
	u16 fill0 [fill_size];
	fixed8p8 pa;
	
	u16 fill1 [fill_size];
	fixed8p8 pb;
	
	u16 fill2 [fill_size];
	fixed8p8 pc;
	
	u16 fill3 [fill_size];
	fixed8p8 pd;
	
public:		// functions
	
	
} __attribute__((_align4));



inline void copy_oam_mirror_to_oam ()
{
	//dma3_cpy ( (vu16*)(mem_oam), oam_mirror, 
	//	( oam_mirror_size * sizeof (oam_entry) ) / sizeof (u16), 0 );
	memcpy32 ( (void*)(mem_oam), oam_mirror,
		( oam_mirror_size * sizeof (oam_entry) ) / sizeof (u32) );
}



#endif		// oam_entry_classes_hpp
