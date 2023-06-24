/********************************************************************************
* control_unit.h: Innehåller deklarationer av funktioner använt av 
*                 kontrollenheten.
********************************************************************************/
#ifndef CONTROL_UNIT_H_
#define CONTROL_UNIT_H_

/* Inkluderingsdirektiv */
#include "cpu.h"
#include "data_memory.h"
#include "alu.h"
#include "stack.h"
#include "program_memory.h"

void reset(void);
void run(void);




#endif /* CONTROL_UNIT_H_ */