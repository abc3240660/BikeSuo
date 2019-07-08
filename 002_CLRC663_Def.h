//       10        20        30        40        50        60        70
//--*----*----*----*----*----*----*----*----*----*----*----*----*----*----*----*

/******************************************************************************
 * A library for CLRC663 Module
 * This file is about the CLRC663 API
 *
 * Copyright (c) 2019 Mobit technology inc.
 * @Author       : Damon
 * @Create time  : 04/14/2019
******************************************************************************/

#ifndef CLRC663_DEF_H_
#define CLRC663_DEF_H_


/*! \addtogroup register
    
  @{
*/
// Define register name                 Addr    //  comment
#define CLRC630_REG_COMMAND             0x00    //!< Starts and stops command execution
#define CLRC630_REG_HOSTCTRL            0x01    //!< Host control register
#define CLRC630_REG_FIFOCONTROL         0x02    //!< Control register of the FIFO
#define CLRC630_REG_WATERLEVEL          0x03    //!< Level of the FIFO underflow and overflow warning
#define CLRC630_REG_FIFOLENGTH          0x04    //!< Length of the FIFO
#define CLRC630_REG_FIFODATA            0x05    //!< Data In/Out exchange register of FIFO buffer
#define CLRC630_REG_IRQ0                0x06    //!< Interrupt register 0
#define CLRC630_REG_IRQ1                0x07    //!< Interrupt register 1
#define CLRC630_REG_IRQ0EN              0x08    //!< Interrupt enable register 0
#define CLRC630_REG_IRQ1EN              0x09    //!< Interrupt enable register 1
#define CLRC630_REG_ERROR               0x0A    //!< Error bits showing the error status of the last command execution
#define CLRC630_REG_STATUS              0x0B    //!< Contains status of the communication
#define CLRC630_REG_RXBITCTRL           0x0C    //!< Control for anticoll. adjustments for bit oriented protocols
#define CLRC630_REG_RXCOLL              0x0D    //!< Collision position register
#define CLRC630_REG_TCONTROL            0x0E    //!< Control of Timer 0..3
#define CLRC630_REG_T0CONTROL           0x0F    //!< Control of Timer0
#define CLRC630_REG_T0RELOADHI          0x10    //!< High register of the reload value of Timer0
#define CLRC630_REG_T0RELOADLO          0x11    //!< Low register of the reload value of Timer0
#define CLRC630_REG_T0COUNTERVALHI      0x12    //!< Counter value high register of Timer0
#define CLRC630_REG_T0COUNTERVALLO      0x13    //!< Counter value low register of Timer0
#define CLRC630_REG_T1CONTROL           0x14    //!< Control of Timer1
#define CLRC630_REG_T1RELOADHI          0x15    //!< High register of the reload value of Timer1
#define CLRC630_REG_T1RELOADLO          0x16    //!< Low register of the reload value of Timer1
#define CLRC630_REG_T1COUNTERVALHI      0x17    //!< Counter value high register of Timer1
#define CLRC630_REG_T1COUNTERVALLO      0x18    //!< Counter value low register of Timer1
#define CLRC630_REG_T2CONTROL           0x19    //!< Control of Timer2
#define CLRC630_REG_T2RELOADHI          0x1A    //!< High byte of the reload value of Timer2
#define CLRC630_REG_T2RELOADLO          0x1B    //!< Low byte of the reload value of Timer2
#define CLRC630_REG_T2COUNTERVALHI      0x1C    //!< Counter value high byte of Timer2
#define CLRC630_REG_T2COUNTERVALLO      0x1D    //!< Counter value low byte of Timer2
#define CLRC630_REG_T3CONTROL           0x1E    //!< Control of Timer3
#define CLRC630_REG_T3RELOADHI          0x1F    //!< High byte of the reload value of Timer3
#define CLRC630_REG_T3RELOADLO          0x20    //!< Low byte of the reload value of Timer3
#define CLRC630_REG_T3COUNTERVALHI      0x21    //!< Counter value high byte of Timer3
#define CLRC630_REG_T3COUNTERVALLO      0x22    //!< Counter value low byte of Timer3
#define CLRC630_REG_T4CONTROL           0x23    //!< Control of Timer4
#define CLRC630_REG_T4RELOADHI          0x24    //!< High byte of the reload value of Timer4
#define CLRC630_REG_T4RELOADLO          0x25    //!< Low byte of the reload value of Timer4
#define CLRC630_REG_T4COUNTERVALHI      0x26    //!< Counter value high byte of Timer4
#define CLRC630_REG_T4COUNTERVALLO      0x27    //!< Counter value low byte of Timer4
#define CLRC630_REG_DRVMOD              0x28    //!< Driver mode register
#define CLRC630_REG_TXAMP               0x29    //!< Transmitter amplifier register
#define CLRC630_REG_DRVCON              0x2A    //!< Driver configuration register
#define CLRC630_REG_TXL                 0x2B    //!< Transmitter register
#define CLRC630_REG_TXCRCPRESET         0x2C    //!< Transmitter CRC control register, preset value
#define CLRC630_REG_RXCRCCON            0x2D    //!< Receiver CRC control register, preset value
#define CLRC630_REG_TXDATANUM           0x2E    //!< Transmitter data number register
#define CLRC630_REG_TXMODWIDTH          0x2F    //!< Transmitter modulation width register
#define CLRC630_REG_TXSYM10BURSTLEN     0x30    //!< Transmitter symbol 1 + symbol 0 burst length register
#define CLRC630_REG_TXWAITCTRL          0x31    //!< Transmitter wait control
#define CLRC630_REG_TXWAITLO            0x32    //!< Transmitter wait low
#define CLRC630_REG_FRAMECON            0x33    //!< Transmitter frame control
#define CLRC630_REG_RXSOFD              0x34    //!< Receiver start of frame detection
#define CLRC630_REG_RXCTRL              0x35    //!< Receiver control register
#define CLRC630_REG_RXWAIT              0x36    //!< Receiver wait register
#define CLRC630_REG_RXTHRESHOLD         0x37    //!< Receiver threshold register
#define CLRC630_REG_RCV                 0x38    //!< Receiver register
#define CLRC630_REG_RXANA               0x39    //!< Receiver analog register
#define CLRC630_REG_LPCD_OPTIONS        0x3A    //!< No function implemented for CLRC66301 and CLRC66302 (For CLRC66303: Options for LPCD configuration)
#define CLRC630_REG_SERIALSPEED         0x3B    //!< Serial speed register
#define CLRC630_REG_LFO_TRIMM           0x3C    //!< Low-power oscillator trimming register
#define CLRC630_REG_PLL_CTRL            0x3D    //!< IntegerN PLL control register, for mcu clock output adjustment
#define CLRC630_REG_PLL_DIVOUT          0x3E    //!< IntegerN PLL control register, for mcu clock output adjustment
#define CLRC630_REG_LPCD_QMIN           0x3F    //!< Low-power card detection Q channel minimum threshold
#define CLRC630_REG_LPCD_QMAX           0x40    //!< Low-power card detection Q channel maximum threshold
#define CLRC630_REG_LPCD_IMIN           0x41    //!< Low-power card detection I channel minimum threshold
#define CLRC630_REG_LPCD_I_RESULT       0x42    //!< Low-power card detection I channel result register
#define CLRC630_REG_LPCD_Q_RESULT       0x43    //!< Low-power card detection Q channel result register
#define CLRC630_REG_PADEN               0x44    //!< PIN enable register
#define CLRC630_REG_PADOUT              0x45    //!< PIN out register
#define CLRC630_REG_PADIN               0x46    //!< PIN in register
#define CLRC630_REG_SIGOUT              0x47    //!< Enables and controls the SIGOUT Pin
#define CLRC663_REG_TXBITMOD            0x48    //!< Transmitter bit mode register
#define CLRC663_REG_TXDATACON           0x4A    //!< Transmitter data configuration register
#define CLRC663_REG_TXDATAMOD           0x4B    //!< Transmitter data modulation register
#define CLRC663_REG_TXSYMFREQ           0x4C    //!< Transmitter symbol frequency
#define CLRC663_REG_TXSYM0H             0x4D    //!< Transmitter symbol 0 high register
#define CLRC663_REG_TXSYM0L             0x4E    //!< Transmitter symbol 0 low register
#define CLRC663_REG_TXSYM1H             0x4F    //!< Transmitter symbol 1 high register
#define CLRC663_REG_TXSYM1L             0x50    //!< Transmitter symbol 1 low register
#define CLRC663_REG_TXSYM2              0x51    //!< Transmitter symbol 2 register
#define CLRC663_REG_TXSYM3              0x52    //!< Transmitter symbol 3 register
#define CLRC663_REG_TXSYM10LEN          0x53    //!< Transmitter symbol 1 + symbol 0 length register
#define CLRC663_REG_TXSYM32LEN          0x54    //!< Transmitter symbol 3 + symbol 2 length register
#define CLRC663_REG_TXSYM10BURSTCTRL    0x55    //!< Transmitter symbol 1 + symbol 0 burst control register
#define CLRC663_REG_TXSYM10MOD          0x56    //!< Transmitter symbol 1 + symbol 0 modulation register
#define CLRC663_REG_TXSYM32MOD          0x57    //!< Transmitter symbol 3 + symbol 2 modulation register
#define CLRC663_REG_RXBITMOD            0x58    //!< Receiver bit modulation register
#define CLRC663_REG_RXEOFSYM            0x95    //!< Receiver end of frame symbol register
#define CLRC663_REG_RXSYNCVALH          0x5A    //!< Receiver synchronisation value high register
#define CLRC663_REG_RXSYNCVALL          0x5B    //!< Receiver synchronisation value low register
#define CLRC663_REG_RXSYNCMOD           0x5C    //!< Receiver synchronisation mode register
#define CLRC663_REG_RXMOD               0x5D    //!< Receiver modulation register
#define CLRC663_REG_RXCORR              0x5E    //!< Receiver correlation register
#define CLRC663_REG_FABCAL              0x5F    //!< Calibration register of the receiver, calibration performed at production
#define CLRC630_REG_VERSION             0x7F    //!< Version and subversion register

