/********************************************************************************
* cpu.h: Inneh�ller definitioner, samt addresser till OP-koder samt register.
*        Samt funktioner f�r att etts�lla, nollst�lla och l�sa dom olika 
*        registren, och en enumeration f�r sj�lva CPU'ns olika "states".
********************************************************************************/
#ifndef CPU_H_
#define CPU_H_

/* Inkluderingsderiktiv */
#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>

#define CPU_REGISTER_ADDRESS_WIDTH 32

#define NOP   0x00         /* Ingen operation */
#define LDI   0x01         /* Laddar in en konstant i ett cpu-register */
#define LD    0x02         /* Kopierar inneh�llet fr�n ett cpu-register till ett annat */
#define IN    0x03         /* L�ser fr�n ett I/O register */
#define OUT   0x04         /* Skrivar inneh�llet fr�n ett cpu-register till I/O portar */
#define OUTI  0x05         /* Skriver en konstant till dataminnet */
#define CLR   0x06         /* Nollst�ller ett CPU register */
#define ORI   0x07         /* Utf�r en OR operation med en konstant */
#define OR    0x08         /* Utf�r en OR operation med ett CPU-register */
#define ANDI  0x09         /* Utf�r en AND operation med en konstant */
#define AND   0x0A         /* Utf�r en AND operation med ett CPU-register */
#define XORI  0x0B         /* Utf�r en XOR operation med en konstant */
#define XOR   0x0C         /* Utf�r en XOR operation med ett CPU-register */
#define ADDI  0x0D         /* Utf�r en addition med en konstant */
#define ADD   0x0E         /* Utf�r en addition med ett CPU-register */
#define SUBI  0x0F         /* Utf�r en subtraktion med en konstant */
#define SUB   0x10         /* Utf�r en subtraktion med ett CPU-register */

#define INC   0x11         /* Inkrementera ett v�rde i ett CPU-register */
#define DEC   0x12         /* Dekrementera ett v�rde i ett CPU-register */
#define COMPI 0x13         /* J�mnf�r v�rdet i ett CPU-register med en konstant */
#define COMP  0x14         /* J�mnf�r v�rdet i ett CPU-register med ett annat CPU-register */
#define JMP   0x15         /* Hoppar till en specifik adress */
#define BREQ  0x16         /* Hoppar till en specifik adress om resultatet fr�n j�mnf�relsen �r noll */
#define BRNE  0x17         /* Hoppar till en specifik adress om resultatet fr�n j�mnf�relsen inte �r noll */
#define BRGT  0x18         /* Hoppar till en specifik adress om resultatet fr�n j�mnf�relsen �r st�rre �n noll */
#define BRLE  0x19         /* Hoppar till en specifik adress om resultatet fr�n j�mnf�relsen �r mindre eller lika med noll */
#define BRLT  0x1A         /* Hoppar till en specifik adress om resultatet fr�n j�mnf�relsen �r mindre �n noll */

#define CALL  0x1B         /* Hoppar till en subrutin och sparar �terhopps adressen p� stacken */
#define RET   0x1C         /* Retunerar fr�n en subrutin efter POP-instruktion, returadressen laddas i fr�n stacken */
#define RETI  0x1D         /* Retunerar fr�n en avbrottsrutin, adress laddad ifr�n stacken, Global Interrupt Flag is set */

#define PUSH  0x1E         /* Sparar inneh�llet av ett register p� stacken, stack-pekaren �r post-dekrementerad med 1 efter PUSH instr. */
#define POP   0x1F         /* Laddar p� en byte p� ett register fr�n stacken, stack-pekaren �r pre-inkrementerad med 1 f�re POP instr. */
#define LSL   0x20         /* Skiftar alla bitarna i ett register ett steg �t v�nster, g�nger 2 */
#define LSR   0x21         /* Skifter alla bitarna i ett register ett steg �t h�ger, delat med 2 */
#define SEI   0x22         /* Aktiverar avbrott globalt, i.e Sets the Global Interrupt Flag (1) in SREG */
#define CLI   0x23         /* Inaktiverar avbrott globalt, i.e Clears the Global Interrupt Flag(1) */
#define STS   0x24         /* store to data space */

