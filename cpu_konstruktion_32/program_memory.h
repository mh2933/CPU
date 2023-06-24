/********************************************************************************
* program_memory.h: H�r deklareras funktioner f�r att skriva och l�sa till och 
*                   fr�n programminnet. Detta minne �r 32 Kbyte stort p�
*                   ATmega328p.      
********************************************************************************/
#ifndef PROGRAM_MEMORY_H_
#define PROGRAM_MEMORY_H_

/* Inkluderingsdirektiv */
#include "cpu.h"

/********************************************************************************
* PROGRAM_MEMORY_ADDRESS_WIDTH: Denna adress bredd g�r att justera utefter 
*                               programkodens storlek.
********************************************************************************/
#define PROGRAM_MEMORY_ADDRESS_WIDTH 40

void program_memory_write(void);
uint64_t program_memory_read(const uint16_t address);

#endif /* PROGRAM_MEMORY_H_ */