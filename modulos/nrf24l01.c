#include <xc.h>
#include <stdint.h>
#include "../controladores.h"
#include "nrf24l01.h"

#define _XTAL_FREQ 16000000UL

#define NRF24L01_CE         LATCbits.LATC0
#define NRF24L01_TRIS_CE    TRISCbits.TRISC0

#define NRF24L01_CSN        LATCbits.LATC1
#define NRF24L01_TRIS_CSN   TRISCbits.TRISC1



// This data type sets the address data pipe 0.
unsigned char ADDRESS_DATA_PIPE0[5] = {0x05,0x04,0x03,0x02,0x01};

void NRF24L01_WriteRegister(unsigned char Mnemonic, unsigned char value)
{
	NRF24L01_CSN = 0;
	SPI1_Write(W_REGISTER | Mnemonic);
	SPI1_Write(value);
	NRF24L01_CSN = 1;       
}

unsigned char NRF24L01_ReadRegister(unsigned char Mnemonic)
{
	unsigned char byte0;
	NRF24L01_CSN = 0; 
	SPI1_Write(R_REGISTER | Mnemonic);
	byte0 = SPI1_Read();
	NRF24L01_CSN = 1; 
	return byte0;
}

void NRF24L01_WriteBuffer(unsigned char data, unsigned char *buffer, unsigned char bytes)
{
	unsigned char i;
	NRF24L01_CSN = 0;                                    
	SPI1_Write(data);                       
	for(i = 0; i < bytes; i++)     
	{
		SPI1_Write(*buffer);
		buffer++;
	}
	NRF24L01_CSN = 1;
}

void NRF24L01_ReadBuffer(unsigned char data, unsigned char *buffer, unsigned char bytes)
{
	unsigned char i;
	NRF24L01_CSN = 0;                                    
	SPI1_Write(data);                       
	for(i = 0; i < bytes; i++)     
	{
		*buffer = SPI1_Read();
		buffer++;
	}
	*buffer = 0;
	NRF24L01_CSN = 1;
}

void NRF24L01_Init(unsigned char mode, unsigned char rf_channel)
{
	NRF24L01_CSN = 1;
	NRF24L01_CE = 0;
	NRF24L01_TRIS_CSN = 0; 
	NRF24L01_TRIS_CE = 0;
//	NRF24L01_CSN = 1;
//	NRF24L01_CE = 0;
	__delay_ms(100);  
	NRF24L01_WriteRegister(CONFIG, 0x0A);
	__delay_ms(10);
	NRF24L01_WriteRegister(EN_AA, 0x01);
	NRF24L01_WriteRegister(EN_RXADDR, 0x01);
	NRF24L01_WriteRegister(SETUP_AW, 0x03);
	NRF24L01_WriteRegister(SETUP_RETR, 0x00);
	NRF24L01_SetChannel(rf_channel);
	NRF24L01_WriteRegister(RF_SETUP, 0x0E);
	//NRF24L01_WriteRegister(STATUSS, 0x70);
	NRF24L01_WriteBuffer(W_REGISTER | RX_ADDR_P0, ADDRESS_DATA_PIPE0, 5);
	NRF24L01_WriteBuffer(W_REGISTER | TX_ADDR, ADDRESS_DATA_PIPE0, 5); 
	NRF24L01_WriteRegister(RX_PW_P0, PAYLOAD_BYTES); 
	//NRF24L01_Flush();
	__delay_ms(100);
	NRF24L01_SetMode(mode);
	__delay_ms(100);
}

void NRF24L01_SetMode(unsigned char mode)
{
	NRF24L01_Flush();
	NRF24L01_WriteRegister(STATUSS, 0x70); // Clear STATUS.    
	switch(mode)
	{
		case 1:
			NRF24L01_WriteRegister(CONFIG, 0x0F);  // RX Control
			NRF24L01_CE = 1;
			break;
		case 2:
			NRF24L01_WriteRegister(CONFIG, 0x0E);  // TX Control 
			NRF24L01_CE = 0;
			break;
	}
}

void NRF24L01_SendData(unsigned char *buffer)
{
	NRF24L01_SetMode(TX_MODE);    
	NRF24L01_WriteBuffer(W_TX_PAYLOAD, buffer, PAYLOAD_BYTES);
	NRF24L01_CE = 1; 
	__delay_ms(1); 
	NRF24L01_CE = 0;
}

unsigned char NRF24L01_DataReady(void)
{
	return ((NRF24L01_ReadRegister(STATUSS) & 0x40) == 0x40) ? 0 : 1;
}

void NRF24L01_ReadData(unsigned char *buffer)
{
	NRF24L01_ReadBuffer(R_RX_PAYLOAD, buffer, PAYLOAD_BYTES);
	NRF24L01_WriteRegister(STATUSS, 0x70); // Clear STATUS.
	NRF24L01_Flush();
}

void NRF24L01_SetChannel(unsigned char rf_channel)
{
	NRF24L01_WriteRegister(RF_CH, rf_channel);
}

unsigned char NRF24L01_GetChannel(void)
{
	return NRF24L01_ReadRegister(RF_CH);
}

void NRF24L01_StandbyI(void)
{   
	NRF24L01_WriteRegister(CONFIG, 0x0A);
	__delay_ms(10);
}

void NRF24L01_Flush(void)
{
	NRF24L01_CSN = 0; 
	SPI1_Write(FLUSH_TX);
	NRF24L01_CSN = 1; 
	__delay_ms(1);
	NRF24L01_CSN = 0; 
	SPI1_Write(FLUSH_RX);
	NRF24L01_CSN = 1; 
}


