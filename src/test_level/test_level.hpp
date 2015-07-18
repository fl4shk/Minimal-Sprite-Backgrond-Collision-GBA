#ifndef test_level_hpp
#define test_level_hpp

#include "../misc_helper_stuff/misc_types.hpp"
#include "../gba_specific_stuff/bg_reg_stuff.hpp"
#include "../misc_helper_stuff/array_2d_helper_class.hpp"



static constexpr u32 test_level_size = 0x800;
static constexpr u32 test_level_xsize = 0x40, test_level_ysize = 0x20;
static constexpr vec2_u32 test_level_size_2d 
	= { test_level_xsize, test_level_ysize };

extern const u32 test_level_block_ids [test_level_size];


extern array_2d_helper <const u32> test_level_block_ids_2d;



#endif		// test_level_hpp
