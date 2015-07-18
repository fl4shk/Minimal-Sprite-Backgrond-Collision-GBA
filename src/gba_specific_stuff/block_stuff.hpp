#ifndef block_stuff_hpp
#define block_stuff_hpp

#include "attribute_defines.hpp"
#include "../misc_helper_stuff/misc_types.hpp"
#include "../misc_helper_stuff/array_2d_helper_class.hpp"


enum block_type
{
	bt_air,
	bt_log,
	bt_wood,
	bt_qmark,
	bt_exclam,
	bt_dud,
	
	
	
	// bt_count is the amount of block types.  It is automatically updated
	// by the compiler.
	bt_count,
	
	
};

class block_base_stuff
{
public:		// variables
	
	
public:		// functions
	virtual const u32 get_metatile_number () = 0;
	
};

extern block_base_stuff* block_stuff_array [bt_count];


class air_block_stuff : public block_base_stuff
{
public:		// variables
	static const u32 metatile_number = 0;
	
public:		// functions
	virtual const u32 get_metatile_number () __attribute__ ((_iwram_code));
	
} __attribute__ ((_align4));


class log_block_stuff : public block_base_stuff
{
public:		// variables
	static const u32 metatile_number = 1;
	
public:		// functions
	virtual const u32 get_metatile_number () __attribute__ ((_iwram_code));
	
} __attribute__ ((_align4));


class wood_block_stuff : public block_base_stuff
{
public:		// variables
	static const u32 metatile_number = 2;
	
public:		// functions
	virtual const u32 get_metatile_number () __attribute__ ((_iwram_code));
	
} __attribute__ ((_align4));


class qmark_block_stuff : public block_base_stuff
{
public:		// variables
	static const u32 metatile_number = 3;
	
public:		// functions
	virtual const u32 get_metatile_number () __attribute__ ((_iwram_code));
	
} __attribute__ ((_align4));


class exclam_block_stuff : public block_base_stuff
{
public:		// variables
	static const u32 metatile_number = 4;
	
public:		// functions
	virtual const u32 get_metatile_number () __attribute__ ((_iwram_code));
	
} __attribute__ ((_align4));


class dud_block_stuff : public block_base_stuff
{
public:		// variables
	static const u32 metatile_number = 5;
	
public:		// functions
	virtual const u32 get_metatile_number () __attribute__ ((_iwram_code));
	
} __attribute__ ((_align4));






class block
{
public:		// variables
	
	u16 type;
	
	u16 extra_data_index;
	
	
public:		// functions
	
	inline block_type get_block_type () const
	{
		return (block_type)type;
	}
	
	
	
} __attribute__ ((_align4));



inline u32 get_metatile_number_of_block_type ( block_type the_block_type ) 
	__attribute__ ((always_inline));


inline u32 get_metatile_number_of_block_type ( block_type the_block_type )
{
	if ( the_block_type < 0 || the_block_type >= block_type::bt_count )
	{
		return block_stuff_array [bt_air]->get_metatile_number ();
	}
	else
	{
		return block_stuff_array [the_block_type]->get_metatile_number ();
	}
	
	//return block_stuff_array [the_block_type]->get_metatile_number ();
}



inline const u32 get_graphics_slot_of_block_type 
	( block_type the_block_type ) __attribute__ ((always_inline));


inline const u32 get_graphics_slot_of_block_type 
	( block_type the_block_type )
{
	// This assumes that EVERY block uses 4 graphics slots in VRAM
	return ( the_block_type * 4 );
}


void update_block_graphics_in_vram ( const unsigned short* the_tiles );



// This will eat up 32 kiB of EWRAM
static constexpr u32 block_id_array_size = 0x4000;
extern u16 block_id_array [block_id_array_size];

// This will eat up 24 kiB of EWRAM
static constexpr u32 block_data_array_size = 0x1800;
extern block block_data_array [block_data_array_size];

// This will eat up 8 kiB of EWRAM
static constexpr u32 extra_block_data_array_size = 0x1000;
extern u16 extra_block_data_array [extra_block_data_array_size];





static constexpr u32 horiz_level_size = block_id_array_size;
static constexpr u32 horiz_level_ysize = 0x20;
static constexpr u32 horiz_level_xsize = block_id_array_size 
	/ horiz_level_ysize;

static constexpr vec2_u32 horiz_level_size_2d 
	= { horiz_level_xsize, horiz_level_ysize };


extern array_2d_helper <u16> horiz_level_block_ids_2d;


inline vec2_s32 get_block_coord_of_point ( const vec2_f24p8& pt )
{
	vec2_s32 ret;
	
	ret.x = pt.x.round_to_int () / 16;
	ret.y = pt.y.round_to_int () / 16;
	
	return ret;
}


inline block_type get_block_type_at_coord ( const vec2_s32& block_coord )
{
	return block_data_array [horiz_level_block_ids_2d.data_at
		( block_coord.x, block_coord.y )].get_block_type ();
}

inline block_type get_block_type_at_coord ( const vec2_u32& block_coord )
{
	return block_data_array [horiz_level_block_ids_2d.data_at
		( block_coord.x, block_coord.y )].get_block_type ();
}

inline void get_block_type_and_block_coord_at_point ( const vec2_f24p8& pt, 
	vec2_s32& the_block_coord, block_type& the_block_type )
{
	the_block_coord = get_block_coord_of_point (pt);
	the_block_type = get_block_type_at_coord (the_block_coord);
}



#endif		// block_stuff_hpp
