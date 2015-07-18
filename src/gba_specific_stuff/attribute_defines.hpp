#ifndef attribute_defines_hpp
#define attribute_defines_hpp


/* ---- #defines for Sections ---- */

// Example:  __attribute__ ((_ewram))
// Another example:  __attribute__ (( _ewram, _align4 ))

// #defines for putting stuff in EWRAM, IWRAM, and SRAM
#define _ewram section (".ewram")
#define _iwram section (".iwram")
#define _sram section (".sram")

// A #define for UNITIALIZED global variables
#define _bss section (".bss")


// #defines for putting stuff in the code (sections for EWRAM and IWRAM
#define _ewram_code section (".ewram_code")
#define _iwram_code section (".iwram_code")

/* ---- End of #defines for Sections ---- */


// A #define for aligning structs/classes
#define _align4 aligned (4)


// A #define for making sure that structs/classes have the exact size of
// all their members combined (USE WITH CAUTION)
#define _packed packed


#endif		// attribute_defines_hpp
