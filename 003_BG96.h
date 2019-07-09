//       10        20        30        40        50        60        70
//--*----*----*----*----*----*----*----*----*----*----*----*----*----*----*----*

/******************************************************************************
 * A library for Quectel BG96 Module
 * This file is about the BG96 API
 *
 * Copyright (c) 2019 Mobit technology inc.
 * @Author       : Damon
 * @Create time  : 02/20/2019
******************************************************************************/

#ifndef __BG96_H
#define __BG96_H

#include <string.h>
#include <stdlib.h>

#include <p24fxxxx.h>

#include "---_Defines.h"

/////////////////////////////////// BG96 AT CMDs ///////////////////////////////////
// AT commands response
static const char RESPONSE_READY[] = "RDY";
static const char RESPONSE_OK[] = "OK";
static const char RESPONSE_CRLF_OK[] = "\r\n\r\nOK";
static const char RESPONSE_ERROR[] = "ERROR";
static const char RESPONSE_POWER_DOWN[] = "POWERED DOWN";
static const char RESPONSE_CONNECT[] = "CONNECT";
static const char RESPONSE_SEND_OK[] = "SEND OK";
static const char RESPONSE_SEND_FAIL[] = "SEND FAIL";

// common AT commands
static const char DEV_AT[] = "";
static const char DEV_INFORMATION[] = "I";
static const char DEV_VERSION[] = "+CGMR";
static const char DEV_IMEI[] = "+CGSN";
static const char DEV_FUN_LEVEL[] = "+CFUN";
static const char DEV_LOCAL_RATE[] = "+IPR";
static const char DEV_SIM_IMSI[] = "+CIMI";
static const char DEV_SIM_PIN[] = "+CPIN";
static const char DEV_SIM_ICCID[] = "+QCCID";
static const char DEV_NET_STATUS[] = "+CREG";
static const char DEV_NET_STATUS_G[] = "+CGREG";
static const char DEV_EPS_NET_STATUS[] = "+CEREG";
static const char DEV_NET_RSSI[] = "+CSQ";
static const char DEV_NET_OPERATOR[] = "+COPS";
static const char DEV_NET_INFORMATION[] = "+QNWINFO";
static const char DEV_NET_PACKET_COUNTER[] = "+QGDCNT";
static const char DEV_POWER_DOWN[] = "+QPOWD";
static const char DEV_CLOCK[] = "+CCLK";

// TCPIP AT Commands
static const char APN_PARAMETERS[] = "+QICSGP";
static const char ACTIVATE_APN[] = "+QIACT";
static const char DEACTIVATE_APN[] = "+QIDEACT";
static const char GET_APN_IP_ADDRESS[] = "+CGPADDR";
static const char OPEN_SOCKET[] = "+QIOPEN";
static const char CLOSE_SOCKET[] = "+QICLOSE";
static const char SOCKET_STATUS[] = "+QISTATE";
static const char SOCKET_SEND_DATA[] = "+QISEND";
static const char SOCKET_READ_DATA[] = "+QIRD";
static const char SOCKET_SEND_HEX_DATA[] = "+QISENDEX";
static const char DATA_ACCESS_MODES[] = "+QISWTMD";
static const char PING_FUNCTION[] = "+QPING";
static const char NTP_FUNCTION[] = "+QNTP";
static const char CONFIGURE_DNS_SERVER[] = "+QIDNSCFG";
static const char DNS_FUNCTION[] = "+QIDNSGIP";
static const char QUERY_ERROR_CODE[] = "+QIGETERROR";
static const char RECV_SOCKET_EVENT[] = "+QIURC";

// FILE AT Commands
static const char FILE_SPACE_INFORMATION[] = "+QFLDS";
static const char FILE_LIST_FILES[] = "+QFLST";
static const char FILE_DELETE_FILES[] = "+QFDEL";
static const char FILE_UPLOAD_FILES[] = "+QFUPL";
static const char FILE_DOWNLOAD_FILE[] = "+QFDWL";
static const char FILE_OPEN_FILE[] = "+QFOPEN";
static const char FILE_READ_FILE[] = "+QFREAD";
static const char FILE_WRITE_FILE[] = "+QFWRITE";
static const char FILE_SET_POSITION_FILE[] = "+QFSEEK";
static const char FILE_GET_POSITION_FILE[] = "+QFPOSITION";
static const char FILE_TRUNCATE_FILE[] = "+QFTUCAT";
static const char FILE_CLOSE_FILE[] = "+QFCLOSE";

