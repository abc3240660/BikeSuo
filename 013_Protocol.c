//       10        20        30        40        50        60        70
//--*----*----*----*----*----*----*----*----*----*----*----*----*----*----*----*

/******************************************************************************
 * A library for MOBIT Protocol
 * This file is about the MOBIT Protocol API
 *
 * Copyright (c) 2019 Mobit technology inc.
 * @Author       : Damon
 * @Create time  : 02/20/2019
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include "013_Protocol.h"
#include "014_md5.h"

const char* cmd_list[] = {
	CMD_DEV_REGISTER,
    CMD_REPORT_GPS,
	CMD_IAP_SUCCESS,
	CMD_DOOR_UNLOCKED,
    CMD_FINISH_RST,
    CMD_FINISH_ADDNFC,
	CMD_HEART_BEAT,
	CMD_QUERY_PARAMS,
	CMD_RING_ALARM,
	CMD_UNLOCK_DOOR,
	CMD_DOOR_LOCKED,
	CMD_JUMP_LAMP,
	CMD_CALYPSO_UPLOAD,
	CMD_FACTORY_RST,
	CMD_INVALID_MOVE,
	CMD_CHARGE_STARTED,
	CMD_CHARGE_STOPED,
	CMD_ENTER_SLEEP,
	CMD_QUERY_GPS,
	CMD_IAP_UPGRADE,
	CMD_MP3_UPDATE,
	CMD_CHANGE_APN,
	CMD_START_TRACE,
	CMD_STOP_TRACE,
	CMD_QUERY_NFC,
	CMD_EXIT_SLEEP,
	CMD_DELETE_NFC,
	CMD_ADD_NFC,
	CMD_DOOR_OPENED,
	CMD_RISK_REPORT,
	NULL
};

u32 g_need_ack = 0;

// DOOR Sta:
u8 g_door_state = 0;

// Door LOCK Sta:
// BIT7: 0-idle, 1-changed
// BIT0: 0-locked, 1-unlocked
u8 g_drlock_sta_chged = 0;

// Door Open/Close Sta:
// BIT7: 0-idle, 1-changed
// BIT0: 0-closed, 1-opened
u8 g_dropen_sta_chged = 0;

// HandBrake LOCK Sta:
// BIT7: 0-idle, 1-changed
// BIT0: 0-locked, 1-unlocked
u8 g_hbrake_sta_chged = 0;

u16 g_gps_trace_gap = 0;

u8 g_server_time[LEN_SYS_TIME+1] = "";

u8 g_msg_md5[LEN_DW_MD5+1] = "";
u8 g_card_ids[(LEN_CARD_ID+1)*10] = "";

u8 g_net_ip[LEN_NET_TCP+1] = "";
u8 g_net_port[LEN_NET_TCP+1] = "";
u8 g_net_apn[LEN_NET_TCP+1] = "";

u8 g_iap_update = 0;
u8 g_iap_update_md5[LEN_DW_MD5+1] = "";
u8 g_iap_update_url[LEN_DW_URL+1] = "";

u8 g_hbeat_gap = 6;// default 6s

u8 g_CHANGE_APN_name[LEN_FILE_NAME+1];

extern u8 g_first_md5[LEN_COMMON_USE];
extern u8 g_bg96_imei[LEN_COMMON_USE];
extern u8 g_bg96_iccid[LEN_COMMON_USE];

void calc_first_md5()
{
    u8 i = 0;
    MD5_CTX g_ota_md5_ctx;
    
    GAgent_MD5Init(&g_ota_md5_ctx);
    GAgent_MD5Update(&g_ota_md5_ctx, g_bg96_imei, strlen((char*)g_bg96_imei));
    GAgent_MD5Update(&g_ota_md5_ctx, g_bg96_iccid, strlen((char*)g_bg96_iccid));
    GAgent_MD5Final(&g_ota_md5_ctx, g_first_md5);
    
    printf("MD5 = ");
    for (i=0; i<16; i++) {
        printf("%.2X", g_first_md5[i]);
    }
    printf("\r\n");
}

u8 get_mobit_cmd_count()
{
	u8 cnt = 0;
	while(1) {
		if (NULL == cmd_list[cnt]) {
			break;
		}
		cnt++;
	}

	return cnt;
}

u8 is_supported_mobit_cmd(u8 pos, char* str)
{
	u8 i = 0;
    u8 cmd_count = get_mobit_cmd_count();
    
    printf("pos = %d\n", pos);
	for (i=pos; i<cmd_count; i++) {
		if (0 == strncmp(str, cmd_list[i], strlen(cmd_list[i]))) {
			break;
		}
	}

	if (i != UNKNOWN_CMD) {
		printf("Recved CMD/ACK %s\n", str);
	}

	return i;
}

void parse_mobit_msg(char* msg)
{
    u8 k = 0;
    u16 i = 0;
    u8 is_run = 0;
    int index = 0;
	char delims[] = ",";
	char* split_str = NULL;

	enum CMD_TYPE cmd_type = UNKNOWN_CMD;

#ifdef DEBUG_USE
	//printf("Support %d CMDs\n", cmd_count);
#endif

    // MD5 Validation
    memcpy(g_msg_md5, msg+strlen(msg)-32, LEN_DW_MD5);
    g_msg_md5[LEN_DW_MD5] = '\0';
	printf("g_msg_md5 = %s\n", g_msg_md5);
    
    if (0) {// MD5 is invalid
        return;
    }

	split_str = strtok(msg, delims);
	while(split_str != NULL) {
#ifdef DEBUG_USE
		//printf("split_str = %s\n", split_str);
#endif
		// index = 3: SVR CMD
		// index = 4: SVR ACK
        if (1 == index) {
            if (0 == strncmp(split_str, "Run", strlen("Run")-1)) {
                is_run = 1;
            }
            
            printf("is_run = %d\n", is_run);
        } else if (2 == index) {
            if (0 == is_run) {
				cmd_type = (enum CMD_TYPE)is_supported_mobit_cmd(0, split_str);
            } else {
                cmd_type = (enum CMD_TYPE)is_supported_mobit_cmd(HEART_BEAT, split_str);
            }

            printf("cmd_type = %d\r\n", cmd_type);
                
        	if (strstr((const char*)msg, (const char*)"B5")) {
            	g_door_state = 0;
			}
				
			if (cmd_type != UNKNOWN_CMD) {
                printf("cmd_type = %d\r\n", cmd_type);
                
                // No need Parse extra params
                ////////////////// SVR CMDs //////////////////
                // Need do some action
                if (UNLOCK_DOOR == cmd_type) {
                    g_need_ack |= (1<<cmd_type);
                } else if (FACTORY_RST == cmd_type) {
                    g_need_ack |= (1<<cmd_type);
                } else if (ADD_NFC == cmd_type) {
                    g_need_ack |= (1<<cmd_type);
                } else if (QUERY_PARAMS == cmd_type) {
                    g_need_ack |= (1<<cmd_type);
                } else if (ENTER_SLEEP == cmd_type) {
                    g_need_ack |= (1<<cmd_type);
                } else if (QUERY_GPS == cmd_type) {
                    g_need_ack |= (1<<cmd_type);
                } else if (QUERY_NFC == cmd_type) {
                    g_need_ack |= (1<<cmd_type);
                } else if (EXIT_SLEEP == cmd_type) {
                    g_need_ack |= (1<<cmd_type);
                ////////////////// SVR ACKs //////////////////
                // Need update completed flag
				} else if (HEART_BEAT == cmd_type) {
                // Below comments:
                // To ensure the server has received this device's notice
                // If not, device will repeat send this notice
				} else if (DOOR_LOCKED == cmd_type) {
                    g_drlock_sta_chged &= 0x7F;
				} else if (DOOR_UNLOCKED == cmd_type) {
                    g_drlock_sta_chged &= 0x7F;
				} else if (DOOR_OPENED == cmd_type) {
                    g_dropen_sta_chged &= 0x7F;
				} else if (FINISH_ADDNFC == cmd_type) {
                    g_dropen_sta_chged &= 0x7F;
				} else if (FINISH_RST == cmd_type) {
                    g_hbrake_sta_chged &= 0x7F;
				} else if (RISK_REPORT == cmd_type) {
                    g_hbrake_sta_chged &= 0x7F;
                ////////////////// SVR ACKs //////////////////
                // Needn't do anything
				} else if (HEART_BEAT == cmd_type) {
                	// Do nothing
				}
			} else {// Maybe Re, So Can Not break
				break;
            }
		} else if (index > 2) {// Need to Parse extra params
            // Parse CMD or ACK
			if (DEV_REGISTER == cmd_type) {
				if (3 == index) {
					g_hbeat_gap = atoi(split_str);
					printf("g_hbeat_gap = %d\n", g_hbeat_gap);
                    if (g_hbeat_gap < 5) {
                        g_hbeat_gap = 5;
                        printf("change g_hbeat_gap = %d\n", g_hbeat_gap);
                    }
				} else if (4 == index) {
					strncpy((char*)g_server_time, split_str, LEN_SYS_TIME);
					g_server_time[LEN_SYS_TIME] = '\0';
					printf("g_swap_pw = %s\n", g_server_time);
				}
			} else if (IAP_UPGRADE == cmd_type) {
                if (3 == index) {
                    g_iap_update = 1;
                    memset(g_iap_update_url, 0, LEN_DW_URL);
                    strncpy((char*)g_iap_update_url, split_str, LEN_DW_URL);
                    printf("g_iap_update_url = %s\n", g_iap_update_url);
                } else if (4 == index) {
                    memset(g_iap_update_md5, 0, LEN_DW_URL);
                    strncpy((char*)g_iap_update_md5, split_str, LEN_DW_URL);
                    printf("g_iap_update_md5 = %s\n", g_iap_update_md5);
                    
    				g_need_ack |= (1<<cmd_type);
                }
			} else if (CHANGE_APN == cmd_type) {
                if (3 == index) {
                    memset(g_net_ip, 0, LEN_NET_TCP);
                    strncpy((char*)g_net_ip, split_str, LEN_NET_TCP);
                    printf("g_net_ip = %s\n", g_net_ip);   
                } else if (4 == index) {
                    memset(g_net_port, 0, LEN_NET_TCP);
                    strncpy((char*)g_net_port, split_str, LEN_NET_TCP);
                    printf("g_net_port = %s\n", g_net_port); 
                } else if (5 == index) {
                    memset(g_net_apn, 0, LEN_NET_TCP);
                    strncpy((char*)g_net_apn, split_str, LEN_NET_TCP);
                    printf("g_net_apn = %s\n", g_net_apn); 
                }
				
				g_need_ack |= (1<<cmd_type);
			} else if (MP3_UPDATE == cmd_type) {
				if (4 == index) {
					//memset(g_mp3_update_name, 0, LEN_FILE_NAME);
					//strncpy((char*)g_mp3_update_name, split_str, LEN_FILE_NAME);
					//printf("g_mp3_update_name = %s\n", g_mp3_update_name);
				} else if (5 == index) {
					//memset(g_mp3_update_url, 0, LEN_DW_URL);
					//g_mp3_update = 1;
					//strncpy((char*)g_mp3_update_url, split_str, LEN_DW_URL);
					//printf("g_mp3_update_url = %s\n", g_mp3_update_url);
				}
            } else if (DELETE_NFC == cmd_type) {
                if (3 == index) {
                    u8 tmp_card[32]="";
                    memset(g_card_ids, 0, LEN_CARD_ID);
                    strncpy((char*)g_card_ids, split_str, LEN_CARD_ID);
                    printf("g_card_ids = %s\n", g_card_ids);
                    
                    for (i=0; i<strlen((char*)g_card_ids);i++) {
                        if ('|' == g_card_ids[i]) {
                            // do delete
                            printf("To deleteX %s\n", tmp_card);
                            
                            k = 0;
                            memset(tmp_card, 0, 32);
                        } else {
                            tmp_card[k++] = g_card_ids[i];
                        }
                    }
                    
                    // do delete
                    printf("To delete %s\n", tmp_card);
                }
                g_need_ack |= (1<<cmd_type);
			} else if (START_TRACE == cmd_type) {
                //g_time_start_gps = os_jiffies;
				//g_gps_trace_gap = atoi(split_str);
				//printf("g_gps_trace_gap = %d\n", g_gps_trace_gap);
                //if (g_gps_trace_gap < 5) {
                //    g_gps_trace_gap = 5;
                //    printf("change g_gps_trace_gap = %d\n", g_gps_trace_gap);
                //}

				g_need_ack |= (1<<cmd_type);
			} else if (RING_ALARM == cmd_type) {
				//g_ring_times = atoi(split_str);
				//printf("g_ring_times = %d\n", g_ring_times);

				g_need_ack |= (1<<cmd_type);
			} else if (JUMP_LAMP == cmd_type) {
				//g_lamp_times = atoi(split_str);
				//printf("g_lamp_times = %d\n", g_lamp_times);

				g_need_ack |= (1<<cmd_type);
			}
		}
		split_str = strtok(NULL, delims);
		if ((NULL==split_str) && (MP3_UPDATE==cmd_type) && (4==index)) {
			//if url NULL -> delete file
			//u8 mp3_file[LEN_FILE_NAME+1] = "";
			//sprintf((char*)mp3_file, "0:/MUSIC/%s.mp3", g_mp3_update_name);
			//f_unlink((const char*)mp3_file);
			//printf("%s deleted\n", mp3_file);
		}
		index++;
	}
}