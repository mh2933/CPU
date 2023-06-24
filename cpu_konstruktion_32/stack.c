/********************************************************************************
* stack.c: Inneh�ller funktionsdefinitioner med 4kB stack som v�xer ned�t
*          
********************************************************************************/

/* Inkluderingsdirektiv */
#include "stack.h"

/********************************************************************************
* stack: Stack med kapacitet 4096 bytes
********************************************************************************/
static uint32_t stack[STACK_ADDRESS_WIDTH];

/********************************************************************************
* sp: Stack pekare, pekar p� sista elementet som lades till p� stacken 
********************************************************************************/
uint16_t sp;

/********************************************************************************
* stack_empty: Indikerar ifall stacken �r tom.
********************************************************************************/
bool stack_empty;

/********************************************************************************
* stack_reset: T�mmer stacken. 
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
              lyckat genomf�rande. Om stacken �r full sker ingen PUSH och error
			  kod 1 returneras.
			  
			  - value: V�rde som PUSH:As p� stacken    
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
* stack_pop: Returnerar en byte POP:ed fr�n botten av stacken. Om stacken �r
             tom, sker ingen l�sning och 0 returneras.
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