// SSL AT Commands
static const char SSL_CONFIG_PARAMETER[] = "+QSSLCFG";
static const char SSL_OPEN_SOCKET[] = "+QSSLOPEN";
static const char SSL_SEND_DATA[] = "+QSSLSEND";
static const char SSL_READ_DATA[] = "+QSSLRECV";
static const char SSL_CLOSE_SOCKET[] = "+QSSLCLOSE";
static const char SSL_QUERY_STATUS[] = "+QSSLSTATE";
static const char SSL_SOCKET_EVENT[] = "+QSSLURC";

// HTTP AT Commands
static const char HTTP_CONFIG_PARAMETER[] = "+QHTTPCFG";
static const char HTTP_SET_URL[] = "+QHTTPURL";
static const char HTTP_GET_REQUEST[] = "+QHTTPGET";
static const char HTTP_POST_REQUEST[] = "+QHTTPPOST";
static const char HTTP_FILE_POST_REQUEST[] = "+QHTTPPOSTFILE";
static const char HTTP_READ_RESPONSE[] = "+QHTTPREAD";
static const char HTTP_FILE_READ_RESPONSE[] = "+QHTTPREADFILE";

// MQTT AT Commands
static const char MQTT_CONFIG_PARAMETER[] = "+QMTCFG";
static const char MQTT_OPEN_NETWORK[] = "+QMTOPEN";
static const char MQTT_CLOSE_NETWORK[] = "+QMTCLOSE";
static const char MQTT_CREATE_CLIENT[] = "+QMTCONN";
static const char MQTT_CLOSE_CLIENT[] = "+QMTDISC";
static const char MQTT_SUBSCRIBE_TOPICS[] = "+QMTSUB";
static const char MQTT_UNSUBSCRIBE_TOPICS[] = "+QMTUNS";
static const char MQTT_PUBLISH_MESSAGES[] = "+QMTPUB";
static const char MQTT_STATUS[] = "+QMTSTAT";
static const char MQTT_RECV_DATA[] = "+QMTRECV";

// GNSS AT Commands
static const char GNSS_CONFIGURATION[] = "+QGPSCFG";
static const char GNSS_TURN_ON[] = "+QGPS";
static const char GNSS_TURN_OFF[] = "+QGPSEND";
static const char GNSS_GET_POSITION[] = "+QGPSLOC";
static const char GNSS_ACQUIRE_NMEA[] = "+QGPSGNMEA";

/////////////////////////////////// Wait Implement ///////////////////////////////////
// For GPIO Ctrl
#define LOW 0
#define HIGH 1
#define OUTPUT 1
#define POWKEY_PIN  6
#define RESET_PIN   5

/////////////////////////////////// BG96 MACRO ///////////////////////////////////
// For Common
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef enum functionality {
    MINIMUM_FUNCTIONALITY = 0,
    FULL_FUNCTIONALITY = 1,
    DISABLE_RF = 4,
} Functionality_t;

typedef enum cmd_status {
    READ_MODE = 0,
    WRITE_MODE = 1,
} Cmd_Status_t;

typedef enum net_status {
    NOT_REGISTERED = 0,
    REGISTERED = 1,
    SEARCHING = 2,
    REGISTRATION_DENIED = 3,
    UNKNOWN = 4,
    REGISTERED_ROAMING = 5,
} Net_Status_t;

typedef enum net_type {
    GSM = 0,
    LTE_CAT_M1 = 8,
    LTE_CAT_NB1 = 9,
} Net_Type_t;

// For FILE
typedef enum open_file_mode {
    CREATE_OR_OPEN = 0,
    CREATE_OR_CLEAR = 1,
    ONLY_READ = 2,
} Open_File_Mode_t;

