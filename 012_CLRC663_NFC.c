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

#include "012_CLRC663_NFC.h"

//      *** *** ***     Print identification numbers     *** *** ***       //

//      *** *** ***     Card Invalidation     *** *** ***       //
// Hex print for blocks without printf.
void print_block(uint8_t * block, uint8_t length){
  int i = 0;
  for (i = 0; i < length; i++){
      if (block[i] < 16){  printf("%02x ",block[i]); } 
      else printf("%02x ",block[i]);
  } 
  printf("\r\n"); 
}

void print_block_01(uint8_t* block, uint8_t lower_lim, uint8_t upper_lim){ 
  int i = 0;
  for(i = lower_lim; i < upper_lim; i++){
    if (block[i] < 16){ printf("%02x ",block[i]); } 
    else printf("%02x ",block[i]);
  } 
  printf(" \r\n"); 
}

void print_card_ID_block(uint8_t * block, uint8_t length){
  printf("CardId: ");
  int i = 0;
  for (i = 3; i < 12; i++){
      if (block[i] < 16){printf("%02x ",block[i]); } 
      else  printf("%02x ",block[i]); }
  printf("%02x ",block[12]>>4);
  printf(" \r\n"); 
}
  //  Card Blacklist and Card Invalidation
void check_valid_card(uint8_t * buf){
  if(buf[40] == 0x62 || buf [41] == 0x83) printf(" ----INVALID CARD: card is locked----");
  else printf("---- VALID CARD ----");
}
  //  Print Pseudo-Unique PICC Identifier, Type B
void print_PUPI(uint8_t* block){
  printf("PUPI: "); 
  print_block_01(block, 1, 5);
}

  //  Print MOBIB Hardcoded Serial Number
void print_serial_nr(uint8_t* block){
  printf("Serial number: "); 
  print_block_01(block, 23, 31);
}
int bitRead(uint8_t value,int pos)
{
    uint8_t temp;
    temp = (value & (0x01 << pos)) >> pos;
    return temp;
}
  //  Shift buffer with two bits (to determine MOBIB Original Card ID)
void shift(uint8_t* buf, uint8_t buf_size){
    int i = 0;
    buf [3] = buf [3] << 2;
    for(i = 4; i < 13; i++){
      uint8_t lastbit = bitRead(buf[i], 7);
      uint8_t secondlastbit = bitRead(buf[i], 6);
      if(lastbit == 1) bitSet(buf[i-1], 1);
      if(secondlastbit == 1) bitSet(buf[i-1], 0);
      buf[i] = buf[i] << 2;
    }
}
  //  Print MOBIB Original Card ID
void print_card_ID(uint8_t* buf, uint8_t bufsize){
    shift(buf, bufsize);
    print_card_ID_block(buf, bufsize);
}

void read_iso14443B_nfc_card(){

    //  Configure CLRC663
  CLRC663_configure_communication_protocol(CLRC630_PROTO_ISO14443B_106_NRZ_BPSK);
  
    //  WUPB
  uint8_t wupb_buffer [] = {CLRC663_ISO14443B_CMD_APF, CLRC663_ISO14443B_CMD_AFI, CLRC663_ISO14443B_CMD_PARAM};
  uint8_t atqb_buffer [12] = {0};
  uint8_t atqb_length = clrc663_communicate(wupb_buffer, sizeof(wupb_buffer), atqb_buffer);
  
  if(atqb_length != 0) { 

      //  ATTRIB
    uint8_t transmit_buffer [] = {0x1D, atqb_buffer[1], atqb_buffer[2], atqb_buffer[3], atqb_buffer[4], 0x00, 0x08, 0x01, 0x00};
    uint8_t receive_buffer [1] = {0};
    clrc663_communicate(transmit_buffer, sizeof(transmit_buffer), receive_buffer);
          
      //  CALYPSO --- Select Global Data Application 
    uint8_t apdu_transmit_buffer [] = APDU_SELECT_GLOBAL_DATA_APP_MOBIB_CARD;
    uint8_t apdu_receive_buffer [42] = {0};
    clrc663_communicate(apdu_transmit_buffer, sizeof(apdu_transmit_buffer), apdu_receive_buffer);
    
      //  CALYPSO --- Read record 1
    uint8_t apdu_transmit_buffer_1 [] = CARDISSUING_FILE_READ_RECORD_1;
    uint8_t apdu_receive_buffer_1 [32] = {0};
    clrc663_communicate(apdu_transmit_buffer_1, sizeof(apdu_transmit_buffer_1), apdu_receive_buffer_1);


    #ifdef DEBUG_ISO14443B
        //  Print sended en received bytes
      printf("  ---   WUPB   --- \n");
      printf("Send: "); print_block(wupb_buffer, sizeof(wupb_buffer));
      printf("Receive: "); print_block(atqb_buffer, sizeof(atqb_buffer));
      printf("  ---   ATTRIB   --- \n");
      printf("Send: "); print_block(transmit_buffer, sizeof(transmit_buffer));
      printf("Receive: "); print_block(receive_buffer, sizeof(receive_buffer));
      printf("  ---   CALYPSO --- APDU select global data application   --- \n");
      printf("Send: "); print_block(apdu_transmit_buffer, sizeof(apdu_transmit_buffer));
      printf("Receive: "); print_block(apdu_receive_buffer, sizeof(apdu_receive_buffer));
      printf("  ---   CALYPSO --- APDU read record 1  --- \n");
      printf("Send: "); print_block(apdu_transmit_buffer_1, sizeof(apdu_transmit_buffer_1));
      printf("Receive: "); print_block(apdu_receive_buffer_1, sizeof(apdu_receive_buffer_1));
    #endif

    #ifdef PRINT_IDENTIFICATION_NUMBERS
      printf(" \r\n");
      check_valid_card(apdu_receive_buffer);
      print_PUPI(atqb_buffer);
      print_serial_nr(apdu_receive_buffer);
      print_card_ID(apdu_receive_buffer_1, sizeof(apdu_receive_buffer_1));
    #endif
  }
}