//! @}

/*! \addtogroup commands
    
  @{
*/
// Define  command name                 hex     //  argument ; comment
#define CLRC630_CMD_IDLE                0x00    /*!< (no arguments) ; no action, cancels current command execution. */

#define CLRC630_CMD_LPCD                0x01    /*!< (no arguments) ; low-power card detection. */

#define CLRC630_CMD_LOADKEY             0x02    /*!< (keybyte1), (keybyte2), (keybyte3), (keybyte4), (keybyte5),
                                                     (keybyte6); reads a MIFARE key (size of 6 bytes) from FIFO buffer
                                                     and puts it into Key buffer. */

#define CLRC630_CMD_MFAUTHENT           0x03    /*!< 60h or 61h, (block address), (card serial number byte0), (card
                                                     serial number byte1), (card serial number byte2), (card serial
                                                     number byte3); performs the MIFARE standard authentication. */

#define CLRC630_CMD_RECEIVE             0x05    /*!< (no arguments) ; activates the receive circuit. */

#define CLRC630_CMD_TRANSMIT            0x06    /*!< bytes to send: byte1, byte2, ...;  transmits data from the FIFO
                                                     buffer. */

#define CLRC630_CMD_TRANSCEIVE          0x07    /*!< bytes to send: byte1, byte2, ....;  transmits data from the FIFO
                                                     buffer and automatically activates the receiver after transmission
                                                     finished. */

