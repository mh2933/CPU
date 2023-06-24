/********************************************************************************
* stack.h: H�r deklareras funktioner f�r att nollst�lla, l�gga till och ta bort
*          fr�n stacken.
********************************************************************************/
#ifndef STACK_H_
#define STACK_H_

/* Inkluderingsdirektiv */
#include "cpu.h"

/********************************************************************************
* STACK_ADDRESS_WIDTH: Adress bredd p� stacken.
********************************************************************************/
#define STACK_ADDRESS_WIDTH 100

void stack_reset(void);
int stack_push(const uint32_t value);
uint32_t stack_pop(void);



#endif /* STACK_H_ */