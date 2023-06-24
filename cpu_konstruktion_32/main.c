/********************************************************************************
* main.c: I detta program implementeras ett 32-bitars system(32 register) på ett 
*          8-bitars system(CPU:ns interna register är 8 bitar) (ATmega328p). Via 
*         "Assemblerkod" togglas en LED vid nedtryckning av tryckknapp.
********************************************************************************/

/* Inkluderingsdirektiv */
#include "control_unit.h"

/********************************************************************************
* main: Här anropas funktionen "reset" för att återställa, sedan körs 
*       programmet via funktionen "run" som kör igenom instruktionslistan
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

