/* stm32f4.ld */
MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 1M
  RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS
{
  .text : {
    KEEP(*(.isr_vector))
    *(.text*)
    *(.rodata*)
  } > FLASH

  .data : {
    *(.data*)
    . = ALIGN(4);
    _edata = .;
  } > RAM AT > FLASH

  .bss : {
    . = ALIGN(4);
    _sbss = .;
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } > RAM

  . = ALIGN(4);
  _end = .;
  _stack_end = ORIGIN(RAM) + LENGTH(RAM);
}