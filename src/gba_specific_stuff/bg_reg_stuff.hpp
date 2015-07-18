#ifndef bg_reg_stuff_hpp
#define bg_reg_stuff_hpp

#include "../misc_helper_stuff/misc_types.hpp"
#include "memory_map.hpp"
#include "../misc_helper_stuff/vec2_class.hpp"


/* ---- Some Helper Structs ---- */

// ---- Character/Tile Stuffs ----
// tile 8x8@4bpp:  32 bytes; 8 ints
struct tile
{
	static const u32 arrsize = 8;
	u32 data [arrsize];
};
typedef tile tile4;

// d-tile:  double-sized tile (8bpp)
struct tile8
{
	static const u32 arrsize = 16;
	u32 data [arrsize];
};


static const u32 charblock_size = 0x200;
typedef tile charblock [charblock_size];

static const u32 charblock8_size = 0x100;
typedef tile8 charblock8 [charblock8_size];

#define tile_ram		( (charblock*)(mem_vram) )
#define tile8_ram		( (charblock8*)(mem_vram) )


#define bg_tile_vram ( (vu16*)(tile_ram [0]) )
#define obj_tile_vram ( (vu16*)(tile_ram [4]) )

// ---- End of Character/Tile Stuffs ----


// ---- Screen-Entry Stuffs ----

// Screen entry conceptual typedef
typedef u16 scr_entry;

// Regular map offsets
//struct bg_point
//{
//	//s16 x, y;
//	u16 x, y;
//} __attribute__((aligned(4)));
typedef vec2_s16 bg_point;


// Screenblock struct.  There are 32 (0x20) tiles per row, and 32 (0x20)
// tiles per column.
static constexpr u32 screenblock_size = 0x400;
static constexpr u32 screenblock_xsize = 0x20, screenblock_ysize = 0x20;
static constexpr vec2_u32 screenblock_size_2d 
	= { screenblock_xsize, screenblock_ysize };
typedef scr_entry screenblock [screenblock_size];



// Screen-entry mapping: se_ram [y][x] is SBB y, entry x
#define se_ram ((screenblock*)mem_vram)





// -- Defines for Screen Entries --

// Tile Index of the SE
#define se_id( n ) ( n & 0x3ff )
#define se_id_mask ( (u16)(0x03ff) )

// SE Flipping
#define se_no_flip ( 0x0 << 0xa )
#define se_hflip ( 0x1 << 0xa )
#define se_vflip ( 0x2 << 0xa )
#define se_flip_mask ( (u16)(0x0c00) )

// SE Palette Bank for 16-color mode
#define se_palbank( n ) ( ( n & 0xf ) << 0xc )
#define se_palbank_mask ( (u16)(0xf000) )


// -- End of Defines for Screen Entries --

// ---- End of Screen-Entry Stuffs ----

/* ---- End of Some Helper Structs ---- */



/* ---- Palette RAM Stuffs ---- */
#define bg_pal_ram ((vu16*)(mem_bg_pal))
#define obj_pal_ram ((vu16*)(mem_obj_pal))

static const u32 pal_ram_size = 0x200;
static const u32 bg_pal_ram_size = 0x200;
static const u32 obj_pal_ram_size = 0x200;
/* ---- End of Palette RAM Stuffs ---- */



/* ---- Graphics-related Registers ---- */

// Display Register Address Defines
#define reg_dispcnt *((vu16*)(mem_io + 0x0000))
#define reg_dispstat *((vu16*)(mem_io + 0x0004))
#define reg_vcount *((vu16*)(mem_io + 0x0006))

// LCD I/O BG Control Registers
#define reg_bgcnt ((vu16*)(mem_io + 0x0008))
#define reg_bg0cnt ( reg_bgcnt [0] )
#define reg_bg1cnt ( reg_bgcnt [1] )
#define reg_bg2cnt ( reg_bgcnt [2] )
#define reg_bg3cnt ( reg_bgcnt [3] )

// LCD I/O BG Scrolling Registers
#define reg_bgofs ((bg_point*)(mem_io + 0x0010))

#define reg_bghofs_n(n) *((vu16*)(mem_io + 0x0010 + 0x04 * n))
#define reg_bgvofs_n(n) *((vu16*)(mem_io + 0x0012 + 0x04 * n))


/* ---- End of Graphics-related Registers ---- */


// The width and height of the screen, in pixels
//#define screen_width 240
//#define screen_height 160
static const u32 screen_width = 240;
static const u32 screen_height = 160;

static const vec2_u32 screen_size_2d = { screen_width, screen_height };

// The width and height of the screen, in tiles
static const u32 screen_width_in_tiles = 30;
static const u32 screen_height_in_tiles = 20;

static const vec2_u32 screen_size_in_tiles_2d = { screen_width_in_tiles, 
	screen_height_in_tiles };