#define I 5                /* Avbrottsflaggan */
#define S 4                /* Signedflaggan */
#define N 3                /* Negativflaggan */
#define Z 2                /* Nollflaggan */
#define V 1                /* Overflowflaggan */
#define C 0                /* Carryflaggan */

#define RESET_vect  0x00   /* �terst�llnings vektor  */
#define PCI_vect    0x02   /* Pin change interrupt vektor f�r hela PORTA */

#define DDR         0x00   /* Datariktningsregister f�r PORTA */ 
#define PORT        0x01   /* Data register f�r I/O PORTA */
#define PIN         0x02   /* Pin insignal register f�r PORTA */ 
#define ICR         0x03   /* Avbrotts kontrol register */
#define IFR         0x04   /* Avbrotts flagga register */
#define PCMSK       0x05   /* Pin change avbrotts register */

#define PCIE 0             /* Pin change interrupt enable */
#define PCIF 0             /* Pin change interrupt flag */

#define PORT0  0           /* PIN 0  = PORTD0 */
#define PORT1  1           /* PIN 1  = PORTD1 */
#define PORT2  2           /* PIN 2  = PORTD2 */
#define PORT3  3           /* PIN 3  = PORTD3 */
#define PORT4  4           /* PIN 4  = PORTD4 */
#define PORT5  5           /* PIN 5  = PORTD5 */
#define PORT6  6           /* PIN 6  = PORTD6 */
#define PORT7  7           /* PIN 7  = PORTD7 */
#define PORT8  8           /* PIN 8  = PORTB0 */
#define PORT9  9           /* PIN 9  = PORTB1 */
#define PORT10 10          /* PIN 10 = PORTB2 */
#define PORT11 11          /* PIN 11 = PORTB3 */
#define PORT12 12          /* PIN 12 = PORTB4 */
#define PORT13 13          /* PIN 13 = PORTB5 */ 

/* Register f�r CPU:n */
#define R0  0x00
#define R1  0x01
#define R2  0x02
#define R3  0x03
#define R4  0x04
#define R5  0x05
#define R6  0x06
#define R7  0x07
#define R8  0x08
#define R9  0x09
#define R10 0x0A
#define R11 0x0B
#define R12 0x0C
#define R13 0x0D
#define R14 0x0E
#define R15 0x0F
#define R16 0x10
#define R17 0x11
#define R18 0x12
#define R19 0x13
#define R20 0x14
#define R21 0x15
#define R22 0x16
#define R23 0x17
#define R24 0x18
#define R25 0x19



/********************************************************************************
* set: Ett-st�ller en bit i ett register utan att p�verka andra bitar.
*
*                        - reg: Reference till registret
*                        - bit: Biten som skall ett-st�llas
********************************************************************************/
static inline void set(volatile uint32_t* reg, const uint8_t bit)
{
	*reg |= (1ULL << bit);
	return;
}

/********************************************************************************
* clr: Nollst�ller en bit i ett register utan att p�verka andra bitar.
*
*                        - reg: Reference till registret
*                        - bit: Biten som skall ett-st�llas
********************************************************************************/
static inline void clr(volatile uint32_t* reg, const uint8_t bit)
{
	*reg &= ~(1ULL << bit);
	return;
}

/********************************************************************************
* read: L�sar en bit (ett eller noll) i et 32-bitars register
*
*                        - reg: Reference till registret
*                        - bit: Biten som skal ett-st�llas
********************************************************************************/
static inline bool read(const volatile uint32_t* reg, const uint8_t bit)
{
	return *reg & (1UL << bit);
}

/********************************************************************************
* read64: L�sar en bit (ett eller noll) i ett 64-bitars register
*
*                        - reg: Reference till registret
*                        - bit: Biten som skall ett-st�llas
********************************************************************************/
static inline bool read64(const volatile uint64_t* reg, const uint8_t bit)
{
	return *reg & (1UL << bit);
}

enum state
{
   FETCH,
   DECODE,
   EXECUTE
   	
};

#endif /* CPU_H_ */