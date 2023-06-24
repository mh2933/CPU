/********************************************************************************
* main.c: I detta program implementeras ett 32-bitars system(32 register) p� ett 
*          8-bitars system(CPU:ns interna register �r 8 bitar) (ATmega328p). Via 
*         "Assemblerkod" togglas en LED vid nedtryckning av tryckknapp.
********************************************************************************/

/* Inkluderingsdirektiv */
#include "control_unit.h"

/********************************************************************************
* main: H�r anropas funktionen "reset" f�r att �terst�lla, sedan k�rs 
*       programmet via funktionen "run" som k�r igenom instruktionslistan
*       IN, OUT, LDI, NOP etc. kontinuerligt
********************************************************************************/
int main(void)
{

	reset();
	
    while (1) 
    {
		run();
    }
}

