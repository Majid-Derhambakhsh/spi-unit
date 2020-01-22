/*
------------------------------------------------------------------------------
~ File   : spi_unit_conf.h
~ Author : Majid Derhambakhsh
~ Version: V0.0.0
~ Created: 01/22/2020 09:22:00 PM
~ Brief  :
~ Support: 
           E-Mail : Majid.Derhambakhsh@gmail.com (subject: Embedded Library Support)
		   
           Github : https://github.com/Majid-Derhambakhsh
------------------------------------------------------------------------------
~ Description:    SPI driver for AVR microcontroller

~ Attention  :    

~ Changes    :
------------------------------------------------------------------------------
*/

#ifndef __SPI_UNIT_CONF_H_
#define __SPI_UNIT_CONF_H_

/* ~~~~~~~~~~~~~~~~~~~~ Configuration ~~~~~~~~~~~~~~~~~~~~ */

/* ------ SPI DDR Register ------ */
#define _DDR_SPI   DDRB

/* ---------- SPI Pins ---------- */
#define _MOSI_PIN  5
#define _MISO_PIN  6
#define _SCK_PIN   7

/* 
	Guide  :
			_DDR_SPI  : SPI DDRx Register
			_MOSI_PIN : SPI MOSI pin number
			_MISO_PIN : SPI MISO pin number
			_SCK_PIN  : SPI SCK pin number
			
	Example:
			#define _DDR_SPI  DDRB
			
			#define _MOSI_PIN 5
			#define _MISO_PIN 6
			#define _SCK_PIN  7
*/

/* Move this function to your program file */
void SPI_TxCpltCallback(void){}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#endif /* __SPI_UNIT_CONF_H_ */