#define CLRC630_CMD_WRITEE2             0x08    /*!< addressH, addressL, data; gets one byte from FIFO buffer and
                                                     writes it to the internal EEPROM.*/

#define CLRC630_CMD_WRITEE2PAGE         0x09    /*!< (page Address), data0, [data1..data63]; gets up to 64 bytes (one
                                                     EEPROM page) from the FIFO buffer and writes it to the EEPROM. */

#define CLRC630_CMD_READE2              0x0A    /*!< addressH, address L, length; reads data from the EEPROM and copies
                                                     it into the FIFO buffer. */

#define CLRC630_CMD_LOADREG             0x0C    /*!< (EEPROM addressH), (EEPROM addressL), RegAdr, (number of Register
                                                     to be copied); reads data from the internal EEPROM and initializes
                                                     the CLRC630 registers. EEPROM address needs to be within EEPROM
                                                     sector 2. */

#define CLRC630_CMD_LOADPROTOCOL        0x0D    /*!< (Protocol number RX), (Protocol number TX); reads data from the
                                                     internal EEPROM and initializes the CLRC630 registers needed for a
                                                     Protocol change.*/

#define CLRC630_CMD_LOADKEYE2           0x0E    /*!< KeyNr; copies a key from the EEPROM into the key buffer. */

