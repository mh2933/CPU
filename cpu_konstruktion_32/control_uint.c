/********************************************************************************
* control_uint.c: Här deklareras olika funktioner för kontrollenheten samt 
                  statiska variabler. Villket tillstånd(states)  
*                 CPU'n defineras och själva utförandet av OP-koderna
*                 bestämms också. 
********************************************************************************/
/* Inkluderingsdirektiv */
#include "control_unit.h"


/* Statiska variabler */
static uint16_t pc;          /* Programräknare, lagrar adressen till nästa instruktion som ska "fetch" */
static uint64_t ir;          /* Insktruktionsregister, lagrar nästa instruktion som ska exekveras */
static uint32_t  sr;         /* Statusregister, lagrar status bitarna ISNZVC */

static uint16_t op_code;     /* Lagrar OP-kod ex. LDI, OUT, JMP osv. */
static uint16_t op1;         /* Operand 1, oftast en en destination  */
static uint32_t op2;         /* Operand 2, oftast ett värde eller adress att läsa */

static enum state current_state;                 /* Lagrar det nuvarande tillståndet FETCH, DECODE, EXECUTE */
static volatile uint32_t pin_last_value;         /* Sista inlästa värdet i PIN-registret */
static uint32_t reg[CPU_REGISTER_ADDRESS_WIDTH]; /* CPU-register R0-R31 */

static void io_reset(void);
static void io_update(void);
static inline void cpu_registers_clear(void);
static inline void monitor_interrupts(void);
static inline void check_for_interrupt_requests(void);
static inline void generate_interrupt(const uint16_t interrupt_vector);
static inline void return_from_interrupt(void);

void reset(void)
{
	pc = 0x00;
	ir = 0x00;
	sr = 0x00;
	
	op_code = 0x00;
	op1     = 0x00;
	op2     = 0x00;
	
	current_state   = FETCH;
	pin_last_value = 0x00;
	
	io_reset();
	cpu_registers_clear();
	program_memory_write();
	stack_reset();
	data_memory_reset();
	return;
}

void run(void)
{
	switch (current_state)
	{
		case FETCH:
		{
			ir = program_memory_read(pc++);
			current_state = DECODE;
			break;
		}
		case DECODE:
		{
			op_code = (uint16_t)(ir >> 48);
			op1     = (uint16_t)(ir >> 32);
			op2     = (uint32_t)(ir);
			
			current_state = EXECUTE;
			break;
		}
		case EXECUTE:
		{
			switch (op_code)
			{
				case NOP:
				{
					break;
				}
				case LDI:
				{
					reg[op1] = op2;
					break;
				}
				case LD:
				{
					reg[op1] = data_memory_read(reg[op2]);
					break;
				}
				case STS: /* STS counter, R16 => op_code = STS, op1 = counter, op2 = R16 */
				{
					data_memory_write(op1 + 256, reg[op2]);
					break;
				}
				case IN:
				{
					reg[op1] = data_memory_read(op2);
					break;
				}
				case OUT:
				{
					if (op1 == PIN)
					{
					    uint32_t port = data_memory_read(PIN) ^ reg[op2];
						data_memory_write(PORT, port); 	
					}
					else
					{
						data_memory_write(op1, reg[op2]);
					}
					break;
				}
				case OUTI:
				{
					if (op1 == PIN)
					{
						uint32_t port = data_memory_read(PORT) ^ op2;
						data_memory_write(PORT, port);
					}
					else
					{
						data_memory_write(op1, op2);
					}
					break;
				}
				case CLR:
				{
					reg[op1] = 0x00;
					break;
				}
				case ORI:
				{
					reg[op1] = alu(OR, reg[op1], op2, &sr);
					break;
				}
				case OR:
				{
					reg[op1] = alu(OR, reg[op1], reg[op2], &sr);
					break;
				}
				case ANDI:
				{
					reg[op1] = alu(AND, reg[op1], op2, &sr);
					break;
				}
				case AND:
				{
					reg[op1] = alu(AND, reg[op1], reg[op2], &sr);
					break;
				}
				case XORI:
				{
					reg[op1] = alu(XOR, reg[op1], op2, &sr);
					break;
				}
				case XOR:
				{
					reg[op1] = alu(XOR, reg[op1], reg[op2], &sr);
					break;
				}
				case ADDI:
				{
					reg[op1] = alu(ADD, reg[op1], op2, &sr);
					break;
				}
				case ADD:
				{
					reg[op1] = alu(ADD, reg[op1], reg[op2], &sr);
					break;
				}
				case SUBI:
				{
					reg[op1] = alu(SUB, reg[op1], op2, &sr);
					break;
				}
				case SUB:
				{
					reg[op1] = alu(SUB, reg[op1], reg[op2], &sr);
					break;
				}
				case INC:
				{
					reg[op1] = alu(ADD, reg[op1], 1, &sr);
					break;
				}
				case DEC:
				{
					reg[op1] = alu(SUB, reg[op1], 1, &sr);
					break;
				}
				case COMPI:
				{
					(void)(alu(SUB, reg[op1], op2, &sr));
					break;
				}
				case COMP:
				{
					(void)(alu(SUB, reg[op1], reg[op2], &sr));
					break;
				}
				case JMP:
				{
					pc = op1;
					break;
				}
				case BREQ:
				{
					if(read(&sr, Z)) pc = op1;
					break;
				}
				case BRNE:
				{
				    if(!read(&sr, Z)) pc = op1;
					break;
				}
				case BRGT:
				{
					if (!read(&sr, S) && !read(&sr, Z)) pc = op1;
					break;
				}
				case BRLE:
				{
					if (read(&sr, S) || read(&sr, Z)) pc = op1;
					break;
				}
				case BRLT:
				{
					if (read(&sr, S)) pc = op1;
					break;
				}
				case CALL:
				{
					stack_push(pc);
					pc = op1;
					break;
				}
				case RET:
				{
					pc = stack_pop();
					break;
				}
				case RETI:
				{
					return_from_interrupt();
					break;
				}
				case PUSH:
				{
					stack_push(reg[op1]);
					break;
				}
				case POP:
				{
					reg[op1] = stack_pop();
					break;
				}
				case LSL:
				{
					reg[op1] = reg[op1] << 1;
					break;
				}
				case LSR:
				{
					reg[op1] = reg[op1] >> 1;
					break;
				}
				case SEI:
				{
					set(&sr, I);
					break;
				}
				case CLI:
				{
					clr(&sr, I);
					break;
				}
				default:
				{
					reset();
					break;
				}
			}
			
			check_for_interrupt_requests();
			current_state = FETCH;
			break;
		}
		
		default:
		{
			reset();
			break;
		}
		
	}
	io_update();
	monitor_interrupts();
	return;
}

