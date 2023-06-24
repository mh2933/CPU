/********************************************************************************
* data_memory.c: Inneh�ller definationer av funktioner f�r dataminnet. 
                 Dataminnet �r 2 Kbytes p� en ATmega328P.   
********************************************************************************/
/* Inkluderingsdirektiv */
#include "data_memory.h"

/********************************************************************************
* data_memory: Adress-bredden p� det 2 Kbytes stora SRAM minnet.  
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
*                            - address: adressen i dataminnet som d�r skall
*                                       skrives till
*                            - value:   V�rdet som skall skrivs till dataminnet
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
* data_memory_read: L�ser fr�n dataminnet
*
*                            - address: adressen i dataminnet som d�r skall
*                                       l�ses ifr�n
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