#define CLRC630_CMD_STOREKEYE2          0x0F    /*!< KeyNr, byte1, byte2, byte3, byte4, byte5, byte6; stores a MIFARE
                                                     key (size of 6 bytes) into the EEPROM.*/

#define CLRC630_CMD_READRNR             0x1C    /*!< (no arguments) ; Copies bytes from the Random Number generator
                                                    into the FIFO until the FiFo is full. */

#define CLRC630_CMD_SOFTRESET           0x1F    /*!< (no arguments) ; resets the CLRC630. */

//! @}


/*! \addtogroup register
    
  @{

    \defgroup status_reg Status
      \brief  Defines for `#CLRC630_REG_STATUS`.

      For interpreting the `#CLRC630_REG_STATUS` register.
      @{
*/
#define CLRC630_STATUS_STATE_IDLE           0b000       //!< Status register; Idle
#define CLRC630_STATUS_STATE_TXWAIT         0b001       //!< Status register; Tx wait
#define CLRC630_STATUS_STATE_TRANSMITTING   0b011       //!< Status register; Transmitting.
#define CLRC630_STATUS_STATE_RXWAIT         0b101       //!< Status register; Rx wait.
#define CLRC630_STATUS_STATE_WAIT_FOR_DATA  0b110       //!< Status register; Waiting for data.
#define CLRC630_STATUS_STATE_RECEIVING      0b111       //!< Status register; Receiving data.
#define CLRC630_STATUS_STATE_NOT_USED       0b100       //!< Status register; Not used.
#define CLRC630_STATUS_CRYPTO1_ON           (1<<5)      //!< Status register; Crypto1 (MIFARE authentication) is on.

    //! @}
//! @}

/*! \addtogroup timer
  @{

    \defgroup timer_control Timer Control
      \brief Timer Control register defines.

      For use with `CLRC630_timer_set_control()`, this can be used to modify the parameters of a specific timer. This
      allows configuration of the timer source, start and stop criteria.
      @{
*/
//! If set, the timer stops after receiving the first 4 bits. If cleared, the timer is not stopped automatically.
#define CLRC630_TCONTROL_STOPRX           (1<<7)
//! Do not start automatically.
#define CLRC630_TCONTROL_START_NOT        (0b00<<4)
//! Start automatically at the end of transmission.
#define CLRC630_TCONTROL_START_TX_END     (0b01<<4)
//! Timer is used for LFO trimming without underflow.
#define CLRC630_TCONTROL_START_LFO_WO     (0b10<<4)
//! Timer is used for LFO trimming with underflow.
#define CLRC630_TCONTROL_START_LFO_WITH   (0b11<<4)
//! Automatically restart from the reload value when an underflow is reached.
#define CLRC630_TCONTROL_AUTO_RESTART     (0b1<<3)
//! results in 7.69e-08 ~ 76 nSec ticks.
#define CLRC630_TCONTROL_CLK_13MHZ        (0b00)
//! results in 4.52e-06 ~ 5 uSec ticks.
#define CLRC630_TCONTROL_CLK_211KHZ       (0b01)
//! The timer ticks based on alternate source 1, check datasheet.
#define CLRC630_TCONTROL_CLK_UF_TA1       (0b10)
//! The timer ticks based on alternate source 2, check datasheet.
#define CLRC630_TCONTROL_CLK_UF_TA2       (0b11)

  //! @}
//! @}


/*! \addtogroup register
    
  @{

  \defgroup irq0_reg Interrupt 0
        \brief Defines for `#CLRC630_REG_IRQ0`.

        For interpreting the `#CLRC630_REG_IRQ0` register, this register contains various interrupt flags.
        @{
*/
// IRQ0 register fields
//! If this is set, set the other fields to the value of those bits.
#define CLRC630_IRQ0_SET                (1<<7)
//! Indicates high FIFO level.
#define CLRC630_IRQ0_HIALERT_IRQ        (1<<6)
//! Indicates low FIFO level.
#define CLRC630_IRQ0_LOALERT_IRQ        (1<<5)
//! Indicates that the chip is idle, command terminated by itself.
#define CLRC630_IRQ0_IDLE_IRQ           (1<<4)
//! Indicates that the transmission is completed, set after last bit is sent.
#define CLRC630_IRQ0_TX_IRQ             (1<<3)
//! Set when the receiver detects end of data stream.
#define CLRC630_IRQ0_RX_IRQ             (1<<2)
//! Set when a transmission error occurs, \see error_reg
#define CLRC630_IRQ0_ERR_IRQ            (1<<1)
//! Set when Start Of Frame or subcarrier is detected.
#define CLRC630_IRQ0_RXSOF_IRQ          (1<<0)

