/********************************************************************************
* program_memory.c: Här defineras funktioner för att skriva och läsa till och
*                   från progamminnet.
********************************************************************************/

/* Inkluderingsdirektiv */
#include "program_memory.h"

#define main          4
#define main_loop     5
#define setup         6
#define ISR_PCINT     15
#define ISR_PCINT_end 19

#define BUTTON2_CHECK 2
#define BUTTON3_CHECK 3

#define LED1 PORT8
#define LED2 PORT9
#define LED3 PORT10
#define BUTTON3 PORT11
#define BUTTON2 PORT12
#define BUTTON1 PORT13

static inline uint64_t join(const uint16_t op_code,
const uint16_t op1,
const uint32_t op2);

static uint64_t program_memory[PROGRAM_MEMORY_ADDRESS_WIDTH];

/********************************************************************************
* program_memory_write: Här skrivs själva "Assembler" koden som körs på Arduinon
*                       Vid nedtryckning av tryckknap hoppar programmet till en
*                       avbrottsrutin som togglar en LED.
********************************************************************************/
void program_memory_write(void)
{
	static bool program_memory_initialized = false;
	if (program_memory_initialized) return;
	
	program_memory[0]  = join(JMP, main, 0x00);
	program_memory[1]  = join(NOP, 0x00, 0x00);
	program_memory[2]  = join(JMP, ISR_PCINT, 0x00);
	program_memory[3]  = join(NOP, 0x00, 0x00);

	program_memory[4]  = join(CALL, setup, 0x00);
	program_memory[5]  = join(JMP, main_loop, 0x00);

	program_memory[6]  = join(LDI, R16, (1 << LED1));
	program_memory[7]  = join(OUT, DDR, R16);
	program_memory[8]  = join(LDI, R17, (1 << BUTTON1));
	program_memory[9]  = join(OUT, PORT, R17);
	program_memory[10] = join(SEI, 0x00, 0x00);
	program_memory[11] = join(LDI, R24, (1 << PCIE));
	program_memory[12] = join(OUT, ICR, R24);
	program_memory[13] = join(OUT, PCMSK, R17);
	program_memory[14] = join(RET, 0x00, 0x00);

	program_memory[15] = join(IN, R24, PIN);
	program_memory[16] = join(ANDI, R24, (1 << BUTTON1));
	program_memory[17] = join(BREQ, ISR_PCINT_end, 0x00);
	program_memory[18] = join(OUT, PIN, R16);
	program_memory[19] = join(RETI, 0x00, 0x00);
	
	program_memory_initialized = true;
	return;
	
	/*/*****************************************************************************
	* Assemblerkod: Misslyckat försök att få in tre leds med assembler.
	*                                             
	********************************************************************************
	
	 void program_memory_write(void)
	 {
		 static bool program_memory_initialized = false;
		 if (program_memory_initialized) return;
		 
		 // RESET_vect: Programmets startadress, Vi hoppar till subrutinen main för att starta programmet
		 program_memory[0]  = join(RESET_vect, 0x00, 0x00);
		 program_memory[1]  = join(JMP, main, 0x00);

		 //PCINT0_vect: Avbrottsvektor för PCI-avbrott på I/O-port B.
		 program_memory[2]  = join(PCI_vect, 0x00, 0x00);
		 program_memory[3]  = join(JMP, ISR_PCINT, 0x00);
		 
		 //ISR_PCINT0: Avbrottsrutin för PCI-avbrott på I/O port B som äger rum vid nedtryckning och uppsläppning av trycknappen.
		 //            Vid nedtryckning togglas lysdioden, annars gör ingenting.
		 program_memory[4]  = join(ISR_PCINT, 0x00, 0x00);
		 program_memory[5]  = join(IN, R24, PIN);
		 program_memory[6]  = join(ANDI, R24, (1 << BUTTON1));
		 program_memory[7]  = join(BREQ, BUTTON2_CHECK, 0x00); // om det resultatet vi fick är noll hoppa till subrutin
		 program_memory[9]  = join(OUT, PIN, R16);
		 program_memory[10] = join(JMP, ISR_PCINT_end, 0x00);
		 program_memory[11] = join(BUTTON2_CHECK, 0x00, 0x00);
		 program_memory[12] = join(IN, R24, PIN);
		 program_memory[13] = join(ANDI, R24, (1 << BUTTON2));
		 program_memory[14] = join(BREQ, BUTTON3_CHECK, 0x00);
		 program_memory[15] = join(OUT, PIN, R17);
		 program_memory[16] = join(JMP, ISR_PCINT_end, 0x00);
		 program_memory[17] = join(BUTTON3_CHECK, 0x00, 0x00);
		 program_memory[18] = join(IN, R24, PIN);
		 program_memory[19] = join(ANDI, R24, (1 << BUTTON3));
		 program_memory[20] = join(BREQ, ISR_PCINT_end, 0x00);
		 program_memory[21] = join(OUT, PIN, R18);
		 program_memory[22] = join(ISR_PCINT_end, 0x00, 0x00);
		 program_memory[23] = join(RETI, 0x00, 0x00);

		 // main: Initierar systemet
		 program_memory[24] = join(main, 0x00, 0x00);

		 // setup R16 = (1 << LED1), R17 = (1 << BUTTON1), R18 = (1 << PCIE0)
		 program_memory[25] = join(setup, 0x00, 0x00);
		 program_memory[26] = join(LDI, R16, (1 << LED1));
		 program_memory[27] = join(LDI, R17, (1 << LED2));
		 program_memory[28] = join(LDI, R18, (1 << LED3));
		 program_memory[29] = join(LDI, R19, (1 << LED1) | (1 << LED2) | (1 << LED3));
		 program_memory[30] = join(OUT, DDR, R19);
		 program_memory[31] = join(LDI, R23, (1 << BUTTON1) | (1 << BUTTON2) | (1 << BUTTON3));
		 program_memory[32] = join(OUT, PORT, R23);
		 program_memory[33] = join(SEI, 0x00, 0x00);
		 //LDI R18, (1 << PCIE0)
		 program_memory[34] = join(STS, ICR, R19);
		 program_memory[35] = join(STS, PCMSK, R23); // (1 << LED1) är samma som (1 << PCIE0), då LED1 = PCIE0 = 0.
		 //LDI R16, (1 << LED1) ; R17 innehåller fortfarande

		 // main_loop: Initierar systemet
		 program_memory[36] = join(main_loop, 0x00, 0x00);
		 program_memory[37] = join(JMP, main_loop, 0x00);
		 
		 program_memory_initialized = true;
		 return;
	 }
	*/
	
	
}
uint64_t program_memory_read(const uint16_t address)
{
	if (address < PROGRAM_MEMORY_ADDRESS_WIDTH)
	{
		return program_memory[address];
	}
	else
	{
		return 0x00;
	}
}

static inline uint64_t join(const uint16_t op_code,
const uint16_t op1,
const uint32_t op2)
{
	const uint64_t instruction = ((uint64_t)op_code << 48) | ((uint64_t)op1 << 32) | (uint64_t)op2;
	return instruction;
}