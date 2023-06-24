/********************************************************************************
* data_memory.h: Innehåller deklarationer av funktioner för dataminnet.
                 Storleken på dataminnet är 2 kB på ATmega328p. 
********************************************************************************/
#ifndef DATA_MEMORY_H_
#define DATA_MEMORY_H_

/* Inkluderingsdirektiv */
#include "cpu.h"

/********************************************************************************
* DATA_MEMORY_ADDRESS_WIDTH: Detta värde kan ändras för att justera 
                             dataminnets utnyttjande, beroende på data mängdens
							 storlek. 
********************************************************************************/
#define DATA_MEMORY_ADDRESS_WIDTH 200

/********************************************************************************
* data_memory_reset: Resetter dataminnet
********************************************************************************/
void data_memory_reset(void);

/********************************************************************************
* data_memory_write: Skriver till dataminnet
*
*                            - address: adressen i dataminnet som där skall 
*                                       skrives till
*                            - value:   Värdet som skall skrivs till dataminnet
********************************************************************************/
int data_memory_write(const uint16_t address,
                      const uint32_t value);
					  
/********************************************************************************
* data_memory_read: Läser från dataminnet
*
*                            - address: adressen i dataminnet som där skall
*                                       läses ifrån
********************************************************************************/					  
uint32_t data_memory_read(const uint16_t address);


#endif /* DATA_MEMORY_H_ */