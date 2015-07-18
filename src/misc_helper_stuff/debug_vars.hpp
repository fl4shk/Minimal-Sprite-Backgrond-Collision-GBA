#ifndef debug_vars_hpp
#define debug_vars_hpp

#include "misc_types.hpp"
#include "../gba_specific_stuff/attribute_defines.hpp"
#include "coll_box_class.hpp"
#include "fixed_classes.hpp"



extern u32 cur_debug_s32_index, cur_debug_u32_index, cur_debug_f24p8_index,
	cur_debug_f8p8_index, cur_debug_st_result_index
	__attribute__ ((_iwram));


static const u32 debug_arr_s32_size = 32;
extern vs32 debug_arr_s32 [debug_arr_s32_size] __attribute__ ((_iwram));
#define next_debug_s32 ( debug_arr_s32 [cur_debug_s32_index++] )


static const u32 debug_arr_u32_size = 32;
extern vu32 debug_arr_u32 [debug_arr_u32_size] __attribute__ ((_iwram));
#define next_debug_u32 ( debug_arr_u32 [cur_debug_u32_index++] )


static const u32 debug_arr_f24p8_size = 32;
extern fixed24p8 debug_arr_f24p8 [debug_arr_f24p8_size] 
	__attribute__ ((_iwram));
#define next_debug_f24p8 ( debug_arr_f24p8 [cur_debug_f24p8_index++] )


static const u32 debug_arr_f8p8_size = 32;
extern fixed8p8 debug_arr_f8p8 [debug_arr_f8p8_size] 
	__attribute__ ((_iwram));
#define next_debug_f8p8 ( debug_arr_f8p8 [cur_debug_f8p8_index++] )


void clear_debug_vars () __attribute__ ((_iwram_code));


#endif		// debug_vars_hpp
