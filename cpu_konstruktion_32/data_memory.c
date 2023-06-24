/********************************************************************************
* data_memory.c: Innehåller definationer av funktioner för dataminnet. 
                 Dataminnet är 2 Kbytes på en ATmega328P.   
********************************************************************************/
/* Inkluderingsdirektiv */
#include "data_memory.h"

/********************************************************************************
* data_memory: Adress-bredden på det 2 Kbytes stora SRAM minnet.  
********************************************************************************/
static uint32_t data_memory[DATA_MEMORY_ADDRESS_WIDTH];

/********************************************************************************
* data_memory_reset: Resetter dataminnet
********************************************************************************/
void data_memory_reset(void)
{
	for (uint16_t i = 0; i < DATA_MEMORY_ADDRESS_WIDTH; i++)
	{
		data_memory[i] = 0x00;
	}
	
	return;
}

/********************************************************************************
* data_memory_write: Skriver till dataminnet
*
*                            - address: adressen i dataminnet som där skall
*                                       skrives till
*                            - value:   Värdet som skall skrivs till dataminnet
********************************************************************************/
int data_memory_write(const uint16_t address,
                      const uint32_t value)
{
	if (address < DATA_MEMORY_ADDRESS_WIDTH)
	{
		data_memory[address] = value;
	    return 0;
	}
	else
	{
		return 1;
	}
}

/********************************************************************************
* data_memory_read: Läser från dataminnet
*
*                            - address: adressen i dataminnet som där skall
*                                       läses ifrån
********************************************************************************/
uint32_t data_memory_read(const uint16_t address)
{
	if (address < DATA_MEMORY_ADDRESS_WIDTH)
	{
		return data_memory[address];
	}
	else
	{
		return 0x00;
	}
}
