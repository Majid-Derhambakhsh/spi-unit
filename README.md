# spi-unit
SPI driver for AVR microcontroller

### Version : 0.0.0

- #### Type : Embedded Software.

- #### Support : AVR microcontroller.

- #### Program Language : C/C++

- #### Properties :

### Initialization and de-initialization functions:
- SPI_Init()
- SPI_DeInit()
- SPI_DefaultMasterInit()
- SPI_DefaultSlaveInit()

### IO operation functions:
- SPI_Transmit()
- SPI_Receive()
- SPI_TransmitReceive()
- SPI_Transmit_IT()
- SPI_Receive_IT()
- SPI_TransmitReceive_IT()

## How to use this driver

### The SPI driver can be used as follows:
1.1  Set SPI DDR Register & Pins in the spi_unit_conf.h header, for example:  

       /* ------ SPI DDR Register ------ */
       #define _DDR_SPI   DDRB  
     
       /* ---------- SPI Pins ---------- */  
       #define _MOSI_PIN  3  
       #define _MISO_PIN  4  
       #define _SCK_PIN   5  

1.2  Move out the SPI_TxCpltCallback() function from spi_unit_conf.h and paste in .c file
       
2.1  Manual initialize:  
-  Declare a SPI_InitTypeDef initialize structure, for example:  
> > SPI_InitTypeDef uspi;
-  Set your configuration in SPI_InitTypeDef, for example:

       uspi.Mode = _SPI_MODE_MASTER  
       uspi.FirstBit = _SPI_FIRSTBIT_MSB;  
       uspi.ClockPhase = _SPI_CLOCKPHASE_FIRSTEDGE;  
       uspi.ClockPolarity = _SPI_CLOCKPOLARITY_LOW;  
       uspi.ClockFrequency = _SPI_CLOCKRATE_FCPU_16;  

-  Initialize the SPI by implementing the SPI_Init() API:
> > SPI_Init(&uspi);

2.2  Default initialize: Initialize the SPI by implementing the SPI_DefaultxInit() API:
      
       SPI_DefaultMasterInit();   
       SPI_DefaultSlaveInit(); 
 
3.1  If using SPI_x_IT functions, enable the SPI Interrupt by __SPI_ENABLE_IT macro, for example:  
          
       // First enable your global interrupt   
       __SPI_ENABLE_IT

4.1  Enable the SPI Peripheral by __SPI_ENABLE macros, for example:  
     
       __SPI_ENABLE

5.1  use the IO operation functions, for example:  

       SPI_Transmit("Hello Word", 10, 1000);  

#### Developer: Majid Derhambakhsh
