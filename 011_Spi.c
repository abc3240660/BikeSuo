
#include <p24fxxxx.h> 
#include "---_Variables.h"
#include "011_Spi.h"

#define MOSI    _LATG8      //PR21,SDO2,10
#define MISO    _RG7       //PR26,PG7
#define SCK     _LATG6      //PR21,SCK2,11
#define CS1     _LATE7


#define TMOSI   _TRISG8
#define TMISO   _TRISG7
#define TSCK    _TRISG6
#define TCS1    _TRISE7

#define SPI2_DUMMY_DATA 0x0
extern VAR Mobit;
extern NonVolatile NonVolatileDATA;

void clrc663_SPI_init(void)
{
    CS1 = 1;
    SCK = 0;
    MOSI = 0;    
    MISO = 1;

    CS1 = 1;
    TSCK = 0;
    TMOSI = 0;
    TMISO = 1;
    
    _RP21R = 11 ;
    _RP19R = 10 ; 
    _SDI2R = 26;
#if 0// temp commented    
    SPI2CON1 = 0x0122;      
    SPI2CON2 = 0x0000;
    SPI2STAT = 0X8000;
    SPI2STATL = 0x0000;
    CM2CON = 0 ;
#endif
    // AUDEN disabled; FRMEN disabled; AUDMOD I2S; FRMSYPW One clock wide; AUDMONO stereo; FRMCNT 0; MSSEN disabled; FRMPOL disabled; IGNROV disabled; SPISGNEXT not sign-extended; FRMSYNC disabled; URDTEN disabled; IGNTUR disabled; 
    SPI2CON1H = 0x0000;
    // SPIEN enabled; DISSDO disabled; MCLKEN FOSC/2; CKP Idle:High, Active:Low; SSEN enabled; MSTEN Slave; MODE16 disabled; SMP Middle; DISSCK disabled; SPIFE Frame Sync pulse coincides; CKE Idle to Active; MODE32 disabled; SPISIDL disabled; ENHBUF disabled; DISSDI disabled; 
    SPI2CON1L = 0x80C2;
    // WLENGTH 0; 
    SPI2CON2L = 0x0000;
    // SPIROV disabled; FRMERR disabled; 
    SPI2STATL = 0x0000;
    // SPI1BRGL 0; 
    SPI2BRGL = 0x0000;
    // SPITBFEN disabled; SPITUREN disabled; FRMERREN disabled; SRMTEN disabled; SPIRBEN disabled; BUSYEN disabled; SPITBEN disabled; SPIROVEN enabled; SPIRBFEN disabled; 
    SPI2IMSKL = 0x0040;
    // RXMSK 0; TXWIEN disabled; TXMSK 0; RXWIEN disabled; 
    SPI2IMSKH = 0x0000;
    // SPI1URDTL 0; 
    SPI2URDTL = 0x0000;
    // SPI1URDTH 0; 
    SPI2URDTH = 0x0000;
    
    //SPI1IMSKLbits.SPIRBFEN = true; // SPI RX Buffer full generates an interrupt
    SPI2IMSKL = 0xFFFF;
    SPI2IMSKH = 0xFFFF;
    //SPI1IMSKLbits.SPIRBEN = true;
    
    IEC2bits.SPI2IE = true;
    IEC2bits.SPI2TXIE = true;
    IEC3bits.SPI2RXIE = true;
    IFS2bits.SPI2IF = 0;  // clear interrupt flag
    IFS2bits.SPI2TXIF = 0;  // clear interrupt flag
    IFS3bits.SPI2RXIF = 0;  // clear interrupt flag
#if 1// temp commented
    ODCEbits.ODCE7 = 1;
//    AD1PCFGL |= 0x0080;
#endif
    LATE |= 0XFF7F;
    TRISE &= 0XFF7F;
}
void SPI2_Exchange( uint8_t *pTransmitData, uint8_t *pReceiveData )
{
    while( SPI2STATLbits.SPITBF == true );
    SPI2BUFL = *((uint8_t*)pTransmitData);
    while ( SPI2STATLbits.SPIRBE == true);
    *((uint8_t*)pReceiveData) = SPI2BUFL;
}
unsigned char clrc663_SPI_write(unsigned char data)
{
    uint8_t receiveData;
    SPI2_Exchange(&data, &receiveData);
    return (receiveData);
}
uint16_t SPI2_ExchangeBuffer(const uint8_t *pTransmitData, uint16_t byteCount, uint8_t *pReceiveData)
{

    uint16_t dataSentCount = 0;
    uint16_t dataReceivedCount = 0;
    uint16_t dummyDataReceived = 0;
    uint16_t dummyDataTransmit = SPI2_DUMMY_DATA;

    uint8_t  *pSend, *pReceived;
    uint16_t addressIncrement;
    uint16_t receiveAddressIncrement, sendAddressIncrement;

    addressIncrement = 1;

    // set the pointers and increment delta 
    // for transmit and receive operations
    if (pTransmitData == NULL)
    {
        sendAddressIncrement = 0;
        pSend = (uint8_t*)&dummyDataTransmit;
    }
    else
    {
        sendAddressIncrement = addressIncrement;
        pSend = (uint8_t*)pTransmitData;
    }
        
    if (pReceiveData == NULL)
    {
       receiveAddressIncrement = 0;
       pReceived = (uint8_t*)&dummyDataReceived;
    }
    else
    {
       receiveAddressIncrement = addressIncrement;        
       pReceived = (uint8_t*)pReceiveData;
    }
    while( SPI2STATLbits.SPITBF == true );
    while (dataSentCount < byteCount)
    {
        if ( SPI2STATLbits.SPITBF != true )
        {
            SPI2BUFL = *pSend;
            pSend += sendAddressIncrement;
            dataSentCount++;
        }
        if (SPI2STATLbits.SPIRBE == false)
        {
            *pReceived = SPI2BUFL;
            pReceived += receiveAddressIncrement;
            dataReceivedCount++;
        }
    }
    while (dataReceivedCount < byteCount)
    {
        if (SPI2STATLbits.SPIRBE == false)
        {
            *pReceived = SPI2BUFL;
            pReceived += receiveAddressIncrement;
            dataReceivedCount++;
        }
    }
    return dataSentCount;
}
uint16_t clrc663_SPI_transfer(const unsigned char *tx,unsigned char *rx,uint16_t len)
{
    return (SPI2_ExchangeBuffer(tx, len, rx));
}

void clrc663_SPI_select(void)
{
    CS1 = 0;
}

void clrc663_SPI_unselect(void)
{
    CS1 = 1;
}
//******************************************************************************
//* END OF FILE
//******************************************************************************
