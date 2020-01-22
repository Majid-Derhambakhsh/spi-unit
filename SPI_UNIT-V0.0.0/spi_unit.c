/*
------------------------------------------------------------------------------
~ File   : spi_unit.c
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

#include "spi_unit.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Variable ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
static volatile uint8_t  *g_spi_txdata_it   = 0;
static volatile uint8_t  *g_spi_rxdata_it   = 0;
static volatile uint16_t g_spi_data_size_it = 0;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Enum ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
enum /* Bit set enum */
{
	
	_SPI_1_BIT_SET = 1U,
	_SPI_2_BIT_SET = 3U
	
}SPI_BitSet;

enum /* Bit shift enum */
{
	
	_SPI2X_SHIFT = 2U
	
}SPI_BitShift;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Prototypes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void (*SPI_DataControl_IT)(void);

void SPI_DataControl_IT_Transmit(void);

void SPI_DataControl_IT_Receive(void);

void SPI_DataControl_IT_TransmitReceive(void);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Interrupt control ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
_INTERRUPT(_SPI_IT_VECT)
{
	
	SPI_DataControl_IT();
	SPI_TxCpltCallback();
	
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void SPI_Init(SPI_InitTypeDef *_spi_cfg)
{
	/* Set MOSI and SCK output, all others input */
	_DDR_SPI = (1 << _MOSI_PIN) | (1 << _SCK_PIN);
	
	/* Initialize spi */
	SPCR  = ((uint8_t)_spi_cfg->FirstBit << DORD) | ((uint8_t)_spi_cfg->Mode << MSTR) | ((uint8_t)_spi_cfg->ClockPolarity << CPOL) | ((uint8_t)_spi_cfg->ClockPhase << CPHA) | ((uint8_t)_spi_cfg->ClockFrequency & _SPI_2_BIT_SET);
	SPSR |= ((uint8_t)_spi_cfg->ClockFrequency >> _SPI2X_SHIFT) & _SPI_1_BIT_SET; 
	
}
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

void SPI_DeInit(void)
{
	
	SPCR  = 0;
	
}
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

void SPI_DefaultMasterInit(void)
{
	/* Set MOSI and SCK output, all others input */
	_DDR_SPI = (1 << _MOSI_PIN) | (1 << _SCK_PIN);
	
	/* Enable SPI, Master, set clock rate fcpu/16 */
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
	
}
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

void SPI_DefaultSlaveInit(void)
{
	/* Set MOSI and SCK output, all others input */
	_DDR_SPI = (1 << _MISO_PIN);
	
	/* Enable SPI, Master, set clock rate fcpu/16 */
	SPCR = (1 << SPE);
	
}
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

void SPI_Transmit(uint8_t *_pdata, uint16_t _size, uint32_t _timeout)
{
	
	for (; _size > 0; _size--) /* Copy data loop */
	{
		/* Start transmission */
		SPDR = *_pdata;
		
		/* Wait for transmission complete */
		for (; (!(SPSR & (1<<SPIF))) && (_timeout > 0); _timeout--) /* Timeout loop */
		{
			_DELAY_MS(1);
		}
		
		/* ------------------------ */
		_pdata++;
		
	}
	
}
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

void SPI_Transmit_IT(uint8_t *_pdata, uint16_t _size)
{
	
	if (g_spi_data_size_it == 0)
	{
		SPI_DataControl_IT = SPI_DataControl_IT_Transmit;
		
		/* ------------------------ */
		g_spi_txdata_it      = (_pdata + 1);
		g_spi_data_size_it = --_size;
		
		/* Start transmission */
		SPDR = *_pdata;
		
	}
	
}
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

void SPI_Receive(uint8_t *_pdata, uint16_t _size, uint32_t _timeout)
{
	
	for (; _size > 0; _size--) /* Copy data loop */
	{
		/* Wait for reception complete */
		for (; (!(SPSR & (1<<SPIF))) && (_timeout > 0); _timeout--) /* Timeout loop */
		{
			_DELAY_MS(1);
		}
		
		/* ------------------------ */
		*_pdata = SPDR;
		_pdata++;
		
	}
	
}
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

void SPI_Receive_IT(uint8_t *_pdata, uint16_t _size)
{
	
	if (g_spi_data_size_it == 0)
	{
		SPI_DataControl_IT = SPI_DataControl_IT_Receive;
		
		/* ------------------------ */
		g_spi_rxdata_it    = _pdata;
		g_spi_data_size_it = _size;
		
	}
	
}
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

void SPI_TransmitReceive(uint8_t *_tx_data, uint8_t *_rx_data, uint16_t _size, uint32_t _timeout)
{
	
	for (; _size > 0; _size--)
	{
		/* Start transmission */
		SPDR = *_tx_data;
		
		/* Wait for transmission complete */
		for (; (!(SPSR & (1<<SPIF))) && (_timeout > 0); _timeout--)
		{
			_DELAY_MS(1);
		}
		
		/* ------------------------ */
		*_rx_data = SPDR;
		
		_rx_data++;
		_tx_data++;
		
	}
	
}
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

void SPI_TransmitReceive_IT(uint8_t *_tx_data, uint8_t *_rx_data, uint16_t _size)
{
	
	if (g_spi_data_size_it == 0)
	{
		SPI_DataControl_IT = SPI_DataControl_IT_TransmitReceive;
		
		/* ------------------------ */
		g_spi_rxdata_it    = _rx_data;
		g_spi_txdata_it    = (_tx_data + 1);
		g_spi_data_size_it = --_size;
		
		/* Start transmission */
		SPDR = *_tx_data;
		
	}
	
}
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

/* ............... IT Data Controls ............... */

void SPI_DataControl_IT_Transmit(void)
{
	
	if (g_spi_data_size_it > 0)
	{
		
		SPDR = *g_spi_txdata_it;
		g_spi_txdata_it++;
		
		g_spi_data_size_it--;
		
	}
	
}

void SPI_DataControl_IT_Receive(void)
{
	
	if (g_spi_data_size_it > 0)
	{
		
		*g_spi_rxdata_it = SPDR;
		g_spi_rxdata_it++;
		
		g_spi_data_size_it--;
		
	}
	
}

void SPI_DataControl_IT_TransmitReceive(void)
{
	
	if (g_spi_data_size_it > 0)
	{
		
		SPDR = *g_spi_txdata_it;
		*g_spi_rxdata_it = SPDR;
		
		g_spi_txdata_it++;
		g_spi_rxdata_it++;
		g_spi_data_size_it--;
		
	}
	else
	{
		*g_spi_rxdata_it = SPDR;
	}
	
}

