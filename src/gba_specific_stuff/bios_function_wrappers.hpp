#ifndef bios_function_wrappers_hpp
#define bios_function_wrappers_hpp


/* ---- The BIOS Call Numbers ---- */
// SoftReset
#define bios_soft_reset 0x00
// RegisterRamReset
#define bios_register_reg_reset 0x01
// Halt
#define bios_halt 0x02
// Stop
#define bios_stop 0x03
// IntrWait
#define bios_intr_wait 0x04
// VBlankIntrWait
#define bios_vblank_intr_wait 0x05
// Div
#define bios_div 0x06
// DivArm
#define bios_div_arm 0x07


// Sqrt
#define bios_sqrt 0x08
// ArcTan
#define bios_arctan 0x09
// ArcTan2
#define bios_arctan2 0x0a
// CPUSet
#define bios_cpu_set 0x0b
// CPUFastSet
#define bios_cpu_fast_set 0x0c
// BiosChecksum
#define bios_bios_checksum 0x0d
// BgAffineSet
#define bios_bg_affine_set 0x0e
// ObjAffineSet
#define bios_obj_affine_set 0x0f



// BitUnPack
#define bios_bit_unpack 0x10
// LZ77UnCompWRAM
#define bios_lz77_uncomp_wram 0x11
// LZ77UnCompVRAM
#define bios_lz77_uncomp_vram 0x12
// HuffUnComp
#define bios_huff_uncomp 0x13
// RLUnCompWRAM
#define bios_rl_uncomp_wram 0x14
// RLUnCompVRAM
#define bios_rl_uncomp_vram 0x15
// Diff8bitUnFilterWRAM
#define bios_diff_8bit_unfilter_wram 0x16
// Diff8bitUnFilterVRAM
#define bios_diff_8bit_unfilter_vram 0x17



// Diff16bitUnFilter
#define bios_diff_16bit_unfilter 0x18
// SoundBiasChange
#define bios_sound_bias_change 0x19
// SoundDriverInit
#define bios_sound_driver_init 0x1a
// SoundDriverMain
#define bios_sound_driver_main 0x1b
// SoundDriverMode
#define bios_sound_driver_mode 0x1c
// SoundDriverVSync
#define bios_sound_driver_vsync 0x1d
// SoundChannelClear
#define bios_sound_channel_clear 0x1e
// MIDIKey2Freq
#define bios_midi_key_2_freq 0x1f


// MusicPlayerOpen
#define bios_music_player_open 0x20
// MusicPlayerStart
#define bios_music_player_start 0x21
// MusicPlayerStop
#define bios_music_player_stop 0x22
// MusicPlayerContinue
#define bios_music_player_continue 0x23
// MusicPlayerFadeOut
#define bios_music_player_fade_out 0x24
// MultiBoot
#define bios_multiboot 0x25
// HardReset
#define bios_hard_reset 0x26
// CustomHalt
#define bios_custom_halt 0x27


// SoundDriverVSyncOff
#define bios_sound_driver_vsync_off 0x28
// SoundDriverVSyncOn
#define bios_sound_driver_vsync_on 0x29
// GetJumpList
#define bios_get_jump_list 0x2a
/* ---- End of The BIOS Call Numbers ---- */


//#if !defined ( __thumb__)
#if defined ( __thumb__)
#define swi_call( x ) asm volatile("swi\t"#x ::: "r0","r1","r2","r3")
#else
#define swi_call( x ) asm volatile("swi\t"#x"<<16" ::: "r0","r1","r2","r3")
#endif



inline void bios_wait_for_vblank ()
{
	swi_call (0x05);
}



#endif		// bios_function_wrappers_hpp