typedef enum pointer_mode {
    FILE_BEGINNING = 0,
    FILE_CURRENT = 1,
    FILE_ENDING = 2,
} Pointer_Mode_t;

// For GNSS
typedef enum gnss_work_mode {
    STAND_ALONE = 1,
    MS_BASED = 2,
    MS_ASSISTED = 3,
    SPEED_OPTIMAL = 4,
} GNSS_Work_Mode_t;

typedef enum gnss_constellation {
    GPS_ONLY = 0,
    GPS_GLONASS_BEIDOU_GALILEO = 1,
    GPS_GLONASS_BEIDOU = 2,
    GPS_GLONASS_GALILEO = 3,
    GPS_GLONASS = 4,
    GPS_BEIDOU_GALILEO = 5,
    GPS_GALILEO = 6,
} GNSS_Constellation_t;

typedef enum nmea_sentences_type {
    GPGGA = 1,
    GPRMC = 2,
    GPGSV = 4,
    GPGSA = 8,
    GPVTG = 16,
} NMEA_Type_t;

// For HTTP
typedef enum http_body_data_type {
    APPLICATION_X_WWW_FORM_URLENCODED = 0,
    TEXT_PLAIN = 1,
    APPLICATION_OCTET_STREAM = 2,
    MULTIPART_FORM_DATA = 3,
} HTTP_Body_Data_Type_t;

// For SSL
typedef enum ssl_version {
    SSL_3_0 = 0,
    TLS_1_0 = 1,
    TLS_1_1 = 2,
    TLS_1_2 = 3,
    ALL_VERSION = 4,
} SSL_Version_t;

// For TCPIP
typedef enum protocol_type {
    IPV4 = 1,
    IPV4V6 = 2,
} Protocol_Type_t;

typedef enum authentication_methods {
    NONE = 0,
    PAP = 1,
    CHAP = 2,
    PAP_OR_CHAP = 3,
} Authentication_Methods_t;

typedef enum socket_type {
    TCP_CLIENT = 0,
    TCP_SEVER = 1,
    UDP_CLIENT = 2,
    UDP_SEVER = 3,
} Socket_Type_t;

typedef enum access_mode {
    BUFFER_MODE = 0,
    DIRECT_PUSH_MODE = 1,
    TRANSPARENT_MODE = 2,
} Access_Mode_t;

typedef enum socket_event {
    SOCKET_RECV_DATA_EVENT = 1,
    SOCKET_CLOSE_EVENT = 2,
    SOCKET_PDP_DEACTIVATION_EVENT = 3,
    SOCKET_INCOMING_CONNECTION_EVENT = 4,
    SOCKET_CONNECTION_FULL_EVENT = 5,
} Socket_Event_t;

typedef enum ssl_cipher_suites {
    TLS_RSA_WITH_AES_256_CBC_SHA = 0,
    TLS_RSA_WITH_AES_128_CBC_SHA = 1,
    TLS_RSA_WITH_RC4_128_SHA = 2,
    TLS_RSA_WITH_RC4_128_MD5 = 3,
    TLS_RSA_WITH_3DES_EDE_CBC_SHA = 4,
    TLS_RSA_WITH_AES_256_CBC_SHA256 = 5,
    TLS_ECDHE_RSA_WITH_RC4_128_SHA = 6,
    TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA = 7,
    TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA = 8,
    TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA = 9,
    TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256 = 10,
    TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384 = 11,
    TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256 = 12,
    SUPPORT_ALL_ABOVE = 13,
} SSL_Cipher_Suites_t;

typedef enum ssl_socket_event {
    SSL_SOCKET_RECV_EVENT = 1,
    SSL_SOCKET_CLOSE_EVENT = 2,
} SSL_Socket_Event_t;

static const char ssl_ca_cert_name[] = "ca_cert.pem";
static const char ssl_client_cert_name[] = "client_cert.pem";
static const char ssl_client_key_name[] = "client_key.pem";

