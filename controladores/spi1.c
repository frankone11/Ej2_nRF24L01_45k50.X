#include <xc.h>
#include <stdio.h>

void SPI1_Inicializa()
{
	SSP1STAT = 0xC0U;
	SSP1CON1 = 0x21U;
}

uint8_t SPI1_Transceive(uint8_t dato)
{
	SSP1BUF = dato;
	while(!SSP1STATbits.BF);  
	return SSP1BUF;
}