static void io_reset(void)
{
	DDRB = 0x00;
	DDRC = 0x00;
	DDRD = 0x00;
	
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
	
	return;
}

static void io_update(void)
{
	const uint32_t ddr  = data_memory_read(DDR);
	const uint32_t port = data_memory_read(PORT);
	const uint32_t pin = ((uint32_t)(((uint32_t)PINC) << 16) | (((uint32_t)PINB) << 8) | ((uint32_t)PIND));
	
	data_memory_write(PIN, pin);
	
	DDRB = (uint8_t)(ddr >> 8);
	DDRC = (uint8_t)(ddr >> 16);
	DDRD = (uint8_t)(ddr);
	
	PORTB = (uint8_t)(port >> 8);
	PORTC = (uint8_t)(port >> 16);
	PORTD = (uint8_t)(port);
	return;
}

static inline void cpu_registers_clear(void)
{
	for (uint8_t i = 0; i < CPU_REGISTER_ADDRESS_WIDTH; i++)
	{
		reg[i] = 0x00;
	}
	return;
}

static inline void monitor_interrupts(void)
{
	const uint32_t pin = data_memory_read(PIN);
	
	for (uint8_t i = 0; i < CPU_REGISTER_ADDRESS_WIDTH; i++)
	{
		if (read(&pin, i) != read(&pin_last_value, i))
		{
			const uint32_t pcmsk = data_memory_read(PCMSK);
			
			if (read(&pcmsk, i))
			{
				uint32_t ifr = data_memory_read(IFR);
				set(&ifr, PCIF);
				data_memory_write(IFR, ifr);
				break;	
			}
		}
	}
	
	pin_last_value = pin;
	return;
}

static inline void check_for_interrupt_requests(void)
{
	if (read(&sr, I))
	{
		uint32_t ifr       = data_memory_read(IFR);
		const uint32_t icr = data_memory_read(ICR);
		
		if (read(&ifr, PCIF) && read(&icr, PCIE))
		{
			clr(&ifr, PCIF);
			data_memory_write(IFR, ifr);
			generate_interrupt(PCI_vect);
		}
	}
	return;
}

static inline void generate_interrupt(const uint16_t interrupt_vector)
{
	stack_push(pc);
	pc = interrupt_vector;
	clr(&sr, I);
	return;
}

static inline void return_from_interrupt(void)
{
	pc = stack_pop();
	set(&sr, I);
	return;
}