// For BG96 Serial
#define RX_BUFFER_LENGTH  512
#define RX_RINGBUFFER_LENGTH 512
// #define UART_DEBUG

static const unsigned long Band_list[] = {
    9600,
    19200,
    38400,
    57600,
    115200,
    230400,
    460800,
    921600
};

typedef enum cmd_response {
    UNKNOWN_RESPONSE  = -2,
    TIMEOUT_RESPONSE  = -1,
    FIAL_RESPONSE  =  0,
    SUCCESS_RESPONSE  = 1,
} Cmd_Response_t;

extern unsigned int bufferHead;
extern char rxBuffer[RX_BUFFER_LENGTH];
extern int errorCode;

/////////////////////////////////// BG96 API ///////////////////////////////////
bool InitModule();

bool SetDevCommandEcho(bool echo);

bool GetDevInformation(char *inf);

bool GetDevVersion(char *ver);

bool GetDevIMEI(char *imei);

Cmd_Response_t SetDevFunctionality(Functionality_t mode);

bool DevLocalRate(unsigned long *rate, Cmd_Status_t status);

bool GetDevSimIMSI(char *imsi);

bool DevSimPIN(char *pin, Cmd_Status_t status);

bool GetDevSimICCID(char *iccid);

Net_Status_t DevNetRegistrationStatus();

bool GetDevNetSignalQuality(unsigned int *rssi);

Cmd_Response_t ScanOperatorNetwork(char *net);

Cmd_Response_t DevOperatorNetwork(unsigned int *mode, unsigned int *format, char *oper, Net_Type_t *act, Cmd_Status_t status);

bool GetDevNetworkInformation(char *type, char *oper, char *band, char *channel);

bool DevNetPacketCounter(unsigned long *send_bytes, unsigned long *recv_bytes, bool clean);

bool DevPowerDown();

bool DevClock(char *d_clock, Cmd_Status_t status);

// For FILE
bool GetFliesSpace(unsigned long *free_bytes, unsigned long *total_bytes);

bool GetFilesList(char *list);

bool DeleteFiles(const char *filename);

bool UploadFiles(const char *filename, const char *u_file);

bool DownloadFiles(char *filename, char *d_file);

bool OpenFile(char *filename, Open_File_Mode_t mode, unsigned int *file_index);

bool ReadFile(unsigned int file_index, char *read_data);

bool WriteFile(unsigned int file_index, char *write_data);

bool CloseFlie(unsigned int file_index);

bool SetFilePointer(unsigned int file_index, unsigned int offset, Pointer_Mode_t p_mode);

bool GetFilePointer(unsigned int file_index, unsigned int *offset);

bool TruncateFile(unsigned int file_index);


// For GNSS
bool SetGNSSConstellation(GNSS_Constellation_t constellation);

bool SetGNSSEnableNMEASentences(bool enable);

bool SetGNSSAutoRun(bool auto_run);

bool TurnOnGNSS(GNSS_Work_Mode_t mode, Cmd_Status_t status);

bool GetGNSSPositionInformation(char *position);

bool TurnOffGNSS();

bool GetGNSSNMEASentences(NMEA_Type_t type, char *sentences);

// For HTTP
bool SetHTTPConfigParameters(unsigned int pdp_index, bool request_header, bool response_header, HTTP_Body_Data_Type_t type);

bool SetHTTPEnableSSL(unsigned int ssl_index);

bool HTTPURL(char *url, Cmd_Status_t status);

bool HTTPGET(unsigned int timeout);

bool HTTPPOST(char *post_data, unsigned int timeout);

bool HTTTPPOSTFile(char *filename, unsigned int timeout);

bool HTTPRead(char *read_data, unsigned int timeout);

bool HTTPReadToFile(char *filename, unsigned int timeout);

// For SSL
bool SetSSLParameters(unsigned int ssl_index, SSL_Version_t s_version, SSL_Cipher_Suites_t s_ciper, unsigned int negotiation_time);

bool SetSSLCertificate(unsigned int ssl_index, const char *ca_cert_path, const char *client_cert_path, const char *client_key_path, bool validity_check);

