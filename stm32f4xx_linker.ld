/*
 * Linker file para STM32F4xx para ser utilizado com GCC Compiler for ARM
 * Autor: Cristóvão Zuppardo Rufino <cristovaozr@gmail.com>
 */

MEMORY
{
	FLASH (rx)	    : ORIGIN = 0x08000000, LENGTH = 1024K
	SRAM1 (rwx)	    : ORIGIN = 0x20000000, LENGTH = 128K /* 112K + 16K */
    SRAM_CCM (rwx)  : ORIGIN = 0x10000000, LENGTH = 64K
}

SECTIONS
{
	.text :
	{
		_text = .;
		KEEP(*(.isr_vector))
		*(.text*) /* Código */
		*(.rodata*) /* Constantes (read-only data = rodata) */
		_etext = .;
	} > FLASH

	.data : AT(ADDR(.text) + SIZEOF(.text))
	{
		_data = .;
		*(vtable) /* V-Table de C++, se utilizado */
		*(.data*) /* Variáveis */
		_edata = .;
	} > SRAM1

	.bss :
	{
		_bss = .;
		*(.bss*) /* Variáveis não inicializadas */
		*(COMMON)
		_ebss = .;
	} > SRAM1
}

