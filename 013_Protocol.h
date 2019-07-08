#ifndef __MOBIT_PROTOCOL_H
#define __MOBIT_PROTOCOL_H

#include "003_BG96.h"

#define PROTOCOL_HEAD	"#MOBIT"
#define DEV_TAG			"ECAR"
#define SW_VERSION		"V201903182110"
#define HW_VERSION		"V1.0"

#define CMD_DEV_ACK		"Re"// DEV ACK

// F407 Send to Server automatically
#define CMD_DEV_REGISTER	"REG"// DEV Host
#define CMD_HEART_BEAT		"HB"// DEV Host
    #define CMD_DOOR_LOCKED		"C1"// DEV Host
#define CMD_DOOR_UNLOCKED	"OL"// DEV Host
#define CMD_CALYPSO_UPLOAD	"RC"// DEV Host
#define CMD_INVALID_MOVE	"AL"// DEV Host
#define CMD_REPORT_GPS		"GEO"// DEV Host
#define CMD_IAP_SUCCESS		"UP"// DEV Host
    #define CMD_CHARGE_STARTED	"B1"// DEV Host
    #define CMD_CHARGE_STOPED	"B3"// DEV Host
    #define CMD_DOOR_OPENED 	"C7"// DEV Host
#define CMD_FINISH_ADDNFC 	"ADDC"// DEV Host
#define CMD_FINISH_RST      "RSOK"// DEV Host
#define CMD_RISK_REPORT     "FA"// DEV Host

// F407 Recv from Server and Action / ACK
#define CMD_QUERY_PARAMS	"QG"// DEV ACK
    #define CMD_RING_ALARM		"R2"// DEV ACK
#define CMD_UNLOCK_DOOR		"OL"// DEV ACK
    #define CMD_JUMP_LAMP		"S2"// DEV ACK
#define CMD_FACTORY_RST     "RS"// DEV ACK
#define CMD_ENTER_SLEEP     "SLEEP"// DEV ACK
#define CMD_QUERY_GPS   	"GEO"// DEV ACK
#define CMD_IAP_UPGRADE   	"UP"// DEV ACK
    #define CMD_MP3_UPDATE  	"U2"// DEV ACK
#define CMD_CHANGE_APN    	"UG"// DEV ACK
    #define CMD_START_TRACE   	"T0"// DEV ACK
    #define CMD_STOP_TRACE   	"T2"// DEV ACK
#define CMD_QUERY_NFC   	"QCL"// DEV ACK
#define CMD_EXIT_SLEEP   	"WU"// DEV ACK
#define CMD_DELETE_NFC   	"RMC"// DEV ACK
#define CMD_ADD_NFC         "ADDC"// DEV ACK

#define LEN_NET_TCP    32
#define LEN_CARD_ID    32

#define LEN_COMMON_USE    32

#define LEN_SYS_TIME    32
#define LEN_IMEI_NO     32
#define LEN_BAT_VOL     32
#define LEN_RSSI_VAL    32
#define LEN_MAX_SEND    1024
#define LEN_MAX_RECV    32
#define LEN_DW_MD5      32
#define LEN_DW_URL      128
#define LEN_FILE_NAME   128

enum CMD_TYPE {
	DEV_REGISTER = 0,
	REPORT_GPS,
	IAP_SUCCESS,
    DOOR_UNLOCKED,
    FINISH_RST,
    FINISH_ADDNFC,
	HEART_BEAT,
	QUERY_PARAMS,
	RING_ALARM,
	UNLOCK_DOOR,
	DOOR_LOCKED,
	JUMP_LAMP,
	CALYPSO_UPLOAD,
	FACTORY_RST,
	INVALID_MOVE,
	CHARGE_STARTED,
	CHARGE_STOPED,
	ENTER_SLEEP,
	QUERY_GPS,
	IAP_UPGRADE,
	MP3_UPDATE,
	CHANGE_APN,
	START_TRACE,
	STOP_TRACE,
	QUERY_NFC,
	EXIT_SLEEP,
	DELETE_NFC,
	ADD_NFC,
	DOOR_OPENED,
	RISK_REPORT,
	UNKNOWN_CMD
};

void calc_first_md5();
void parse_mobit_msg(char* msg);

#endif
