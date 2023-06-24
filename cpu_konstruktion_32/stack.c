/********************************************************************************
* stack.c: Innehåller funktionsdefinitioner med 4kB stack som växer nedåt
*          
********************************************************************************/

/* Inkluderingsdirektiv */
#include "stack.h"

/********************************************************************************
* stack: Stack med kapacitet 4096 bytes
********************************************************************************/
static uint32_t stack[STACK_ADDRESS_WIDTH];

/********************************************************************************
* sp: Stack pekare, pekar på sista elementet som lades till på stacken 
********************************************************************************/
uint16_t sp;

/********************************************************************************
* stack_empty: Indikerar ifall stacken är tom.
********************************************************************************/
bool stack_empty;

/********************************************************************************
* stack_reset: Tömmer stacken. 
********************************************************************************/
void stack_reset(void)
{
	for (uint32_t i = 0; i < STACK_ADDRESS_WIDTH; i++)
	{
		stack[i] = 0x00;
	}
	
	sp = STACK_ADDRESS_WIDTH - 1;
	stack_empty = true;
	return;
}

/********************************************************************************
* stack_push: PUSH en byte till botten av stacken och returnerar 0 efter
              lyckat genomförande. Om stacken är full sker ingen PUSH och error
			  kod 1 returneras.
			  
			  - value: Värde som PUSH:As på stacken    
********************************************************************************/
int stack_push(const uint32_t value)
{
	if (sp == 0)
	{
		return 1;
	}
	else
	{
		if (stack_empty)
		{
			stack[sp] = value;
			stack_empty = false;
		}
		else
		{
			stack[sp--] = value;
		}
		return 0;
	}
}

/********************************************************************************
* stack_pop: Returnerar en byte POP:ed från botten av stacken. Om stacken är
             tom, sker ingen läsning och 0 returneras.
********************************************************************************/
uint32_t stack_pop(void)
{
	if (stack_empty)
	{
		return 0;
	}
	else
	{
		if (sp < STACK_ADDRESS_WIDTH - 1)
		{
			return stack[sp++];
		}
		else
		{
			stack_empty = true;
			return stack[sp];
		}
	}
}
