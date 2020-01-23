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
1.1  Manual initialize:  
-  Declare a SPI_InitTypeDef initialize structure, for example:  
> > SPI_InitTypeDef uspi;
-  Set your configuration in SPI_InitTypeDef, for example:  
> > uspi.Mode = _SPI_MODE_MASTER;  
    uspi.FirstBit = _SPI_FIRSTBIT_MSB;  
    uspi.ClockPhase = _SPI_CLOCKPHASE_FIRSTEDGE;  
    uspi.ClockPolarity = _SPI_CLOCKPOLARITY_LOW;  
    uspi.ClockFrequency = _SPI_CLOCKRATE_FCPU_16;  

-  Initialize the SPI by implementing the SPI_Init() API:
> > SPI_Init(&uspi);

1.2  Default initialize: Initialize the SPI by implementing the SPI_DefaultxInit() API:
> > SPI_DefaultMasterInit();  
    SPI_DefaultSlaveInit(); 

#### Developer: Majid Derhambakhsh