//! @}

/*!
  \defgroup irq1_reg Interrupt 1
        \brief Defines for `#CLRC630_REG_IRQ1`.

        For interpreting the `#CLRC630_REG_IRQ1` register, this register contains various interrupt flags.
        @{
*/
// IRQ1 register fields
//! If this is set, set the other fields to the value of those bits.
#define CLRC630_IRQ1_SET                (1<<7)
//! Indicates a global interrupt occured.
#define CLRC630_IRQ1_GLOBAL_IRQ         (1<<6)
//! Indicated an LPCD interrupt occured.
#define CLRC630_IRQ1_LPCD_IRQ           (1<<5)
//! Set to 1 if Timer4 has an underflow.
#define CLRC630_IRQ1_TIMER4_IRQ         (1<<4)
//! Set to 1 if Timer3 has an underflow.
#define CLRC630_IRQ1_TIMER3_IRQ         (1<<3)
//! Set to 1 if Timer2 has an underflow.
#define CLRC630_IRQ1_TIMER2_IRQ         (1<<2)
//! Set to 1 if Timer1 has an underflow.
#define CLRC630_IRQ1_TIMER1_IRQ         (1<<1)
//! Set to 1 if Timer0 has an underflow.
#define CLRC630_IRQ1_TIMER0_IRQ         (1<<0)

    //! @}

/*!
  \defgroup irq0en_reg Interrupt 0 Enable
        \brief Defines for `#CLRC630_REG_IRQ0EN`.

        For manipulating the `#CLRC630_REG_IRQ0EN` register, this register controls which interrupts from IRQ0 trigger
        a global interrupt (`#CLRC630_IRQ1_GLOBAL_IRQ`).
        @{
*/

// IRQ0EN register fields
//! If set, the signal on the IRQ pin is inverted.
#define CLRC630_IRQ0EN_IRQ_INV          (1<<7)
//! If set allow High Alert to propagate to the global IRQ.
#define CLRC630_IRQ0EN_HIALERT_IRQEN    (1<<6)
//! If set allow Low Alert to propagate to the global IRQ.
#define CLRC630_IRQ0EN_LOALERT_IRQEN    (1<<5)
//! If set allow idle irq to propagate to the global IRQ.
#define CLRC630_IRQ0EN_IDLE_IRQEN       (1<<4)
//! If set allow tx irq to propagate to the global IRQ.
#define CLRC630_IRQ0EN_TX_IRQEN         (1<<3)
//! If set allow rx irq to propagate to the global IRQ.
#define CLRC630_IRQ0EN_RX_IRQEN         (1<<2)
//! If set allow error irq to propagate to the global IRQ.
#define CLRC630_IRQ0EN_ERR_IRQEN        (1<<1)
//! If set allow rx SOF irq to propagate to the global IRQ.
#define CLRC630_IRQ0EN_RXSOF_IRQEN      (1<<0)

    //! @}

/*!
  \defgroup irq1en_reg Interrupt 1 Enable
        \brief Defines for `#CLRC630_REG_IRQ1EN`.

        For manipulating the `#CLRC630_REG_IRQ1EN` register, this register controls which interrupts from IRQ1 trigger
        a global interrupt (`#CLRC630_IRQ1_GLOBAL_IRQ`).

        \note The timer IRQ's are conveniently correct when bitshifting the id: `1 << timer_id.`
        @{
*/

