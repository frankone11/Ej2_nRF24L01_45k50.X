/* 
 * File:   spi1.h
 * Author: paco
 *
 * Created on 25 de abril de 2022, 08:27 PM
 */

#ifndef __TCB_SPI1__
#define	__TCB_SPI1__

#ifdef	__cplusplus
extern "C" {
#endif

	void SPI1_Inicializa(void);
	uint8_t SPI1_Transceive(uint8_t dato);

#ifdef	__cplusplus
}
#endif

#define SPI1_Init() SPI1_Inicializa()
#define SPI1_Write(data) SPI1_Transceive(data)
#define SPI1_Read() SPI1_Transceive(0x00U)

#endif	/* __TCB_SPI1__ */

