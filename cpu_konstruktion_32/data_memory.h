/********************************************************************************
* data_memory.h: Inneh�ller deklarationer av funktioner f�r dataminnet.
                 Storleken p� dataminnet �r 2 kB p� ATmega328p. 
********************************************************************************/
#ifndef DATA_MEMORY_H_
#define DATA_MEMORY_H_

/* Inkluderingsdirektiv */
#include "cpu.h"

/********************************************************************************
* DATA_MEMORY_ADDRESS_WIDTH: Detta v�rde kan �ndras f�r att justera 
                             dataminnets utnyttjande, beroende p� data m�ngdens
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
*                            - address: adressen i dataminnet som d�r skall 
*                                       skrives till
*                            - value:   V�rdet som skall skrivs till dataminnet
********************************************************************************/
int data_memory_write(const uint16_t address,
                      const uint32_t value);
					  
/********************************************************************************
* data_memory_read: L�ser fr�n dataminnet
*
*                            - address: adressen i dataminnet som d�r skall
*                                       l�ses ifr�n
********************************************************************************/					  
uint32_t data_memory_read(const uint16_t address);


#endif /* DATA_MEMORY_H_ */