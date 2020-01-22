/*
------------------------------------------------------------------------------
~ File   : spi_unit.h
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

#ifndef __SPI_UNIT_H_
#define __SPI_UNIT_H_

/*----------------------------------------------------------*/

#ifdef __cplusplus

extern "C"
{

#endif /* __cplusplus */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Include ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#include <stdint.h> /* Import standard integer type */

#include "spi_unit_conf.h" /* Import config file */

/*----------------------------------------------------------*/

#ifdef __CODEVISIONAVR__  /* Check compiler */

#pragma warn_unref_func- /* Disable 'unused function' warning */

#include <io.h>            /* Import AVR IO library */
#include <delay.h>         /* Import delay library */

/*----------------------------------------------------------*/

#elif defined(__GNUC__)   /* Check compiler */

#pragma GCC diagnostic ignored "-Wunused-function" /* Disable 'unused function' warning */

#include <avr/io.h>        /* Import AVR IO library */
#include <util/delay.h>    /* Import delay library */

/*----------------------------------------------------------*/

#else                     /* Compiler not found */

#error Compiler not supported  /* Send error */

#endif /* __CODEVISIONAVR__ */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ------ SPI Exported Macros ------ */
#define __SPI_ENABLE     {SPCR |= (1U << SPE);}
#define __SPI_DISABLE    {SPCR &= ~(1U << SPE);}
#define __SPI_ENABLE_IT  {SPCR |= (1U << SPIE);}
#define __SPI_DISABLE_IT {SPCR &= ~(1U << SPIE);}

/* ---------------------------- Public ---------------------------- */
/* ---------------------- Define by compiler ---------------------- */

#ifdef __CODEVISIONAVR__ /* Check compiler */
	
	#define _SPI_IT_VECT SPI_STC
	
	#ifndef _INTERRUPT
		#define _INTERRUPT(vect)  interrupt [vect] void spi_isr(void)
	#endif
	
	#ifndef _DELAY_MS
		#define _DELAY_MS(x)    delay_ms(x)
	#endif /* _DELAY_MS */
	
#elif defined(__GNUC__) /* Check compiler */
	
	#define _SPI_IT_VECT SPI_STC_vect
	
	#ifndef _INTERRUPT
		#define _INTERRUPT(vect)  ISR(vect)
	#endif
	
	#ifndef _DELAY_MS
		#define _DELAY_MS(x)    _delay_ms(x)
	#endif /* _DELAY_MS */
	
#endif /* __CODEVISIONAVR__ */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Enum ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

typedef enum /* SPI Modes */
{
	
	_SPI_MODE_SLAVE  = 0,
	_SPI_MODE_MASTER = 1U
	
}SPI_ModeTypeDef;

typedef enum /* SPI Data Order Modes */
{
	
	_SPI_FIRSTBIT_MSB = 0,
	_SPI_FIRSTBIT_LSB = 1U
	
}SPI_DataOrderTypeDef;

typedef enum /* SPI Clock Polarity Modes */
{
	
	_SPI_CLOCKPOLARITY_LOW  = 0,
	_SPI_CLOCKPOLARITY_HIGH = 1U
	
}SPI_CLKPolarityTypeDef;

typedef enum /* SPI Clock Phase Modes */
{
	
	_SPI_CLOCKPHASE_FIRSTEDGE = 0,
	_SPI_CLOCKPHASE_LASTEDGE  = 1U
	
}SPI_CLKPhaseTypeDef;

typedef enum /* SPI Clock Rates */
{
	
	_SPI_CLOCKRATE_FCPU_2   = 4U,
	_SPI_CLOCKRATE_FCPU_4   = 0,
	_SPI_CLOCKRATE_FCPU_8   = 5U,
	_SPI_CLOCKRATE_FCPU_16  = 1U,
	_SPI_CLOCKRATE_FCPU_32  = 6U,
	_SPI_CLOCKRATE_FCPU_64  = 2U,
	_SPI_CLOCKRATE_FCPU_128 = 3U,
	
}SPI_CLKRateTypeDef;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

typedef struct /* structure that contains the configuration information for the specified SPI properties */
{
	
	SPI_ModeTypeDef        Mode           : 1;
	SPI_DataOrderTypeDef   FirstBit       : 1;
	SPI_CLKPhaseTypeDef    ClockPhase     : 1;
	SPI_CLKPolarityTypeDef ClockPolarity  : 1;
	SPI_CLKRateTypeDef     ClockFrequency : 3;
	
}SPI_InitTypeDef;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Prototype ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void SPI_Init(SPI_InitTypeDef *_spi_cfg);
/*
	Guide   :
			Function description	Initialize the SPI according to the specified parameters in the
									SPI_InitTypeDef and initialize the associated handle.
			
			Parameters
									* _spi_cfg : pointer to a SPI_InitTypeDef structure that contains
												 the configuration information for SPI module.
									
			Return Values
									-
			
	Example :
			SPI_InitTypeDef spi_cfg;
			
			spi_cfg.Mode           = _SPI_MODE_MASTER;
			spi_cfg.FirstBit       = _SPI_FIRSTBIT_MSB;
			spi_cfg.ClockFrequency = _SPI_CLOCKRATE_FCPU_16;
			spi_cfg.ClockPhase     = _SPI_CLOCKPHASE_FIRSTEDGE;
			spi_cfg.ClockPolarity  = _SPI_CLOCKPOLARITY_HIGH;
			
			SPI_Init(&spi_cfg);
			
*/

void SPI_DeInit(void);
/*
	Guide   :
			Function description	De Initialize the SPI peripheral.
			
			Parameters
									-
									
			Return Values
									-
			
	Example :
			
			SPI_DeInit();
			
*/

void SPI_DefaultMasterInit(void);
/*
	Guide   :
			Function description	Initialize the SPI according to the default parameters in the
									Atmel datasheet
			
			Parameters
									-
									
			Return Values
									-
			
	Example :
			
			SPI_DefaultMasterInit();
			
*/

void SPI_DefaultSlaveInit(void);
/*
	Guide   :
			Function description	Initialize the SPI according to the default parameters in the
									Atmel datasheet
			
			Parameters
									-
									
			Return Values
									-
			
	Example :
			
			SPI_DefaultSlaveInit();
			
*/

void SPI_Transmit(uint8_t *_pdata, uint16_t _size, uint32_t _timeout);
/*
	Guide   :
			Function description	Transmit an amount of data in blocking mode.
			
			Parameters
									* _pdata   : pointer to data buffer
									* _size    : amount of data to be sent
									* _timeout : Timeout duration
									
			Return Values
									-
			
	Example :
			
			SPI_Transmit("Transmit Test", 13, 1000);
			
*/

void SPI_Transmit_IT(uint8_t *_pdata, uint16_t _size);
/*
	Guide   :
			Function description	Transmit an amount of data in non-blocking mode with Interrupt.
			
			Parameters
									* _pdata   : pointer to data buffer
									* _size    : amount of data to be sent
									
			Return Values
									-
			
	Example :
			
			uint8_t data_for_transmit[50];
			
			SPI_Transmit_IT(data_for_transmit, 50);
			
*/

void SPI_Receive(uint8_t *_pdata, uint16_t _size, uint32_t _timeout);
/*
	Guide   :
			Function description	Receive an amount of data in blocking mode.
			
			Parameters
									* _pdata   : pointer to data buffer
									* _size    : amount of data to be received
									* _timeout : Timeout duration
									
			Return Values
									-
			
	Example :
			
			uint8_t received_data[20];
			
			SPI_Receive(received_data, 10, 1000);
			
*/

void SPI_Receive_IT(uint8_t *_pdata, uint16_t _size);
/*
	Guide   :
			Function description	Receive an amount of data in non-blocking mode with Interrupt.
			
			Parameters
									* _pdata   : pointer to data buffer
									* _size    : amount of data to be received
									
			Return Values
									-
			
	Example :
			
			uint8_t received_data[100];
			
			SPI_Receive_IT(received_data, 100);
			
*/

void SPI_TransmitReceive(uint8_t *_tx_data, uint8_t *_rx_data, uint16_t _size, uint32_t _timeout);
/*
	Guide   :
			Function description	Transmit and Receive an amount of data in blocking mode
			
			Parameters
									* _tx_data : pointer to transmission data buffer
									* _rx_data : pointer to reception data buffer
									* _size    : amount of data to be sent and received
									* _timeout : Timeout duration
									
			Return Values
									-
			
	Example :
			
			uint8_t data_for_transmit[15];
			uint8_t received_data[15];
			
			SPI_TransmitReceive(data_for_transmit, received_data, 8, 1000);
			
*/

void SPI_TransmitReceive_IT(uint8_t *_tx_data, uint8_t *_rx_data, uint16_t _size);
/*
	Guide   :
			Function description	Transmit and Receive an amount of data in non-blocking mode
									with Interrupt.
			
			Parameters
									* _tx_data : pointer to transmission data buffer
									* _rx_data : pointer to reception data buffer
									* _size    : amount of data to be sent and received
									
			Return Values
									-
			
	Example :
			
			uint8_t received_data[15];
			
			SPI_TransmitReceive_IT("Hello!!!", received_data, 8);
			
*/

void SPI_TxCpltCallback(void);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ End of the program ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#ifdef __cplusplus

}

#endif /* __cplusplus */

#endif
