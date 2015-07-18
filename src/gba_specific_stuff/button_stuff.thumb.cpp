#include "attribute_defines.hpp"
#include "button_stuff.hpp"
#include "../misc_helper_stuff/prev_curr_pair_class.hpp"


// Global variables to hold the key state
//vu16 __key_curr __attribute__((_ewram)) = 0,
//	__key_prev __attribute__((_ewram)) = 0;

volatile prev_curr_pair <vu16> __key_state __attribute__((_ewram)) 
	= { 0, 0 };


