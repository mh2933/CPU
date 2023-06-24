/********************************************************************************
* alu.h: Innehåller deklaration av funktionen "alu", Arithmetic Logic Unit
         (Beräkningsenhet). Utför beräkningar och updaterar statusbitarna
		 SNZVC. 
		 
		 S (Signed)  : Set if result is negative with overflow considered.
		 N (Negative): Set if result is negative, i.e. S = result[7].
		 Z (Zero)    : Set if result is zero, i.e. N = result == 0 ? 1 : 0.
		 V (Overflow): Set if overflow occurs**.
		 C (Carry)   : Set if result contains a carry bit, C = result[9].
		 
		 Exempel från Eriks Visual Studio Kod:
		 Subtrahera två 8-bitars tal -100 och 50. Resultat -100 - 50 = -150,
		 men eftersom bara 8-bitar finns tillgängliga så blir resulatet
		 -150 + 2^8 = -150 + 256 = 106, i.e. 0110 0110. Eftersom MSB är rensad
		 och de två talen -100 och 50 har olika tecken och resultatet har samma 
		 tecken som det subtraherade talet 50. Därför sätts V-flaggan hög.
		 Eftersom N = 0 && V == 1, sätts S-flag hög. Därför tolkas talet korrekt 
		 som negativt. 
		 
		 a) När addition(+) utförs om operand A och B har samma tecken och 
		    resultatet är det motsatta tecknet, i.e.
			
			V = (A[7] == B[7]) && (A[7] != result[7]) : 1 : 0
			
		 b) När subratktion(-) utförs om operand A och B är av motsatt tecken
		    men resultatet har samma tecken som B, i.e.
			
			V = (A[7] != B[7]) && (B[7] == result[7]) : 1 : 0 
				
********************************************************************************/
#ifndef ALU_H_
#define ALU_H_

/* Inkluderingsdirektiv */
#include "cpu.h"
#include <math.h>

/********************************************************************************
* alu: 
*      - operation: The operation to perform (OR, AND, XOR, ADD or SUB).
*      - a        : First operand.
*      - b        : Second operand.
*      - sr       : Reference to status register containing SNZVC flags.
********************************************************************************/
uint32_t alu(uint16_t op,
             uint32_t a,
			 uint32_t b,
			 uint32_t* sr);



#endif /* ALU_H_ */