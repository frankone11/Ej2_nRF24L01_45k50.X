/* 
 * File:   uart1.h
 * Author: paco
 *
 * Created on 3 de enero de 2021, 12:37 PM
 */

#ifndef __TCB_UART1__
#define	__TCB_UART1__

#ifdef	__cplusplus
extern "C" {
#endif

void UART1_Inicializa(void);
void UART1_Desinicializa(void);
void UART1_Envia(uint8_t dato);
uint8_t UART1_Recibe(void);
void UART1_Espera(void);

#ifdef	__cplusplus
}
#endif

#endif	/* __TCB_UART1__ */