static const u32 num_pixels_per_tile_row_or_column = 8;


/* ---- Display Register Value Defines ---- */
//  Bitwise OR these values together

// Defines for reg_dispcnt
//   Video Mode (Select ONLY ONE)
#define dcnt_mode0 0x0000
#define dcnt_mode1 0x0001
#define dcnt_mode2 0x0002
#define dcnt_mode3 0x0003
#define dcnt_mode4 0x0004
#define dcnt_mode5 0x0005
#define dcnt_mode_mask ( (u16)(0x0007) )

//   BG Mode 4 and 5 Page Flipping
#define dcnt_page_0 ( 0x0000 << 0x4 )
#define dcnt_page_1 ( 0x0001 << 0x4 )
#define dcnt_page_mask ( (u16)(0x0010) )

//   OBJ Character VRAM Mapping (Select ONLY ONE)
#define dcnt_obj_2d ( 0x0000 << 0x6 )
#define dcnt_obj_1d ( 0x0001 << 0x6 )
#define dcnt_obj_dim_mask ( (u16)(0x0040) )

//   Forced Blank (Select ONLY ONE)
#define dcnt_blank_off ( 0x0000 << 0x7 )
#define dcnt_blank_on ( 0x0001 << 0x7 )
#define dcnt_blank_mask ( (u16)(0x0080) )

//   Screen Display BG0 (Select ONLY ONE)
#define dcnt_bg0_off ( 0x0000 << 0x8 )
#define dcnt_bg0_on ( 0x0001 << 0x8 )
#define dcnt_bg0_onoff_mask ( (u16)(0x0100) )

//   Screen Display BG1 (Select ONLY ONE)
#define dcnt_bg1_off ( 0x0000 << 0x9 )
#define dcnt_bg1_on ( 0x0001 << 0x9 )
#define dcnt_bg1_onoff_mask ( (u16)(0x0200) )

//   Screen Display BG2 (Select ONLY ONE)
#define dcnt_bg2_off ( 0x0000 << 0xa )
#define dcnt_bg2_on ( 0x0001 << 0xa )
#define dcnt_bg2_onoff_mask ( (u16)(0x0400) )

//   Screen Display BG3 (Select ONLY ONE)
#define dcnt_bg3_off ( 0x0000 << 0xb )
#define dcnt_bg3_on ( 0x0001 << 0xb )
#define dcnt_bg3_onoff_mask ( (u16)(0x0800) )

//   Screen Display OBJ (Select ONLY ONE)
#define dcnt_obj_off ( 0x0000 << 0xc )
#define dcnt_obj_on ( 0x0001 << 0xc )
#define dcnt_obj_onoff_mask ( (u16)(0x1000) )

//   Window 0 Display (Select ONLY ONE)
#define dcnt_win0_off ( 0x0000 << 0xd )
#define dcnt_win0_on ( 0x0001 << 0xd )
#define dcnt_win0_onoff_mask ( (u16)(0x2000) )

//   Window 1 Display (Select ONLY ONE)
#define dcnt_win1_off ( 0x0000 << 0xe )
#define dcnt_win1_on ( 0x0001 << 0xe )
#define dcnt_win1_onoff_mask ( (u16)(0x4000) )

//   OBJ Window Display (Select ONLY ONE)
#define dcnt_winobj_off ( 0x0000 << 0xf )
#define dcnt_winobj_on ( 0x0001 << 0xf )
#define dcnt_winobj_onoff_mask ( (u16)(0x8000) )

/* ---- End of Display Register Value Defines ---- */



/* ---- Defines for reg_dispstat ---- */

//   VBlank status (Read Only)
#define dstat_in_vbl ( 0x0001 << 0x0 )

//   HBlank status (Read Only)
#define dstat_in_hbl ( 0x0001 << 0x1 )

//   VCount trigger status (Read Only ?)
#define dstat_in_vct ( 0x0001 << 0x2 )

//   VBlank IRQ Enable
#define dstat_vbl_irq ( 0x0001 << 0x3 )

//   HBlank IRQ Enable
#define dstat_hbl_irq ( 0x0001 << 0x4 )

//   VCount IRQ Enable
#define dstat_vct_irq ( 0x0001 << 0x5 )

//   VCount trigger value
#define dstat_vct(x) ( x << 0x8 )

/* ---- End of Defines for reg_dispstat ---- */



/* ---- Defines for reg_bgXcnt (X = 0, 1, 2, or 3) ---- */

// BG Priority.  Higher Priority BGs are drawn FIRST.  If there are any
// BGs with the same priority, then BG0 has the highest priority, and BG3
// has the lowest.
#define bgcnt_prio( n ) ( n & 0x1 )
#define bgcnt_prio_mask ( (u16)(0x0001) )