// IRQ1EN register fields.
//! Set to 1: IRQ pin acts as PushPull, otherwise open drain.
#define CLRC630_IRQ1EN_IRQ_PUSHPULL        (1<<7)
//! Set to 1: allows the global IRQ to propagate to the IRQ pin.
#define CLRC630_IRQ1EN_IRQ_PINEN           (1<<6)
//! If set allow LPCD irq to propagate to the global IRQ.
#define CLRC630_IRQ1EN_LPCD_IRQEN          (1<<5)
//! If set allow Timer 4 irq to propagate to the global IRQ.
#define CLRC630_IRQ1EN_TIMER4_IRQEN        (1<<4)
//! If set allow Timer 3 irq to propagate to the global IRQ.
#define CLRC630_IRQ1EN_TIMER3_IRQEN        (1<<3)
//! If set allow Timer 2 irq to propagate to the global IRQ.
#define CLRC630_IRQ1EN_TIMER2_IRQEN        (1<<2)
//! If set allow Timer 1 irq to propagate to the global IRQ.
#define CLRC630_IRQ1EN_TIMER1_IRQEN        (1<<1)
//! If set allow Timer 0 irq to propagate to the global IRQ.
#define CLRC630_IRQ1EN_TIMER0_IRQEN        (1<<0)

    //! @}

/*!
  \defgroup error_reg Error
        \brief Defines for `#CLRC630_REG_ERROR`.

        For interpreting the `#CLRC630_REG_ERROR` register, this register holds information about errors that have
        occured.
        @{
*/

// Error register fields
//! An error appeared during the last EEPROM command.
#define CLRC630_ERROR_EE_ERR            (1<<7)
//! Data was written to FIFO while this shouldn't be done.
#define CLRC630_ERROR_FIFOWRERR         (1<<6)
//! Data was written to the FIFO while it was already full.
#define CLRC630_ERROR_FIFOOVL           (1<<5)
//! A valid SOF was received, but less then 4 bits of data were received.
#define CLRC630_ERROR_MINFRAMEERR       (1<<4)
//! No data available to be sent.
#define CLRC630_ERROR_NODATAERR         (1<<3)
//! A collision occured.
#define CLRC630_ERROR_COLLDET           (1<<2)
//! A protocol error occured.
#define CLRC630_ERROR_PROTERR           (1<<1)
//! A data integrity error occured.
#define CLRC630_ERROR_INTEGERR          (1<<0)

    //! @}

/*!
  \defgroup crc_reg CRC
        \brief Defines to manipulate `#CLRC630_REG_TXCRCPRESET` and `#CLRC630_REG_RXCRCCON`.

        For the `#CLRC630_REG_TXCRCPRESET` and `#CLRC630_REG_RXCRCCON` registers. Mainly used ORed with
        `#CLRC630_RECOM_14443A_CRC` as that allows enabling or disabling the CRC checksum calculation for ISO14443
        interaction.

        \see `#CLRC630_RECOM_14443A_CRC`.

        @{
*/

//! Enable CRC, should be ORed with `#CLRC630_RECOM_14443A_CRC`.
#define CLRC630_CRC_ON            1
//! Disable CRC, should be ORed with `#CLRC630_RECOM_14443A_CRC`.
#define CLRC630_CRC_OFF           0

    //! @}

/*!
  \defgroup txdatanum_reg Tx Datanum
        \brief Define to manipulate `#CLRC630_REG_TXDATANUM`.

        
        For the `#CLRC630_REG_TXDATANUM` register, the last 3 bits of this register determine how many bits of the last
        byte in the FIFO are actually transmitted. For transmission of 7 bit or 5 bit symbols this needs to be modified.

        \note Without `#CLRC630_TXDATANUM_DATAEN` you are probably going to get unexpected results.
        @{
*/

//! If set, data is sent, if cleared it is possible to send a single symbol pattern.
#define CLRC630_TXDATANUM_DATAEN        (1<<3)

    //! @}

// close the registers group
//! @}


/*! \addtogroup documentation
    
    The defines in @ref protocol_index are the protocol numbers and can be used as such. The
    `#CLRC630_PROTO_ISO14443A_106_MILLER_MANCHESTER` is the default one for the ISO14443A select procedure.
  @{

  \defgroup protocol_index Protocol numbers
        \brief Defines for the various protocol numbers.

        For use with the `CLRC630_cmd_load_protocol()` function, but also used for
        `CLRC630_AN1102_recommended_registers()`.
        @{
*/

