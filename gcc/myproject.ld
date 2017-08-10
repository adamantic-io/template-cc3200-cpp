/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                     `..--::::::--.``                                    *
 *                 `-:/++:--.`      ``....``                               *
 *               .://+:.        ``..``    .-.`                             *
 *             `://+/`      .-//-.       .yss                              *
 *            `://+:      .://`         `so`y+                             *
 *            -///+      -//+           +y. :y:                            *
 *           `:////     `://:          :y:   +y.                           *
 *            :///+     `////         .yo    `ss                           *
 *            -///+.     -//+.        sy+/////oy+                          *
 *            `////+`     -//+-      +y-......./y:                         *
 *             `/////`     .///:`   -y/         +y.                        *
 *              `/////-      -///:.`++          `+/                        *
 *                -////:.      .:///-.`                     `              *
 *                 `:////:.       `-:/+/-..``     `..`     .               *
 *                   .://///-`         .--:::::---.       .-               *
 *                     `-/////:-.                       `::                *
 *                        `-/+////:-.``              `.:/.                 *
 *                            .-:/+/////::--------::+/:.                   *
 *                                 .--::////////::-.`                      *
 *                            ADAMANTIC SOLUTIONS                          *
 *                      Copyright (C) 2017 ADAMANTIC srl                   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Project : TI-CC3200 C++ Template                                        *
 * Author  : Domenico Barra <dom@adamantic.io>                             *
 * This    : Basic Linker Script                                           *
 * License : LGPL v.3, see the LICENSE file shipped with this distribution *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

HEAP_SIZE = 0x00010000;

MEMORY
{
    /* SRAM size of 240KB for cc3200 ES 1.33 device onward */
    SRAM (rwx) : ORIGIN = 0x20004000, LENGTH = 0x3C000
}

stack_size = 0xFFFF;
_stack_start = ORIGIN(SRAM)+LENGTH(SRAM);
_stack_end = _stack_start - stack_size;

SECTIONS
{
   .text :
    {
    	_text = .;
        KEEP(*(.intvecs))
    	CREATE_OBJECT_SYMBOLS
		*(.text .text.* .gnu.linkonce.t.*) 
		*(.plt)
		*(.gnu.warning)
		*(.glue_7t)
        *(.glue_7)
		
		*(.eh_frame) /* for C++ exceptions on x86 */

		. = ALIGN(0x4);
		/* These are for static constructors and destructors under ELF */
		KEEP (*crtbegin.o(.ctors))
		KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors)) KEEP (*(SORT(.ctors.*)))
		KEEP (*crtend.o(.ctors))
		KEEP (*crtbegin.o(.dtors))
		KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors)) KEEP (*(SORT(.dtors.*)))
		KEEP (*crtend.o(.dtors))
		
        *(.text*)
        *(.rodata .rodata.* .gnu.linkonce.r.*)
		*(.ARM.extab* .gnu.linkonce.armextab.*)
		*(.init) 
		*(.fini)
		. = ALIGN(8);
        _etext = .;
    } > SRAM

    .ARM : 
    {
    	__exidx_start = .;
      	*(.ARM.exidx* .gnu.linkonce.armexidx.*)
      	__exidx_end = .;
    } > SRAM

    __init_data = .;

    .data : AT(__init_data)
    {
        _data = .;
        KEEP(*(.jcr)) 
        *(.got.plt) *(.got) 
        *(.shdata)
		*(.data .data.* .gnu.linkonce.d.*)
		. = ALIGN (8);
        _edata = .;
    } > SRAM

	. = ALIGN(4);
	.init_array :
	{
		__init_array_start = .;
		KEEP (*(.init_array*))
		__init_array_end = .;
	} > SRAM

    .bss :
    {
        _bss = .;
        *(.shbss)
		*(.bss .bss.* .gnu.linkonce.b.*)        
		*(COMMON)
        _ebss = .;
    } > SRAM

    .heap :
    {
	_heap = .;
	. = . + HEAP_SIZE;
	. = ALIGN(8);
	_eheap = .;

    } > SRAM
}

