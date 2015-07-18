ENTRY(_start2)
/*STARTUP(objs/main.o)*/

OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)


MEMORY
{
	rom	: ORIGIN = 0x08000000, LENGTH = 32M
	iwram	: ORIGIN = 0x03000000, LENGTH = 32K
	ewram	: ORIGIN = 0x02000000, LENGTH = 256K
	sram	: ORIGIN = 0x0e000000, LENGTH = 64K
}

__text_start	=	ORIGIN(rom);
__ewram_start	=	ORIGIN(ewram);
__iwram_start	=	ORIGIN(iwram);
__sram_start	=	ORIGIN(sram);

SECTIONS
{
	. = __text_start;
	
	.startup :
	{
		*(.startup);
		*(.asm_text);
		. = ALIGN(4);
	} >rom
	
	.text :
	{
		CREATE_OBJECT_SYMBOLS
		*(.text .text.* .gnu.linkonce.t.*)
		*(.plt)
		*(.gnu_warning)
		*(.glue_7t) *(.glue_7)
		
		
		. = ALIGN(4);
		
		KEEP (*crtbegin.o(.ctors))
		KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
		KEEP (*(SORT(.ctors.*)))
		KEEP (*crtend.o(.ctors))
		KEEP (*ctrbegin.o(.dtors))
		KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors))
		KEEP (*(SORT(.dtors.*)))
		KEEP (*ctrend.o(.dtors))
		
		*(.rodata .rodata.* .gnu.linkonce.r.*)
		
		
		*(.init)
		*(.fini)
	} >rom
	
	.ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >rom
	__exidx_start = .;
	.ARM.exidx   : { *(.ARM.exidx* .gnu.linkonce.armexidx.*) } >rom
	__exidx_end = .;
	
	.ARM.attributes : { *(.ARM.attributes) } >rom
	
	
	.init_array : ALIGN (4)
	{
		__init_array_load = LOADADDR (.init_array);
		__init_array_start = .;
		*(.init_array)
		*(SORT_BY_INIT_PRIORITY(.init_array.*))
		__init_array_end = .;
	} >ewram AT >rom
	
	
	.data :
	{
		__data_load = LOADADDR (.data);
		__data_start = .;
		KEEP (*(.jcr))
		*(.got.plt) *(.got)
		*(.shdata)
		*(.data .data.* .gnu.linkonce.d.*)
		. = ALIGN (4);
		__data_end = .;
	} >ewram AT >rom
	
	
	/* Code to be copied to IWRAM */
	.iwram_code :
	{
		/* The start of code to be copied to IWRAM*/
		iwram_code_rom_start = LOADADDR (.iwram_code);
		
		iwram_code_iwram_start = .;
		*(.iwram_code);
		
		. = ALIGN(4);
	} >iwram AT >rom
	
	iwram_code_size = SIZEOF(.iwram_code);
	
	
	
	.ewram_code :
	{
		/* The start of code to be copied to EWRAM */
		ewram_code_rom_start = LOADADDR (.ewram_code);
		
		ewram_code_ewram_start = .;
		*(.ewram_code);
		
		. = ALIGN(4);
	} >ewram AT >rom
	
	ewram_code_size = SIZEOF(.ewram_code);
	
	
	
	.bss :
	{
		__bss_start__ = .;
		*(.bss .bss.* .gnu.linkonce.b.*)
		*(.ewram .ewram.*)
		*(COMMON)
		. = ALIGN(4);
		__bss_end__ = .;
		
		/* The symbol end is used to tell where malloc, new, and friends have free access. */
		end = .;
	} >ewram
	
	
	.iwram :
	{
		*(.iwram .iwram.*);
		
		. = ALIGN(4);
		
		/* The symbol end is used to tell where malloc, new, and friends have free access. */
		/*end = .;*/
	} >iwram
	
	__iwram_size = SIZEOF(.iwram);
	
	
	.sram :
	{
		*(.sram .sram.*);
		
		. = ALIGN(4);
	} >sram
	
	/*__ewram_lma = __iwram_lma + __iwram_size;
	
	.ewram __ewram_start + SIZEOF(.ewram_code) : AT (__ewram_lma)
	{
		*(.ewram);
		
		. = ALIGN(4);
	} >ewram =0
	
	__ewram_size = SIZEOF(.ewram);*/
	
	
	
	
	/*.sram ALIGN(4) (NOLOAD) :
	{
		__sram_start__ = ABSOLUTE(.);
		*(.sram);
		
		. = ALIGN(4);
		__sram_end__ = ABSOLUTE(.);
	} >sram*/
	
	
	.stab : { *(.stab) } AT >rom
	.stabstr : { *(.stabstr) } AT >rom
	.comment : { *(.comment) } AT >rom
	.debug_frame : { *(.debug_frame) } AT >rom
}

/*PROVIDE ( _HEAP_START = 0x020200000 );

PROVIDE ( _HEAP_END = 0x020300000 );*/