bool InitSSL(unsigned int ssl_index, char *ca_cert, char *client_cert, char *client_key, char *err_code);

bool OpenSSLSocket(unsigned int pdp_index, unsigned int ssl_index, unsigned int socket_index, char *ip, unsigned int port, Access_Mode_t mode);

bool SSLSocketSendData(unsigned int socket_index, char *ssl_send_data);

bool SSLSocketRecvData(unsigned int socket_index, unsigned int ssl_recv_len, char *ssl_recv_data);

bool CloseSSLSocket(unsigned int socket_index);

bool QuerySSLSocketStatus(unsigned int socket_index, char *ssl_status);

SSL_Socket_Event_t WaitCheckSSLSocketEvent(char *event, unsigned int timeout);

// For TCPIP
bool SetDevAPNParameters(unsigned int pdp_index, Protocol_Type_t type, char *apn, char *usr, char *pwd, Authentication_Methods_t met);

Cmd_Response_t ActivateDevAPN(unsigned int pdp_index);

bool DeactivateDevAPN(unsigned int pdp_index);

bool GetDevAPNIPAddress(unsigned int pdp_index, char *ip);

bool InitAPN(unsigned int pdp_index, char *apn, char *usr, char *pwd, char *err_code);

bool OpenSocketService(unsigned int pdp_index, unsigned int socket_index, Socket_Type_t socket, char *ip, unsigned int port, unsigned int local_port, Access_Mode_t mode);

bool CloseSocketService(unsigned int socket_index);

bool SocketSendData(unsigned int socket_index, Socket_Type_t socket, char *data_buf, char *ip, unsigned int port);

bool SocketRecvData(unsigned int socket_index, unsigned int recv_len, Socket_Type_t socket, char *recv_buf);

bool SocketSendHEXData(unsigned int socket_index, char *hex_buf);

bool SwitchAccessModes(unsigned int socket_index, Access_Mode_t mode);

bool DevPingFunction(unsigned int socket_index, char *host);

bool DevNTPFunction(unsigned int socket_index, char *ntp_ip, unsigned int port, char *time);

bool ConfigDNSServer(unsigned int socket_index, char *primary_addr, char *secondary_addr);

bool DevDNSFunction(unsigned int socket_index, char *domain_name, char *ip);

bool QueryLastErrorCode(char *err_code);

Socket_Event_t WaitCheckSocketEvent(char *event, unsigned int timeout);

// For Serial
bool SendDataAndCheck(const char *data_buf, const char *ok_str, const char *err_str, unsigned int timeout);

bool SendATcommand(const char *command);

unsigned int ReadResponseByteToBuffer();

unsigned int ReadResponseToBuffer(unsigned int timeout);

Cmd_Response_t ReadResponseAndSearch(const char *test_str, unsigned int timeout);

Cmd_Response_t ReadResponseAndSearchChr(const char test_chr, unsigned int timeout);

Cmd_Response_t ReadResponseAndSearch_multi(const char *test_str, const char *e_test_str, unsigned int timeout);

Cmd_Response_t SendAndSearch(const char *command, const char *test_str, unsigned int timeout);

Cmd_Response_t SendAndSearchChr(const char *command, const char test_chr, unsigned int timeout);

Cmd_Response_t SendAndSearch_multi(const char *command, const char *test_str, const char *e_test_str, unsigned int timeout);

bool ReturnErrorCode(int *s_err_code);

void CleanBuffer();

int IsRingBufferAvailable();

char *SearchStrBuffer(const char *test_str);

char *SearchChrBuffer(const char test_chr);

void Configure_BG96(void);

int IsTmpRingBufferAvailable();
bool WaitUartNetRxIdle();
int IsNetRingBufferAvailable();
char ReadByteFromNetRingBuffer();

bool BG96ATInit(void);
bool HeartBeat(void);

void InitRingBuffers(void);

bool BG96ATInitialize(void);
bool ConnectToTcpServer(void);
bool BG96TcpSend(void);

#endif //__BG96_H

//******************************************************************************
//* END OF FILE
//******************************************************************************
