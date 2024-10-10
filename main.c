/*
 * File:   main.c
 * Author: paco
 *
 * Created on 25 de abril de 2022, 08:21 PM
 */
#include <xc.h>
#include <stdio.h>
#include "tcb_principal.h"
#define _XTAL_FREQ 16000000UL

unsigned char i;
char buffer1[20];
unsigned char bufferTX[32];

void main(void)
{
	TCB_Sistema_Inicializa();
	UART1_Inicializa();
	SPI1_Inicializa(); 
	
	printf("TCB Ej2. nRF24L01 (TX)\r\n\r\n");
	printf("Iniciando nRF24L01.\r\n");
	
	NRF24L01_Init(TX_MODE, 0x40); 
	printf("Se van a enviar datos...\r\n");
	while(1)
	{
		printf("**********\r\n");
		bufferTX[0] = 1;   
		for(i = 0; i < 8; i++)
		{
			NRF24L01_SendData(bufferTX); 
			printf("Enviando: 0x%02X (%03d)\r\n", bufferTX[0], bufferTX[0]);
			bufferTX[0] = (unsigned char)(bufferTX[0] << 1U);
			__delay_ms(300);  
		}
		bufferTX[0] = 128;
		for(i = 0; i < 6; i++)
		{
			bufferTX[0] = (unsigned char)(bufferTX[0] >> 1U);
			NRF24L01_SendData(bufferTX); 
			printf("Enviando: 0x%02X (%03d)\r\n", bufferTX[0], bufferTX[0]);
			__delay_ms(300);
		}
	}
}

void putch(char c)
{
	UART1_Envia(c);
	UART1_Espera();
}