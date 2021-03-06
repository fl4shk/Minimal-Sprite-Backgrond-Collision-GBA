#ifndef trigonometry_funcs_hpp
#define trigonometry_funcs_hpp

#include "fixed_classes.hpp"

extern "C"
{

static const u32 sin_table_size = 512;
extern const s16 sin_table [sin_table_size];

};


static const u32 trig_lut_fixed_shift = 12;

// NOTE:  theta's range is [0, 0xffff] for [0,2π), just like the BIOS
// functions.  Also, the returned value has a fixed-point shift of 12.

// Look up a sine value
inline s32 lut_sin ( u32 theta )
{
	return sin_table [ ( theta >> 7 ) & 0x1ff ];
}

// Look up a cosine value
inline s32 lut_cos ( u32 theta )
{
	return sin_table [ ( ( theta >> 7 ) + 128 ) & 0x1ff ];
}


//x = y = 20;
//
//x += ( 4 * lut_cos (theta) ) >> trig_lut_fixed_shift; 
//y += ( 4 * lut_sin (theta) ) >> trig_lut_fixed_shift;


inline fixed24p8 lut_sin_f24p8 ( u32 theta )
{
	return (fixed24p8){ lut_sin (theta) 
		>> ( trig_lut_fixed_shift - fixed24p8::shift ) };
}

inline fixed24p8 lut_cos_f24p8 ( u32 theta )
{
	return (fixed24p8){ lut_cos (theta) 
		>> ( trig_lut_fixed_shift - fixed24p8::shift ) };
}


inline fixed8p8 lut_sin_f8p8 ( u32 theta )
{
	return (fixed8p8){ (s16)( lut_sin (theta) 
		>> ( trig_lut_fixed_shift - fixed8p8::shift ) ) };
}

inline fixed8p8 lut_cos_f8p8 ( u32 theta )
{
	return (fixed8p8){ (s16)( lut_cos (theta) 
		>> ( trig_lut_fixed_shift - fixed8p8::shift ) ) };
}



#endif		// trigonometry_funcs_hpp
