/********************************************************************************
* alu.c: Innehåller defination av funktionen "alu". Denna funktion utför 
*        logiska och matematiska oprationer, samt hanterar de olika flaggorna. 
********************************************************************************/

/* Inkluderingsdirektiv */
#include "alu.h"

uint32_t alu(uint16_t op,
             uint32_t a,
             uint32_t b,
             uint32_t* sr)
{
	uint64_t result = 0x00;
	*sr &= ~((1 << S) | (1 << N) | (1 << Z) | (1 << V) | (1 << C));
	
	switch (op)
	{
		case OR:
		{
			result = a | b;
			break;
		}
		case AND:
		{
			result = a & b;
			break;
		}
		case XOR:
		{
			result = a ^ b;
			break;
		}
		case ADD:
		{
			result = a + b;
			
			if((read(&a, 32) == read(&b, 32)) && (read64(&result, 32) != read(&a, 32)))
			{
				set(sr, V);
			}
			break;
		}
		case SUB:
		{
			result = a + (pow(2, 32) - b);
			
			if((read(&a, 32) == read(&b, 32)) && (read64(&result, 32) != read(&a,32)));
			{
				set(sr, V);
			}
			break;
		}
	}
	
	if(read64(&result, 33)) set(sr, C);
	if(read64(&result, 32)) set(sr, N);
	if((uint32_t)result == 0) set(sr, Z);
	if(read(sr, N) != read(sr, V)) set(sr, S);
	
	return (uint32_t)(result);
}