// Character Base Block
#define bgcnt_cbb( n ) ( ( n & 0x3 ) << 0x2 )
#define bgcnt_cbb_mask ( (u16)(0x000c) )

// Mosaic Flag (I don't think I'll use it)
#define bgcnt_mosaic_off ( 0x0 << 0x6 )
#define bgcnt_mosaic_on ( 0x1 << 0x6 )
#define bgcnt_mosaic_mask ( (u16)(0x0040) )

// Whether the BG is 4bpp or 8bpp 
#define bgcnt_4bpp ( 0x0 << 0x7 )
#define bgcnt_8bpp ( 0x1 << 0x7 )
#define bgcnt_bpp_mask ( (u16)(0x0080) )

//Screen Base Block
#define bgcnt_sbb( n ) ( ( n & 0x1f ) << 0x8 )
#define bgcnt_sbb_mask ( (u16)(0x1f00) )

// Affine Wrapping
#define bgcnt_wrap_off ( 0x0 << 0xd )
#define bgcnt_wrap_on ( 0x1 << 0xd )
#define bgcnt_wrap_mask ( (u16)(0x2000) )

// Regular Background Size in Tiles
#define bgcnt_reg_32x32 ( 0x0 << 0xe )
#define bgcnt_reg_64x32 ( 0x1 << 0xe )
#define bgcnt_reg_32x64 ( 0x2 << 0xe )
#define bgcnt_reg_64x64 ( 0x3 << 0xe )
#define bgcnt_reg_mask ( (u16)(0xc000) )

// Affine Background Size in Tiles
#define bgcnt_aff_16x16 ( 0x0 << 0xe )
#define bgcnt_aff_32x32 ( 0x1 << 0xe )
#define bgcnt_aff_64x64 ( 0x2 << 0xe )
#define bgcnt_aff_128x128 ( 0x3 << 0xe )
#define bgcnt_aff_mask ( (u16)(0xc000) )

/* ---- End of Defines for reg_bgXcnt ---- */




/* ---- Some misc. inline functions ---- */
inline void m3_plot ( u32 x, u32 y, u32 color )
{
	( (vu16*)(mem_vram) ) [y * screen_width + x] = color;
}
inline void m4_plot_basic ( u32 x, u32 y, u16 two_color_ids, u32 page = 0 )
{
	// Plot to Page 0
	if ( page == 0 )
	{
		( (vu16*)(mem_vram_page_0) ) [y * screen_width + x] 
			= two_color_ids;
	}
	
	// Plot to Page 1
	else
	{
		( (vu16*)(mem_vram_page_1) ) [y * screen_width + x] 
			= two_color_ids;
	}
}


// The reason that color_id is passed in as a 32-bit variable is speed.
inline void m4_plot ( s32 x, s32 y, u32 color_id, u32 page )
{
	
	if ( !( x >= 0 && x <= (s32)screen_width 
		&& y >= 0 && y <= (s32)screen_height ) )
	{
		return;
	}
	
	vu16* vram_area;
	u16 two_color_ids;
	
	u8 color_id_8bit = color_id & 0xff;
	
	
	// Plot to Page 0
	if ( page == 0 )
	{
		vram_area = (vu16*)(mem_vram_page_0);
	}
	
	// Plot to Page 1
	else
	{
		vram_area = (vu16*)(mem_vram_page_1);
	}
	
	two_color_ids = vram_area [(y * screen_width + x) / sizeof (vu16)];
	
	
	// If x is odd, change the high byte
	if ( x & 1 )
	{
		// Clear the high byte
		two_color_ids &= 0x00ff;
		
		// Set the high byte to the new color ID
		two_color_ids |= ( color_id_8bit << 8 );
	}
	
	// If x is even, change the low byte
	else
	{
		// Clear the low byte
		two_color_ids &= 0xff00;
		
		// Set the low byte to the new color ID
		two_color_ids |= color_id_8bit;
	}
	
	vram_area [(y * screen_width + x) / sizeof (vu16)] = two_color_ids;
}

void m4_line ( s32 x0, s32 y0, s32 x1, s32 y1, u32 color_id, u32 page ) 
	__attribute__ ((_iwram_code));


inline u16 rgb15 ( u32 red, u32 green, u32 blue )
{
	return ( red | ( green << 5 ) | ( blue << 10 ) );
}




static const u32 bgofs_mirror_size = 4;
extern bg_point bgofs_mirror [bgofs_mirror_size] __attribute__ ((_iwram));



inline void copy_bgofs_mirror_to_registers ()
{
	memcpy32 ( reg_bgofs, bgofs_mirror,
		( bgofs_mirror_size * sizeof (bg_point) ) / sizeof (u32) );
}



#endif		// bg_reg_stuff_hpp
