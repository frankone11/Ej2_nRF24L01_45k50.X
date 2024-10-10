#include <xc.h>
#include <stdint.h>

void UART1_Inicializa()
{
	TXSTA1 = 0x24U;
	RCSTA1 = 0x90U;
	BAUDCONbits.BRG16 = 1;
	SPBRGH1 = 0x01U;
	SPBRG1 = 0xA0U;
}

void UART1_Desinicializa()
{
	TXSTA1bits.TXEN = 0;
	RCSTA1bits.SPEN = 0;
}

void UART1_Envia(uint8_t dato)
{
	TXREG1 = dato;
}

uint8_t UART1_Recibe()
{
	return RCREG1;
}

void UART1_Espera()
{
	while(!TXSTA1bits.TRMT);
}