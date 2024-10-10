#include <xc.h>
#include <stdio.h>

void TCB_Sistema_Inicializa(void)
{
	ANSELB = 0;
	ANSELC = 0;
	LATCbits.LATC6 = 1;
	LATBbits.LATB1 = 0;
	LATBbits.LATB3 = 0;
	LATBbits.LATB0 = 1;
	TRISCbits.TRISC7 = 1;
	TRISCbits.TRISC6 = 0;
	
	TRISBbits.TRISB0 = 1; //SDI
	TRISBbits.TRISB1 = 0; //SCK
	TRISBbits.TRISB3 = 0; //SDO
	
	WPUB = 1;
	INTCON2bits.nRBPU = 1;
}
