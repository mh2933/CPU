/********************************************************************************
* cpu.h: Innehåller definitioner, samt addresser till OP-koder samt register.
*        Samt funktioner för att ettsälla, nollställa och läsa dom olika 
*        registren, och en enumeration för själva CPU'ns olika "states".
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
#define LD    0x02         /* Kopierar innehållet från ett cpu-register till ett annat */
#define IN    0x03         /* Läser från ett I/O register */
#define OUT   0x04         /* Skrivar innehållet från ett cpu-register till I/O portar */
#define OUTI  0x05         /* Skriver en konstant till dataminnet */
#define CLR   0x06         /* Nollställer ett CPU register */
#define ORI   0x07         /* Utför en OR operation med en konstant */
#define OR    0x08         /* Utför en OR operation med ett CPU-register */
#define ANDI  0x09         /* Utför en AND operation med en konstant */
#define AND   0x0A         /* Utför en AND operation med ett CPU-register */
#define XORI  0x0B         /* Utför en XOR operation med en konstant */
#define XOR   0x0C         /* Utför en XOR operation med ett CPU-register */
#define ADDI  0x0D         /* Utför en addition med en konstant */
#define ADD   0x0E         /* Utför en addition med ett CPU-register */
#define SUBI  0x0F         /* Utför en subtraktion med en konstant */
#define SUB   0x10         /* Utför en subtraktion med ett CPU-register */

#define INC   0x11         /* Inkrementera ett värde i ett CPU-register */
#define DEC   0x12         /* Dekrementera ett värde i ett CPU-register */
#define COMPI 0x13         /* Jämnför värdet i ett CPU-register med en konstant */
#define COMP  0x14         /* Jämnför värdet i ett CPU-register med ett annat CPU-register */
#define JMP   0x15         /* Hoppar till en specifik adress */
#define BREQ  0x16         /* Hoppar till en specifik adress om resultatet från jämnförelsen är noll */
#define BRNE  0x17         /* Hoppar till en specifik adress om resultatet från jämnförelsen inte är noll */
#define BRGT  0x18         /* Hoppar till en specifik adress om resultatet från jämnförelsen är större än noll */
#define BRLE  0x19         /* Hoppar till en specifik adress om resultatet från jämnförelsen är mindre eller lika med noll */
#define BRLT  0x1A         /* Hoppar till en specifik adress om resultatet från jämnförelsen är mindre än noll */

#define CALL  0x1B         /* Hoppar till en subrutin och sparar återhopps adressen på stacken */
#define RET   0x1C         /* Retunerar från en subrutin efter POP-instruktion, returadressen laddas i från stacken */
#define RETI  0x1D         /* Retunerar från en avbrottsrutin, adress laddad ifrån stacken, Global Interrupt Flag is set */

#define PUSH  0x1E         /* Sparar innehållet av ett register på stacken, stack-pekaren är post-dekrementerad med 1 efter PUSH instr. */
#define POP   0x1F         /* Laddar på en byte på ett register från stacken, stack-pekaren är pre-inkrementerad med 1 före POP instr. */
#define LSL   0x20         /* Skiftar alla bitarna i ett register ett steg åt vänster, gånger 2 */
#define LSR   0x21         /* Skifter alla bitarna i ett register ett steg åt höger, delat med 2 */
#define SEI   0x22         /* Aktiverar avbrott globalt, i.e Sets the Global Interrupt Flag (1) in SREG */
#define CLI   0x23         /* Inaktiverar avbrott globalt, i.e Clears the Global Interrupt Flag(1) */
#define STS   0x24         /* store to data space */

#define I 5                /* Avbrottsflaggan */
#define S 4                /* Signedflaggan */
#define N 3                /* Negativflaggan */
#define Z 2                /* Nollflaggan */
#define V 1                /* Overflowflaggan */
#define C 0                /* Carryflaggan */

#define RESET_vect  0x00   /* Återställnings vektor  */
#define PCI_vect    0x02   /* Pin change interrupt vektor för hela PORTA */

#define DDR         0x00   /* Datariktningsregister för PORTA */ 
#define PORT        0x01   /* Data register för I/O PORTA */
#define PIN         0x02   /* Pin insignal register för PORTA */ 
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

/* Register för CPU:n */
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
* set: Ett-ställer en bit i ett register utan att påverka andra bitar.
*
*                        - reg: Reference till registret
*                        - bit: Biten som skall ett-ställas
********************************************************************************/
static inline void set(volatile uint32_t* reg, const uint8_t bit)
{
	*reg |= (1ULL << bit);
	return;
}

/********************************************************************************
* clr: Nollställer en bit i ett register utan att påverka andra bitar.
*
*                        - reg: Reference till registret
*                        - bit: Biten som skall ett-ställas
********************************************************************************/
static inline void clr(volatile uint32_t* reg, const uint8_t bit)
{
	*reg &= ~(1ULL << bit);
	return;
}

/********************************************************************************
* read: Läsar en bit (ett eller noll) i et 32-bitars register
*
*                        - reg: Reference till registret
*                        - bit: Biten som skal ett-ställas
********************************************************************************/
static inline bool read(const volatile uint32_t* reg, const uint8_t bit)
{
	return *reg & (1UL << bit);
}

/********************************************************************************
* read64: Läsar en bit (ett eller noll) i ett 64-bitars register
*
*                        - reg: Reference till registret
*                        - bit: Biten som skall ett-ställas
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