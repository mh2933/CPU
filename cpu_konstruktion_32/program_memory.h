/********************************************************************************
* program_memory.h: Här deklareras funktioner för att skriva och läsa till och 
*                   från programminnet. Detta minne är 32 Kbyte stort på
*                   ATmega328p.      
********************************************************************************/
#ifndef PROGRAM_MEMORY_H_
#define PROGRAM_MEMORY_H_

/* Inkluderingsdirektiv */
#include "cpu.h"

/********************************************************************************
* PROGRAM_MEMORY_ADDRESS_WIDTH: Denna adress bredd går att justera utefter 
*                               programkodens storlek.
********************************************************************************/
#define PROGRAM_MEMORY_ADDRESS_WIDTH 40

void program_memory_write(void);
uint64_t program_memory_read(const uint16_t address);

#endif /* PROGRAM_MEMORY_H_ */