//! This is the default protocol during the SELECT procedure, it is the most likely to work.
//! Transmitter at 106 kbit/s using Miller modulation, Receive at 106 kbit/s using Manchester SubC modulation.
#define CLRC630_PROTO_ISO14443A_106_MILLER_MANCHESTER 0
//! Transmitter at 212 kbit/s using Miller modulation, Receive at 212 kbit/s using BPSK modulation.
#define CLRC630_PROTO_ISO14443A_212_MILLER_BPSK 1
//! Transmitter at 424 kbit/s using Miller modulation, Receive at 424 kbit/s using BPSK modulation.
#define CLRC630_PROTO_ISO14443A_424_MILLER_BPSK 2
//! Transmitter at 848 kbit/s using Miller modulation, Receive at 848 kbit/s using BPSK modulation.
#define CLRC630_PROTO_ISO14443A_848_MILLER_BPSK 3
//! Transmitter at 106 kbit/s using NRZ modulation, Receive at 848 kbit/s using BPSK modulation.
#define CLRC630_PROTO_ISO14443B_106_NRZ_BPSK 4
//! Transmitter at 212 kbit/s using NRZ modulation, Receive at 848 kbit/s using BPSK modulation.
#define CLRC630_PROTO_ISO14443B_212_NRZ_BPSK 5
//! Transmitter at 424 kbit/s using NRZ modulation, Receive at 848 kbit/s using BPSK modulation.
#define CLRC630_PROTO_ISO14443B_424_NRZ_BPSK 6
//! Transmitter at 848 kbit/s using NRZ modulation, Receive at 848 kbit/s using BPSK modulation.
#define CLRC630_PROTO_ISO14443B_848_NRZ_BPSK 7
//! Transmitter at 212 kbit/s using Manchester modulation, Receive at 212 kbit/s using Manchester modulation.
#define CLRC630_PROTO_FELICA_212_MANCHESTER_MANCHESTER 8
//! Transmitter at 424 kbit/s using Manchester modulation, Receive at 424 kbit/s using Manchester modulation.
#define CLRC630_PROTO_FELICA_424_MANCHESTER_MANCHESTER 9
//! ISO15693 1/4 SSC
#define CLRC630_PROTO_ISO15693_1_OF_4_SSC 10
//! ISO15693 1/4 DSC
#define CLRC630_PROTO_ISO15693_1_OF_4_DSC 11
//! ISO15693 1/256 SSC
#define CLRC630_PROTO_ISO15693_1_OF_256_SSC 12
//! EPC/UID Unitray SSC
#define CLRC630_PROTO_EPC_UID_UNITRAY_SSC 13
//! ISO18000-3 Mode 3, Tari, ASK, PIE, 2/424
#define CLRC630_PROTO_ISO18000_MODE_3 14

    //! @}

// recommended register values from register 0x28 down.
// From AN11022: CLRC663 Quickstart Guide
// All the other protocols are also in there....
//! Correct settings for the CRC registers for ISO14443A data frames.
#define CLRC630_RECOM_14443A_CRC 0x18
//! Recommended register values for ISO1443A at 106 kbit/s with Miller / Manchester modulation.
#define CLRC630_RECOM_14443A_ID1_106 {0x8A, 0x08, 0x21, 0x1A, 0x18, 0x18, 0x0F, 0x27, 0x00, 0xC0, 0x12, 0xCF, 0x00, \
                                      0x04, 0x90, 0x32, 0x12, 0x0A}
//! Recommended register values for ISO1443A at 212 kbit/s with Miller / BPSK modulation.
#define CLRC630_RECOM_14443A_ID1_212 {0x8E, 0x12, 0x11, 0x06, 0x18, 0x18, 0x0F, 0x10, 0x00, 0xC0, 0x12, 0xCF, 0x00, \
                                      0x05, 0x90, 0x3F, 0x12, 0x02}
//! Recommended register values for ISO1443A at 424 kbit/s with Miller / BPSK modulation.
#define CLRC630_RECOM_14443A_ID1_424 {0x8E, 0x12, 0x11, 0x06, 0x18, 0x18, 0x0F, 0x08, 0x00, 0xC0, 0x12, 0xCF, 0x00, \
                                      0x06, 0x90, 0x3F, 0x12, 0x0A}
//! Recommended register values for ISO1443A at 848  kbit/s with Miller / BPSK modulation.
#define CLRC630_RECOM_14443A_ID1_848 {0x8F, 0xDB, 0x11, 0x06, 0x18, 0x18, 0x0F, 0x02, 0x00, 0xC0, 0x12, 0xCF, 0x00, \
                                      0x07, 0x90, 0x3F, 0x12, 0x02}
//! Recommended register values for ISO1443B at 106  kbit/s with NRZ / BPSK modulation.
#define CLRC633_RECOM_14443B_ID1_106 {0x8F, 0x0E, 0x09, 0x0A, 0x7B, 0x7B, 0x08, 0x00, 0x00, 0x01, 0x00, 0x05, 0x00, \
                                      0x34, 0x90, 0x6F, 0x12, 0x03}
//! Recommended register values for ISO1443B at 212  kbit/s with NRZ / BPSK modulation.
#define CLRC633_RECOM_14443B_ID1_212 {0x8F, 0x0E, 0x09, 0x0A, 0x7B, 0x7B, 0x08, 0x00, 0x00, 0x01, 0x00, 0x05, 0x00, \
                                      0x35, 0x90, 0x3F, 0x12, 0x03}
//! Recommended register values for ISO1443B at 424  kbit/s with NRZ / BPSK modulation.
#define CLRC633_RECOM_14443B_ID1_424 {0x8F, 0x0F, 0x09, 0x0A, 0x7B, 0x7B, 0x08, 0x00, 0x00, 0x01, 0x00, 0x05, 0x00, \
                                      0x36, 0x90, 0x3F, 0x12, 0x03}
//! Recommended register values for ISO1443B at 848  kbit/s with NRZ / BPSK modulation.
#define CLRC633_RECOM_14443B_ID1_848 {0x8F, 0x10, 0x09, 0x0A, 0x7B, 0x7B, 0x08, 0x00, 0x00, 0x01, 0x00, 0x05, 0x00, \
                                      0x37, 0x90, 0x3F, 0x12, 0x03}
//! @}

/*! \addtogroup iso14443a
  @{
*/
// Defines from ISO14443A
#define CLRC630_ISO14443_CMD_REQA               0x26  //!< request (idle -> ready)
#define CLRC630_ISO14443_CMD_WUPA               0x52  //!< wake up type a (idle / halt -> ready)
#define CLRC630_ISO14443_CAS_LEVEL_1            0x93  //!< Cascade level 1 for select.
#define CLRC630_ISO14443_CAS_LEVEL_2            0x95  //!< Cascade level 2 for select.
#define CLRC630_ISO14443_CAS_LEVEL_3            0x97  //!< Cascade level 3 for select.

//! @}

/*! \addtogroup mifare
  @{
*/
// Defines for MIFARE
#define CLRC630_MF_AUTH_KEY_A                   0x60  //!< A key_type for mifare auth.
#define CLRC630_MF_AUTH_KEY_B                   0x61  //!< A key_type for mifare auth.
#define CLRC630_MF_CMD_READ                     0x30  //!< To read a block from mifare card.
#define CLRC630_MF_CMD_WRITE                    0xA0  //!< To write a block to a mifare card.
#define CLRC630_MF_ACK                          0x0A  //!< Sent by cards to acknowledge an operation.

//! @}

/*! \addtogroup iso14443b
  @{
*/
// Defines from ISO14443B
// WUPB and REQB commands
#define CLRC663_ISO14443B_CMD_APF               0x05  //!< First byte of a REQB/WUPB request (always 0x05)
#define CLRC663_ISO14443B_CMD_AFI               0x00  //!< Application Family Identifier
#define CLRC663_ISO14443B_CMD_PARAM             0x08  //!< Indicates WUPB or REQB commands

//! @}


/*! \Select the Global Data Application on the MoBIB card.
  @{
*/
// Sending following APDU
#define APDU_SELECT_GLOBAL_DATA_APP_MOBIB_CARD  {0x02, 0x00, 0xA4, 0x04, 0x00, 0x0B, 0xA0, 0x00, 0x00, 0x02, 0x91, 0xD0, 0x56, 0x00, 0x01, 0x90, 0x01}

//  Read record 1 in the CardIssuing file with APDU command
#define CARDISSUING_FILE_READ_RECORD_1          {0x03, 0x00, 0xB2, 0x01, 0xE4, 0x1D}

#endif  // CLRC663_DEF_H_
